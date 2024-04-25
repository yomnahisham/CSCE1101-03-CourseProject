#include "allusers.h"
#include "user.h"
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

qint64 AllUsers::tokenExpirationTimestamp = 0;

AllUsers::AllUsers() {}

bool AllUsers::isTokenExpired() {
    QDateTime expirationTime = QDateTime::fromSecsSinceEpoch(AllUsers::tokenExpirationTimestamp);
    QDateTime currentDateTime = QDateTime::currentDateTime();
    return currentDateTime >= expirationTime;
}

void AllUsers::refreshToken(QString& newAccessToken) {
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest request(QUrl("https://api.dropbox.com/oauth2/token"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QByteArray postData;
    postData.append("grant_type=refresh_token");
    postData.append("&refresh_token=" + newAccessToken.toUtf8());
    QNetworkReply* reply = manager->post(request, postData);

    QObject::connect(reply, &QNetworkReply::finished, [=, &newAccessToken]() mutable {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
            QJsonObject jsonObject = jsonDoc.object();
            newAccessToken = jsonObject.value("access_token").toString();
            int expiresIn = jsonObject.value("expires_in").toInt();
            QDateTime currentDateTime = QDateTime::currentDateTime();
            AllUsers::tokenExpirationTimestamp = currentDateTime.addSecs(expiresIn).toSecsSinceEpoch();
            qDebug() << "Token Expiration Time:" << currentDateTime.addSecs(expiresIn).toString();
            qDebug() << "Access token refreshed successfully.";
        } else {
            qDebug() << "Error: " << reply->errorString();
        }
        reply->deleteLater();
        manager->deleteLater();
    });
}

void AllUsers::addUser(const QString& username, const QString& password){
    AllUsers::saveUserDataToDropbox(username, password, 0);
}

void AllUsers::showLeaderboard() {
    QString dropboxAccessToken;
    if (AllUsers::isTokenExpired()) {
        AllUsers::refreshToken(dropboxAccessToken);
    }

    QDir directory("CSCE1101-03-CourseProject-Database/UserData");
    QStringList files = directory.entryList(QStringList() << "*.txt", QDir::Files);

    QMap<int, QString> leaderboard;

    for (const QString& fileName : files) {
        QFile file("CSCE1101-03-CourseProject-Database/UserData/" + fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString username = fileName.split('.').first();
            int score = in.readAll().toInt();
            leaderboard.insert(-score, username);
            file.close();
        }
    }

    qDebug() << "Top 5 Leaderboard:";
    int count = 0;
    QMapIterator<int, QString> i(leaderboard);
    while (i.hasNext() && count < 5) {
        i.next();
        qDebug() << "Username:" << i.value() << ", Score:" << -i.key();
        ++count;
    }
}

bool AllUsers::authenticateUser(const QString &username, const QString &password) {
    QString dropboxAccessToken;
    if (AllUsers::isTokenExpired()) {
        AllUsers::refreshToken(dropboxAccessToken);
    }

    QString filePath = "/CSCE1101-03-CourseProject-Database/UserData/" + username + ".txt";

    QNetworkAccessManager* manager = new QNetworkAccessManager();

    QNetworkRequest request(QUrl("https://content.dropboxapi.com/2/files/download"));
    request.setRawHeader("Authorization", ("Bearer " + dropboxAccessToken).toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject payload;
    payload["path"] = filePath;

    QNetworkReply* reply = manager->post(request, QJsonDocument(payload).toJson());

    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        bool authenticated = false;
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();
            QJsonObject userData = QJsonDocument::fromJson(data).object();
            QString storedPassword = userData.value("password").toString();
            authenticated = (storedPassword == password);
            qDebug() << "Authentication result:" << authenticated;
        } else {
            qDebug() << "Error downloading user data file:" << reply->errorString();
        }
        reply->deleteLater();
        manager->deleteLater();
    });

    return false;
}

bool AllUsers::search(const QString& username) {
    QString dropboxAccessToken;
    if (AllUsers::isTokenExpired()) {
        AllUsers::refreshToken(dropboxAccessToken);
    }

    QString directoryPath = "/CSCE1101-03-CourseProject-Database/UserData/";

    QNetworkAccessManager* manager = new QNetworkAccessManager();

    QNetworkRequest request(QUrl("https://content.dropboxapi.com/2/files/list_folder"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", ("Bearer " + dropboxAccessToken).toUtf8());

    QJsonObject payload;
    payload["path"] = directoryPath;

    QNetworkReply* reply = manager->post(request, QJsonDocument(payload).toJson());

    bool fileExists = false;

    QObject::connect(reply, &QNetworkReply::finished, [=, &fileExists]() mutable {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
            QJsonObject jsonObject = jsonDoc.object();
            QJsonArray entries = jsonObject["entries"].toArray();
            for (const auto& entry : entries) {
                QJsonObject file = entry.toObject();
                QString filename = file["name"].toString();
                if (filename == username + ".txt") {
                    fileExists = true;
                    break;
                }
            }
        } else {
            qDebug() << "Error: " << reply->errorString();
        }
        reply->deleteLater();
        manager->deleteLater();
    });

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    return fileExists;
}

int AllUsers::getScore(const QString& username) {
    QString dropboxAccessToken;
    if (AllUsers::isTokenExpired()) {
        AllUsers::refreshToken(dropboxAccessToken);
    }

    QString filePath = "/CSCE1101-03-CourseProject-Database/UserData/" + username + ".txt";

    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest request(QUrl("https://content.dropboxapi.com/2/files/download"));
    request.setRawHeader("Authorization", ("Bearer " + dropboxAccessToken).toUtf8());

    QNetworkReply* reply = manager->post(request, QJsonDocument(QJsonObject{{"path", filePath}}).toJson());

    int score = 0;

    QObject::connect(reply, &QNetworkReply::finished, [=, &score]() mutable {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
            QJsonObject jsonObject = jsonDoc.object();
            score = jsonObject.value("score").toInt();
        } else {
            qDebug() << "Error: " << reply->errorString();
        }
        reply->deleteLater();
        manager->deleteLater();
    });

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    return score;
}

void AllUsers::saveUserDataToDropbox(const QString& username, const QString& password, int score) {
    QString dropboxAccessToken;
    if (AllUsers::isTokenExpired()) {
        AllUsers::refreshToken(dropboxAccessToken);
    }

    QString filePath = "/CSCE1101-03-CourseProject-Database/UserData/" + username + ".txt";

    QJsonObject jsonPayload;
    jsonPayload["path"] = filePath;
    jsonPayload["mode"] = "overwrite";
    jsonPayload["autorename"] = true;
    jsonPayload["mute"] = false;
    jsonPayload["username"] = username;
    jsonPayload["password"] = password;
    jsonPayload["score"] = score;

    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest request(QUrl("https://content.dropboxapi.com/2/files/upload"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");
    request.setRawHeader("Authorization", ("Bearer " + dropboxAccessToken).toUtf8());

    QNetworkReply* reply = manager->post(request, QJsonDocument(jsonPayload).toJson());

    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "User data saved to Dropbox successfully.";
        } else {
            qDebug() << "Error: " << reply->errorString();
        }
        reply->deleteLater();
        manager->deleteLater();
    });
}

void AllUsers::updateScoreInDropbox(const QString& username, int newScore) {
    QString dropboxAccessToken;
    if (AllUsers::isTokenExpired()) {
        AllUsers::refreshToken(dropboxAccessToken);
    }

    QString filePath = "/CSCE1101-03-CourseProject-Database/UserData/" + username + ".txt";

    QJsonObject jsonPayload;
    jsonPayload["path"] = filePath;
    jsonPayload["mode"] = "add";
    jsonPayload["autorename"] = true;
    jsonPayload["mute"] = false;
    jsonPayload["score"] = newScore;

    if (newScore > getScore(username)) {
        QNetworkAccessManager* manager = new QNetworkAccessManager();
        QNetworkRequest request(QUrl("https://content.dropboxapi.com/2/files/upload"));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");
        request.setRawHeader("Authorization", ("Bearer " + dropboxAccessToken).toUtf8());

        QNetworkReply* reply = manager->post(request, QJsonDocument(jsonPayload).toJson());

        QObject::connect(reply, &QNetworkReply::finished, [=]() {
            if (reply->error() == QNetworkReply::NoError) {
                qDebug() << "Score updated in Dropbox successfully.";
            } else {
                qDebug() << "Error: " << reply->errorString();
            }
            reply->deleteLater();
            manager->deleteLater();
        });
    } else {
        qDebug() << "New score is not higher than the existing score.";
    }
}
