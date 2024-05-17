#include "user.h"
#include "allusers.h"
#include <QDebug>

User::User(const QString& username, const QString& password) : username(username), password(password){
    score = 0; // constrcutor- initializes everything and puts initial score to 0
}

// constructor with different parameter, made for all users authentication
User::User(const QString& username, const QString& password, const int& s): username(username), password(password), score(s){}


// adds new user to the db
void User::newUser(const QString& username, const QString& password){
    AllUsers::addUser(username, password);
}

