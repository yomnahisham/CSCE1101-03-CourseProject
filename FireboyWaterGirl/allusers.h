#ifndef ALLUSERS_H
#define ALLUSERS_H
#include "user.h"
#include <QString>
#include <QSqlDatabase>

class AllUsers {
public:
    AllUsers();
    static void initializeDatabase();
    static void addUser(const QString& username, const QString& password);
    static void showLeaderboard();
    static User* authenticateUser(const QString &username, const QString &password);
    static bool search(const QString& username);
    static void updateScore(User* loggedUser, int newScore);
    static QSqlDatabase getDatabaseConnection();

private:
    static QSqlDatabase db;
    static QString getDatabasePath();
};

#endif // ALLUSERS_H
