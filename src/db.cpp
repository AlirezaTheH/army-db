#include "db.h"

#include <QFile>

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
    QFile dbfile(path);
    dbfile.remove();
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(path);
    database.open();
}

void DB::createAllTables()
{
    // create battlefields
    query(
        "create table if not exists battlefields ("
        "id integer primary key autoincrement not null, "
        "position_latitude double not null, "
        "position_longitude double not null, "
        "radius double not null, "
        "start_datetime datetime not null, "
        "end_datetime datetime not null"
        ")"
    );

    // create fortifications
    query(
        "create table if not exists fortifications ("
        "id integer primary key autoincrement not null, "
        "type integer not null, "
        "is_natural boolean not null, "
        "position_latitude double not null, "
        "position_longitude double not null, "
        "radius double not null, "
        "health double not null, "
        "armor double not null, "
        "battlefield_fk integer, "
        "foreign key (battlefield_fk) references battlefields(id)"
        ")"
    );

    // create bases
    query(
        "create table if not exists bases ("
        "id integer primary key autoincrement not null, "
        "name varchar(128) not null, "
        "position_latitude double not null, "
        "position_longitude double not null, "
        "radius double not null, "
        "vehicle_capacity integer not null, "
        "trooper_capacity integer not null, "
        "battlefield_fk integer, "
        "foreign key (battlefield_fk) references battlefields(id)"
        ")"
    );

    // create vehicles
    query(
        "create table if not exists vehicles ("
        "id integer primary key autoincrement not null, "
        "type integer not null, "
        "position_latitude double not null, "
        "position_longitude double not null, "
        "health double not null, "
        "armor double not null, "
        "max_speed integer not null, "
        "max_acceleration integer not null, "
        "fuel_type integer not null, "
        "fuel_max_capacity integer not null, "
        "fuel_consuming_unit integer not null, "
        "max_passengers integer not null"
        ")"
    );

    // create armies
    query(
        "create table if not exists armies ("
        "id integer primary key autoincrement not null, "
        "force_type integer not null, "
        "size_type integer not null, "
        "position_latitude double not null, "
        "position_longitude double not null, "
        "radius double not null, "
        "vehicle_capacity integer not null, "
        "trooper_capacity integer not null"
        ")"
    );

    // create troopers
    query(
        "create table if not exists troopers ("
        "id integer primary key autoincrement not null, "
        "last_name varchar(128) not null, "
        "first_name varchar(128) not null, "
        "type integer not null, "
        "position_latitude double not null, "
        "position_longitude double not null, "
        "health double not null, "
        "grade integer not null, "
        "birth_datetime datetime not null, "
        "weight double not null, "
        "height double not null, "
        "is_single boolean not null, "
        "children_count integer not null"
        ")"
    );

    // create trooper skills
    query(
        "create table if not exists trooper_skills ("
        "skill integer not null, "
        "trooper_fk integer, "
        "foreign key (trooper_fk) references troopers(id), "
        "primary key (skill, trooper_fk)"
        ")"
    );

    // create ammo
    query(
        "create table if not exists ammo ("
        "id integer primary key autoincrement not null, "
        "type integer not null, "
        "surface_material integer not null, "
        "explosion_material integer not null, "
        "weight double not null, "
        "count integer not null, "
        "width double not null, "
        "length double not null, "
        "height double not null"
        ")"
    );

    // create weapons
    query(
        "create table if not exists weapons ("
        "id integer primary key autoincrement not null, "
        "name varchar(128) not null, "
        "type integer not null, "
        "model integer not null, "
        "weight double not null, "
        "count integer not null, "
        "width double not null, "
        "length double not null, "
        "height double not null, "
        "fire_speed integer not null, "
        "max_range double not null, "
        "average_realod_time double not null, "
        "magazine_size integer not null"
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
        values.append(QString::number(qrand() % 10 + 1));
        query_insert("bases", values);
    }
}


QueryData DB::query(const QString &query)
{
    QueryData result;

    QSqlQuery q(database);
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
