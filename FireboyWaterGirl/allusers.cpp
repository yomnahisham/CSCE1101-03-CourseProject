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

//check if the access token has expired
bool AllUsers::isTokenExpired() {
    QDateTime expirationTime = QDateTime::fromSecsSinceEpoch(AllUsers::tokenExpirationTimestamp);
    return QDateTime::currentDateTime() >= expirationTime;
}

//refresh the access token
void AllUsers::refreshToken() {
    QFile refreshTokenFile(":/assets/dropbox_refresh_token.txt");
    if (!refreshTokenFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error: Unable to open Dropbox refresh token file";
        return;
    }
    QString refreshToken = QTextStream(&refreshTokenFile).readAll();
    refreshTokenFile.close();

    //request to refresh the access token
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest request(QUrl("https://api.dropbox.com/oauth2/token"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    //request body with the refresh token
    QByteArray postData;
    postData.append("grant_type=refresh_token");
    postData.append("&refresh_token=" + refreshToken.toUtf8());

    //POST request to refresh the access token
    QNetworkReply* reply = manager->post(request, postData);

    //response??
    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            // Parse the response JSON
            QByteArray data = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
            QJsonObject jsonObject = jsonDoc.object();

            // Extract the new access token and expiration time
            QString newAccessToken = jsonObject.value("access_token").toString();
            int expiresIn = jsonObject.value("expires_in").toInt(); // Expiry time in seconds

            // Update the access token in your application's configuration
            QFile tokenFile(QDir::currentPath() + "/dropbox_token.txt");
            if (!tokenFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
                qDebug() << "Error: Unable to open Dropbox access token file for writing";
                return;
            }
            QTextStream out(&tokenFile);
            out << newAccessToken;
            tokenFile.close();

            // Update the token expiration timestamp (e.g., by adding expiresIn seconds to the current time)
            QDateTime currentDateTime = QDateTime::currentDateTime();
            QDateTime expirationDateTime = currentDateTime.addSecs(expiresIn);
            // Store the expiration timestamp in your application's configuration
            // (e.g., another file or wherever you're storing the token information)

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
    if (AllUsers::isTokenExpired()) {
        AllUsers::refreshToken(); //refresh the access token if it has expired
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
            leaderboard.insert(-score, username); // Store scores in descending order
            file.close();
        }
    }

    //later to be edited, not the purpose, just for testing purposes
    qDebug() << "Top 5 Leaderboard:";
    int count = 0;
    QMapIterator<int, QString> i(leaderboard);
    while (i.hasNext() && count < 5) {
        i.next();
        qDebug() << "Username:" << i.value() << ", Score:" << -i.key(); //reverse the sign to get original score
        ++count;
    }
}

bool AllUsers::authenticateUser(const QString &username, const QString &password) {
    if (AllUsers::isTokenExpired()) {
        AllUsers::refreshToken(); //refresh the access token if it has expired
    }

    QFile tokenFile(":/assets/dropbox_token.txt");
    if (!tokenFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error: Unable to open Dropbox access token file";
        return false;
    }
    QString dropboxAccessToken = QTextStream(&tokenFile).readAll();
    tokenFile.close();

    //construct the file path for the user's data file
    QString filePath = "/CSCE1101-03-CourseProject-Database/UserData/" + username + ".txt";

    //network access manager
    QNetworkAccessManager* manager = new QNetworkAccessManager();

    //request
    QNetworkRequest request(QUrl("https://content.dropboxapi.com/2/files/download"));
    request.setRawHeader("Authorization", ("Bearer " + dropboxAccessToken).toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //construct the JSON payload for the request
    QJsonObject payload;
    payload["path"] = filePath;

    //POST request to download the user's data file
    QNetworkReply* reply = manager->post(request, QJsonDocument(payload).toJson());

    bool authenticated = false;

    //response??
    QObject::connect(reply, &QNetworkReply::finished, [=, &authenticated]() mutable {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();
            QJsonObject userData = QJsonDocument::fromJson(data).object();

            // Extract password from user data
            QString storedPassword = userData.value("password").toString();

            // Compare passwords
            authenticated = (storedPassword == password);
            qDebug() << "Authentication result:" << authenticated; // Debug output
        } else {
            qDebug() << "Error downloading user data file:" << reply->errorString(); // Debug output
        }
        reply->deleteLater();
        manager->deleteLater();
    });

    //wait for the request to finish
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    return authenticated;
}


bool AllUsers::search(const QString& username) {
    //check if token expired, if so, refresh it
    if (AllUsers::isTokenExpired()) {
        AllUsers::refreshToken();
    }

    QFile tokenFile(":/assets/dropbox_token.txt");
    if (!tokenFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error: Unable to open Dropbox access token file";
        return false;
    }
    QString dropboxAccessToken = QTextStream(&tokenFile).readAll();
    tokenFile.close();

    QString directoryPath = "/CSCE1101-03-CourseProject-Database/UserData/";

    //network access manager
    QNetworkAccessManager* manager = new QNetworkAccessManager();

    //request to list the contents of the directory
    QNetworkRequest request(QUrl("https://content.dropboxapi.com/2/files/list_folder"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", ("Bearer " + dropboxAccessToken).toUtf8());

    //construct the JSON payload for the request
    QJsonObject payload;
    payload["path"] = directoryPath;

    //POST request to list the contents of the directory
    QNetworkReply* reply = manager->post(request, QJsonDocument(payload).toJson());

    // Initialize a variable to store the result of file existence check
    bool fileExists = false;

    //response??
    QObject::connect(reply, &QNetworkReply::finished, [=, &fileExists]() mutable {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
            QJsonObject jsonObject = jsonDoc.object();
            //check if the response contains the file entry for the username
            QJsonArray entries = jsonObject["entries"].toArray();
            for (const auto& entry : entries) {
                QJsonObject file = entry.toObject();
                QString filename = file["name"].toString();
                if (filename == username + ".txt") {
                    // File exists
                    fileExists = true;
                    break;
                }
            }
        } else {
            qDebug() << "Error: " << reply->errorString();
        }
        //delete the reply object and the network access manager
        reply->deleteLater();
        manager->deleteLater();
    });

    //wait for the request to finish
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    return fileExists;
}

int AllUsers::getScore(const QString& username) {
    //check if token expired, if so, refresh it
    if (AllUsers::isTokenExpired()) {
        AllUsers::refreshToken();
    }

    QFile tokenFile(":/assets/dropbox_token.txt");
    if (!tokenFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error: Unable to open Dropbox access token file";
        return 0;
    }
    QString dropboxAccessToken = QTextStream(&tokenFile).readAll();
    tokenFile.close();

    QString filePath = "/CSCE1101-03-CourseProject-Database/UserData/" + username + ".txt";

    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest request(QUrl("https://content.dropboxapi.com/2/files/download"));
    request.setRawHeader("Authorization", ("Bearer " + dropboxAccessToken).toUtf8());

    QNetworkReply* reply = manager->post(request, QJsonDocument(QJsonObject{{"path", filePath}}).toJson());

    int score = 0;

    //response??
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

    //wait for reply to finish
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    return score;
}

void AllUsers::saveUserDataToDropbox(const QString& username, const QString& password, int score) {
    //check if token expired, if so, refresh it
    if (AllUsers::isTokenExpired()) {
        AllUsers::refreshToken();
    }

    QFile tokenFile(":/assets/dropbox_token.txt");
    if (!tokenFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error: Unable to open Dropbox access token file";
        return;
    }
    QString dropboxAccessToken = QTextStream(&tokenFile).readAll();
    tokenFile.close();

    QString filePath = "/CSCE1101-03-CourseProject-Database/UserData/" + username + ".txt";

    //construct the JSON payload
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

    //response??
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
    QFile tokenFile(":/assets/dropbox_token.txt");
    if (!tokenFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error: Unable to open Dropbox access token file";
        return;
    }
    QString dropboxAccessToken = QTextStream(&tokenFile).readAll();
    tokenFile.close();

    QString filePath = "/CSCE1101-03-CourseProject-Database/UserData/" + username + ".txt";

    //construct the JSON payload
    QJsonObject jsonPayload;
    jsonPayload["path"] = filePath;
    jsonPayload["mode"] = "add";
    jsonPayload["autorename"] = true;
    jsonPayload["mute"] = false;
    jsonPayload["score"] = newScore;

    //check if the new score is higher than the existing score
    if (newScore > getScore(username)) {
        QNetworkAccessManager* manager = new QNetworkAccessManager();
        QNetworkRequest request(QUrl("https://content.dropboxapi.com/2/files/upload"));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");
        request.setRawHeader("Authorization", ("Bearer " + dropboxAccessToken).toUtf8());

        QNetworkReply* reply = manager->post(request, QJsonDocument(jsonPayload).toJson());

        //response??
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
