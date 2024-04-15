#include "allusers.h"
#include "user.h"
#include <QDebug>
#include <QCryptographicHash>

AllUsers::AllUsers() {
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306); // MySQL port
    db.setDatabaseName("CSCE1101-03-CourseProject-Database");
    db.setUserName("root");
    db.setPassword("yomnahisham");

    if (!db.open()) {
        qDebug() << "Error: Unable to open database";
    }

    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS users (id INT AUTO_INCREMENT PRIMARY KEY, username VARCHAR(255), password VARCHAR(255), score INT)")) {
        qDebug() << "Error: Unable to create users table";
    }
}

void AllUsers::addUser(const QString& username, const QString& password, int score){
    QSqlQuery query;
    QString hashedPass = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();
    query.prepare("INSERT INTO users (username, password, score) VALUES (:username, :password, :score)");
    query.bindValue(":username", username);
    query.bindValue(":password", hashedPass);
    query.bindValue(":score", score);

    if (!query.exec()) {
        qDebug() << "Error: Unable to add user";
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
    QSqlQuery query;
    QString hashedPass = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();
    query.prepare("SELECT COUNT(*) FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", hashedPass);

    if(!query.exec()){
        qDebug() << "Error: Unable to authenticate user";
        return false;
    }

    query.next();
    int count = query.value(0).toInt();
    return count > 0;
}
