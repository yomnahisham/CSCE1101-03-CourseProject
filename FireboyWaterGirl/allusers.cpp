#include "allusers.h"
#include "user.h"

#include <QDebug>
#include <fstream>
#include <QString>
#include <QCryptographicHash>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>

AllUsers::AllUsers() {
    // establish connection to SQLite database
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("fireboywatergirl.db"); // SQLite database file
    if (!db.open()) {
        qDebug() << "Error: Unable to open database";
        qDebug() << db.lastError().text();
        return;
    }

    // create users table if it does not exist
    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS users (username VARCHAR(255) PRIMARY KEY, password VARCHAR(255), score INT)")) {
        qDebug() << "Error: Unable to create users table";
        qDebug() << query.lastError().text();
    }
}

void AllUsers::addUser(const QString& username, const QString& password){
    // using QCryptographicHash to ensure security of passwords in Database
    QString hashedPass = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();

    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password, score) VALUES (:username, :password, :score)");
    query.bindValue(":username", username);
    query.bindValue(":password", hashedPass);
    query.bindValue(":score", 0);

    if (!query.exec()) {
        qDebug() << "Error: Unable to add user";
        qDebug() << query.lastError().text();
    }
}

void AllUsers::showLeaderboard() {
    QSqlQuery query("SELECT username, score FROM users ORDER BY score DESC LIMIT 10");
    while (query.next()) {
        QString username = query.value(0).toString();
        int score = query.value(1).toInt();
        qDebug() << "Username:" << username << "Score:" << score;
    }
}

bool AllUsers::authenticateUser(const QString &username, const QString &password){
    QString hashedPass = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", hashedPass);

    if(!query.exec()){
        qDebug() << "Error: Unable to authenticate user";
        qDebug() << query.lastError().text();
        return false;
    }

    query.next();
    int count = query.value(0).toInt();
    return (count == 1);
}

bool AllUsers::search(const QString& username){
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM users WHERE username = :username");
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

