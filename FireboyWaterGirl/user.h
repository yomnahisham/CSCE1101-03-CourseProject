#ifndef USER_H
#define USER_H

#include <QString>
#include <QtSql>

class User {
public:
    User(const QString& username, const QString& password);
    void updateScore(int nScore);
    void newUser(const QString& username, const QString& password, int score);

private:
    QString username;
    QString password;
    int score;
};

#endif // USER_H
