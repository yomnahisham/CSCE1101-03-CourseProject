#include "user.h"
#include "allusers.h"
#include <QDebug>

User::User(const QString& username, const QString& password) : username(username), password(password){
    score = 0;
}

User::User(const QString& username, const QString& password, const int& s): username(username), password(password), score(s){}

void User::newUser(const QString& username, const QString& password){
    AllUsers::addUser(username, password);
}

