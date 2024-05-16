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

bool AllUsers::authenticateUser(const QString &username, const QString &password) {
    QSqlDatabase db = getDatabaseConnection();
    if (!db.isOpen()) {
        qDebug() << "Error: Database is not open";
        return false;
    }

    QString hashedPass = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();
    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM userInfo WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", hashedPass);

    if (!query.exec()) {
        qDebug() << "Error: Unable to authenticate user";
        qDebug() << query.lastError().text();
        return false;
    }

    query.next();
    int count = query.value(0).toInt();
    return (count == 1);
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

void AllUsers::updateScore(const QString& username, int newScore) {
    QSqlDatabase db = getDatabaseConnection();
    if (!db.isOpen()) {
        qDebug() << "Error: Database is not open";
        return;
    }

    QSqlQuery query(db);
    query.prepare("UPDATE userInfo SET score = :score WHERE username = :username");
    query.bindValue(":score", newScore);
    query.bindValue(":username", username);

    if (!query.exec()) {
        qDebug() << "Error: Unable to update user score";
        qDebug() << query.lastError().text();
    } else {
        qDebug() << "User score updated successfully for user: " << username;
    }
}
