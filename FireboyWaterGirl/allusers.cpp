#include "allusers.h"
#include "user.h"

#include <QDebug>
#include <QCryptographicHash>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QDir>
#include <QCoreApplication>

// initialize static member
QSqlDatabase AllUsers::db;

AllUsers::AllUsers(){}

QString AllUsers::getDatabasePath() {
    // navigate up to get to the desired location for the database
    QDir dir(QCoreApplication::applicationDirPath());
    // goes up in the directory to reach repo folder including the sql db
    dir.cdUp();
    dir.cdUp();
    dir.cdUp();
    dir.cdUp();
    dir.cdUp();
    dir.cdUp();
    QString dbPath = dir.absolutePath() + QDir::separator() + "GameDB.db";
    qDebug() << "Database path: " << dbPath;
    return dbPath;
}

void AllUsers::initializeDatabase() {
    if (!QSqlDatabase::isDriverAvailable("QSQLITE")) {
        qDebug() << "Error: QSQLITE driver not available";
        return;
    }

    db = QSqlDatabase::addDatabase("QSQLITE", "GameDB");
    db.setDatabaseName(getDatabasePath());

    if (!db.open()) {
        qDebug() << "Error: Unable to open database";
        qDebug() << db.lastError().text();
        return;
    }

    // create userInfo table if it does not exist
    QSqlQuery query(db);
    if (!query.exec("CREATE TABLE IF NOT EXISTS userInfo (username VARCHAR(225) NOT NULL UNIQUE, password VARCHAR(225) NOT NULL, score INTEGER NOT NULL, PRIMARY KEY(username))")) {
        qDebug() << "Error: Unable to create userInfo table";
        qDebug() << query.lastError().text();
    }
}

void AllUsers::addUser(const QString& username, const QString& password) {
    QSqlDatabase db = getDatabaseConnection();
    if (!db.isOpen()) {
        qDebug() << "Error: Database is not open";
        return;
    }

    QString hashedPass = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();

    QSqlQuery query(db);
    query.prepare("INSERT INTO userInfo (username, password, score) VALUES (:username, :password, :score)");
    query.bindValue(":username", username);
    query.bindValue(":password", hashedPass);
    query.bindValue(":score", 0);

    if (!query.exec()) {
        qDebug() << "Error: Unable to add user";
        qDebug() << query.lastError().text();
    } else {
        qDebug() << "User added successfully: " << username;
    }
}

void AllUsers::showLeaderboard() {
    QSqlDatabase db = getDatabaseConnection();
    if (!db.isOpen()) {
        qDebug() << "Error: Database is not open";
        return;
    }

    QSqlQuery query("SELECT username, score FROM userInfo ORDER BY score DESC LIMIT 10", db);
    while (query.next()) {
        QString username = query.value(0).toString();
        int score = query.value(1).toInt();
        qDebug() << "Username:" << username << "Score:" << score;
    }
}

User* AllUsers::authenticateUser(const QString &username, const QString &password) {
    QSqlDatabase db = getDatabaseConnection();
    if (!db.isOpen()) {
        qDebug() << "Error: Database is not open";
        return nullptr; // Return nullptr if database is not open
    }

    QString hashedPass = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();
    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM userInfo WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", hashedPass);

    if (!query.exec()) {
        qDebug() << "Error: Unable to authenticate user";
        qDebug() << query.lastError().text();
        return nullptr; // Return nullptr if query execution fails
    }

    query.next();
    int count = query.value(0).toInt();
    if (count == 1) {
        // authentication successful, get user information
        query.prepare("SELECT * FROM userInfo WHERE username = :username AND password = :password");
        query.bindValue(":username", username);
        query.bindValue(":password", hashedPass);
        if (query.exec() && query.next()) {
            QString username = query.value("username").toString();
            int score = query.value("score").toInt();
            QString password = query.value("password").toString(); // Fetch password from the database
            User* user = new User(username, password, score); // Modify the User constructor accordingly
            return user;
        } else {
            qDebug() << "Error: Unable to retrieve user information";
            qDebug() << query.lastError().text();
            return nullptr;
        }
    } else {
        // authentication failed
        qDebug() << "Authentication failed for user: " << username;
        return nullptr;
    }
}



bool AllUsers::search(const QString& username) {
    QSqlDatabase db = getDatabaseConnection();
    if (!db.isOpen()) {
        qDebug() << "Error: Database is not open";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM userInfo WHERE username = :username");
    query.bindValue(":username", username);

    if (!query.exec()) {
        qDebug() << "Error: Unable to execute search query";
        qDebug() << query.lastError().text();
        return false;
    }

    query.next();
    int count = query.value(0).toInt();
    return (count > 0);
}

QSqlDatabase AllUsers::getDatabaseConnection() {
    if (!db.isOpen()) {
        initializeDatabase();
    }
    return db;
}

void AllUsers::updateScore(User* loggedUser, int newScore) {
    if (!loggedUser) {
        qDebug() << "Error: Logged user is null";
        return;
    }

    qDebug() << "Entered update";
    QString username = loggedUser->username;
    qDebug() << "Username: " << username; // Print the username parameter

    QSqlDatabase db = getDatabaseConnection();
    if (!db.isOpen()) {
        qDebug() << "Error: Database is not open";
        return;
    } else {
        qDebug() << "Database connection is open"; // Add this line
    }

    QSqlQuery query(db);

    if (!query.prepare("UPDATE userInfo SET score = :score WHERE username = :username")) {
        qDebug() << "Error preparing update query";
        qDebug() << query.lastError().text();
        return;
    } else {
        qDebug() << "Update query prepared successfully"; // Add this line
    }

    query.bindValue(":score", newScore);
    query.bindValue(":username", username);

    if (!query.exec()) {
        qDebug() << "Error: Unable to update user score";
        qDebug() << query.lastError().text();
    } else {
        qDebug() << "User score updated successfully for user: " << username;
    }
}

