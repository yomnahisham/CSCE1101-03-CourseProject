#ifndef ALLUSERS_H
#define ALLUSERS_H

#include <QString>
#include <QSqlDatabase>

class AllUsers {
public:
    static void initializeDatabase();
    static void addUser(const QString& username, const QString& password);
    static void showLeaderboard();
    static bool authenticateUser(const QString &username, const QString &password);
    static bool search(const QString& username);

private:
    static QSqlDatabase getDatabaseConnection();
    static QSqlDatabase db;
};

#endif // ALLUSERS_H
