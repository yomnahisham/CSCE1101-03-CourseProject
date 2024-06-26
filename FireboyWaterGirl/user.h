#ifndef USER_H
#define USER_H

#include <QString>
#include <QtSql>

class User {
public:
    User(const QString& username, const QString& password);
    User(const QString& username, const QString& password, const int& s);
    static void newUser(const QString& username, const QString& password);
    QString username;

private:
    QString password;
    int score;
};

#endif // USER_H
