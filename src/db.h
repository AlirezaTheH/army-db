#ifndef DB_H
#define DB_H

#include <QtSql>

#include "querydata.h"


class DB
{
public:
    static DB *instance();

private:
    DB();

    void init();
    void createAllTables();
    void seed();

public:
    QueryData query(const QString &query);
    void query_insert(const QString &table, QStringList values);

private:
    static DB *ins;
    QSqlDatabase database;
};

#endif // DB_H
