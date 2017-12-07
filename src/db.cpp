#include "db.h"

DB *DB::ins = new DB();


DB::DB()
{
    init();
    createAllTables();
    seed();
}

DB *DB::instance()
{
    return ins;
}


void DB::init()
{
    QString path = "army.sqlite";
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(path);
    database.open();
}

void DB::createAllTables()
{
    // create battlefield
    query(
        "create table if not exists battlefields ("
        "id integer primary key autoincrement not null, "
        "position_latitude double not null, "
        "position_longitude double not null, "
        "radius double not null, "
        "start_datetime datetime not null, "
        "end_datetime datetime not null "
        ")"
    );

    // createa base
    query(
        "create table if not exists bases ("
        "id integer primary key autoincrement not null, "
        "name varchar(128) not null, "
        "position_latitude double not null, "
        "position_longitude double not null, "
        "radius double not null, "
        "vehicle_capacity integer not null, "
        "soldier_capacity integer not null "
        ")"
    );
}

void DB::seed()
{
    // battlefield
    for (int i = 0; i < 10; i++)
    {
        QStringList values;
        values.append(QString::number(i + 1));
        values.append(QString::number(((float) qrand() / RAND_MAX) + 26 + i));
        values.append(QString::number(((float) qrand() / RAND_MAX) + 45 + i));
        values.append(QString::number(100 + i));
        values.append(QString("2018-04-11 19:0%1:00").arg(i));
        values.append(QString("2018-09-13 19:0%1:00").arg(i));

        query_insert("battlefields", values);
    }

    // base
    for (int i = 0; i < 10; i++)
    {
        QStringList values;
        values.append(QString::number(i + 1));
        values.append("Base_" + QString::number(i));
        values.append(QString::number(((float) qrand() / RAND_MAX) + 26 + i));
        values.append(QString::number(((float) qrand() / RAND_MAX) + 45 + i));
        values.append(QString::number(100 + i));
        values.append(QString::number(i * 10 + 5));
        values.append(QString::number(i * 20 + 25));

        query_insert("bases", values);
    }
}


QueryData DB::query(const QString &query)
{
    QueryData result;

    QSqlQuery q;
    q.exec(query);

    if (q.lastError().type() != q.lastError().NoError)
    {
        qDebug() << "sql:" << q.lastError().text();
        result.error = q.lastError().text();
        return result;
    }

    for (int i = 0; i < q.record().count(); i++)
        result.columns.append(q.record().fieldName(i));

    while (q.next())
    {
        QVariantList values;
        for (int i = 0; i < q.record().count(); i++)
            values.append(q.record().value(i));
        result.rows.append(values);
    }

    return result;
}


void DB::query_insert(const QString &table, QStringList values)
{
    for (int i = 0; i < values.size(); i++)
        if (values[i].toUpper() != "NULL")
            values[i] = "'" + values[i] + "'";

    query(QString(
        "insert into %1 values (%2)"
    ).arg(table, values.join(", ")));
}
