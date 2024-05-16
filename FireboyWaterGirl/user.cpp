#include "user.h"
#include "allusers.h"
#include <QDebug>

User::User(const QString& username, const QString& password) : username(username), password(password){
    score = 0;
}

void User::updateScore(int nScore){
    AllUsers::updateScore(username, nScore);
}

void User::newUser(const QString& username, const QString& password){
    AllUsers::addUser(username, password);
}

