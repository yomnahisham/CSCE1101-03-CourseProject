#include "User.h"
#include <QDebug>

User::User(const QString& username, const QString& password, int score) : username(username), password(password), score(0) {}

void User::updateScore(int nScore) {
    QSqlQuery query;
    query.prepare("UPDATE users SET score = :score WHERE username = :username");
    query.bindValue(":score", nScore);
    query.bindValue(":username", username);

    if (!query.exec()) {
        qDebug() << "Error: Unable to update score";
    }
}

void User::newUser(const QString &username, const QString &password, int score){
    AllUsers all;
    all.addUser(username, password, score);
}
