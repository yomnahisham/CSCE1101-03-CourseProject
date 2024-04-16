#ifndef USER_H
#define USER_H

#include <QString>
#include <QtSql>

class User {
public:
    User(const QString& username, const QString& password);
    void updateScore(int nScore);
    static void newUser(const QString& username, const QString& password);

private:
    QString username;
    QString password;
    int score;
};

#endif // USER_H
