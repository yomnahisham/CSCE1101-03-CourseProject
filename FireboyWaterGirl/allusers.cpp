#include "allusers.h"
#include "user.h"
#include <QDebug>
#include <fstream>
#include <string>
#include <QCryptographicHash>

using namespace std;

AllUsers::AllUsers() {
    string filePath = "Assets/password.txt";
    string password;

    ifstream file(filePath);
    if (file.is_open()) {
        // Read the password from the file
        getline(file, password);
        file.close();
    } else {
        qDebug() << "Error: Unable to open password file";
    }
    QString qPassword = QString::fromStdString(password);

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306); // MySQL port
    db.setDatabaseName("CSCE1101-03-CourseProject-Database");
    db.setUserName("root");
    db.setPassword(qPassword);

    if (!db.open()) {
        qDebug() << "Error: Unable to open database";
    }

    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS users (username VARCHAR(255) PRIMARY KEY, password VARCHAR(255), score INT)")) {
        qDebug() << "Error: Unable to create users table";
    }
}


void AllUsers::addUser(const QString& username, const QString& password){
    QSqlQuery query;

    // using QCryptographicHash to ensure security of passwords in Database
    QString hashedPass = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();
    query.prepare("INSERT INTO users (username, password, score) VALUES (:username, :password, :score)");
    query.bindValue(":username", username);
    query.bindValue(":password", hashedPass);
    query.bindValue(":score", 0);

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
    return (count == 1);
}

bool AllUsers::search(const QString& username){
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM users WHERE username = :username");
    query.bindValue(":username", username);

    if (!query.exec()) {
        qDebug() << "Error: Unable to execute search query";
        return false;
    }

    query.next();
    int count = query.value(0).toInt();
    return (count > 0);
}

