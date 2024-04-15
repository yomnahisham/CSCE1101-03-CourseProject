#ifndef ALLUSERS_H
#define ALLUSERS_H

#include <QtSql>
//#include "user.h"

class AllUsers{
public:
    AllUsers();
    static void addUser(const QString& username, const QString& password, int score);
    void showLeaderboard();
    bool authenticateUser(const QString& username, const QString& password);

private:
    QSqlDatabase db;
};

#endif // ALLUSERS_H
