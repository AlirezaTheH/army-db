#include "db.h"

#include <QFile>

#include "consts.h"

DB *DB::ins = new DB();


DB::DB():
    dropDatabase(true)
{
    init();
    if (dropDatabase)
    {
        createAllEntityTables();
        createAllRelationTables();
        seed();
    }
}

DB *DB::instance()
{
    return ins;
}


void DB::init()
{
    QString path = "army.sqlite";
    if (dropDatabase)
    {
        QFile dbfile(path);
        dbfile.remove();
    }
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(path);
    database.open();
}

void DB::createAllEntityTables()
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
        "is_natural boolean not null, "
        "health double not null, "
        "armor double not null, "
        "type integer not null, "
        "position_latitude double not null, "
        "position_longitude double not null, "
        "radius double not null, "
        "battlefield_fk integer not null, "
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
        "battlefield_fk integer not null, "
        "foreign key (battlefield_fk) references battlefields(id)"
        ")"
    );

    // create vehicles
    query(
        "create table if not exists vehicles ("
        "id integer primary key autoincrement not null, "
        "health double not null, "
        "armor double not null, "
        "type integer not null, "
        "position_latitude double not null, "
        "position_longitude double not null, "
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
        "name varchar(128) not null, "
        "force_type integer not null, "
        "size_type integer not null, "
        "position_latitude double not null, "
        "position_longitude double not null, "
        "radius double not null, "
        "vehicle_capacity integer not null, "
        "trooper_capacity integer not null, "
        "base_fk integer not null, "
        "commander_fk integer not null, "
        "foreign key (base_fk) references bases(id), "
        "foreign key (commander_fk) references troopers(id)"
        ")"
    );

    // create troopers
    query(
        "create table if not exists troopers ("
        "id integer primary key autoincrement not null, "
        "first_name varchar(128) not null, "
        "last_name varchar(128) not null, "
        "type integer not null, "
        "position_latitude double not null, "
        "position_longitude double not null, "
        "birth_datetime datetime not null, "
        "grade integer not null, "
        "health double not null, "
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
        "trooper_fk integer not null, "
        "foreign key (trooper_fk) references troopers(id), "
        "primary key (skill, trooper_fk)"
        ")"
    );

    // create ammo
    query(
        "create table if not exists ammo ("
        "id integer primary key autoincrement not null, "
        "name varchar(128) not null, "
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

    // create suits
    query(
        "create table if not exists suits ("
        "id integer primary key autoincrement not null, "
        "type integer not null, "
        "size integer not null, "
        "armor double not null, "
        "can_use boolean not null"
        ")"
    );
}


void DB::createAllRelationTables()
{
    // create base has vehicle
    query(
        "create table if not exists base_has_vehicle ("
        "base_fk integer not null, "
        "vehicle_fk integer not null, "
        "foreign key (base_fk) references bases(id), "
        "foreign key (vehicle_fk) references vehicles(id), "
        "primary key (base_fk, vehicle_fk)"
        ")"
    );

    // create base has suit
    query(
        "create table if not exists base_has_suit ("
        "base_fk integer not null, "
        "suit_fk integer not null, "
        "foreign key (base_fk) references bases(id), "
        "foreign key (suit_fk) references suits(id), "
        "primary key (base_fk, suit_fk)"
        ")"
    );

    // create army has trooper
    query(
        "create table if not exists army_has_trooper ("
        "army_fk integer not null, "
        "trooper_fk integer not null, "
        "foreign key (army_fk) references armies(id), "
        "foreign key (trooper_fk) references troopers(id), "
        "primary key (army_fk, trooper_fk)"
        ")"
    );

    // create army has vehicle
    query(
        "create table if not exists army_has_vehicle ("
        "army_fk integer not null, "
        "vehicle_fk integer not null, "
        "foreign key (army_fk) references armies(id), "
        "foreign key (vehicle_fk) references vehicles(id), "
        "primary key (army_fk, vehicle_fk)"
        ")"
    );

    // create army has weapon
    query(
        "create table if not exists army_has_weapon ("
        "army_fk integer not null, "
        "weapon_fk integer not null, "
        "foreign key (army_fk) references armies(id), "
        "foreign key (weapon_fk) references weapons(id), "
        "primary key (army_fk, weapon_fk)"
        ")"
    );

    // create army has ammo
    query(
        "create table if not exists army_has_ammo ("
        "army_fk integer not null, "
        "ammo_fk integer not null, "
        "foreign key (army_fk) references armies(id), "
        "foreign key (ammo_fk) references ammo(id), "
        "primary key (army_fk, ammo_fk)"
        ")"
    );

    // create trooper has suit
    query(
        "create table if not exists trooper_has_suit ("
        "trooper_fk integer not null, "
        "suit_fk integer not null, "
        "foreign key (trooper_fk) references troopers(id), "
        "foreign key (suit_fk) references suits(id), "
        "primary key (trooper_fk, suit_fk)"
        ")"
    );

    // weapon can use ammo
    query(
        "create table if not exists weapon_canuse_ammo ("
        "weapon_fk integer not null, "
        "ammo_fk integer not null, "
        "foreign key (weapon_fk) references weapons(id), "
        "foreign key (ammo_fk) references ammo(id), "
        "primary key (weapon_fk, ammo_fk)"
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

    // fortification
    for (int i = 0; i < 10; i++)
    {
        QStringList values;
        values.append(QString::number(i + 1));
        values.append(QString::number(i % 2 == 1));
        values.append(QString::number(55 + i * 3));
        values.append(QString::number(55 + i * 3));
        values.append(QString::number(i % FORTIFICATION_TYPES.size()));
        values.append(QString::number(((float) qrand() / RAND_MAX) + 26 + i));
        values.append(QString::number(((float) qrand() / RAND_MAX) + 45 + i));
        values.append(QString::number(100 + i));
        values.append(QString::number(qrand() % 10 + 1));
        query_insert("fortifications", values);
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

    // trooper
    for (int i = 0; i < 60; i++)
    {
        QStringList values;
        values.append(QString::number(i + 1));
        values.append("Trooper_FName_" + QString::number(i));
        values.append("Trooper_LName_" + QString::number(i));
        values.append(QString::number((i < 10) ? 0 : 1));
        values.append(QString::number(((float) qrand() / RAND_MAX) + 26 + (i % 10)));
        values.append(QString::number(((float) qrand() / RAND_MAX) + 45 + (i % 10)));
        values.append(QString("2018-04-11 19:0%1:00").arg((i % 10)));
        values.append(QString::number((i % 10) * 2 + 5));
        values.append(QString::number(55 + (i % 10) * 3));
        values.append(QString::number(80 + (i % 10) * 2));
        values.append(QString::number(1.6 + ((float) (i % 10) / 30.0)));
        values.append(QString::number(i % 2 == 1));
        values.append(QString::number((i % 10) / 2));
        query_insert("troopers", values);

        // trooper_skills
        for (int j = 0; j < 2; j++)
        {
            QStringList values;
            values.append(QString::number((i + j) % TROOPER_SKILLS.size()));
            values.append(QString::number(i + 1));
            query_insert("trooper_skills", values);
        }
    }

    // army
    for (int i = 0; i < 10; i++)
    {
        QStringList values;
        values.append(QString::number(i + 1));
        values.append("Army_" + QString::number(i));
        values.append(QString::number(i % ARMY_FORCE_TYPES.size()));
        values.append(QString::number(i % ARMY_SIZE_TYPES.size()));
        values.append(QString::number(((float) qrand() / RAND_MAX) + 26 + i));
        values.append(QString::number(((float) qrand() / RAND_MAX) + 45 + i));
        values.append(QString::number(100 + i));
        values.append(QString::number(i * 10 + 5));
        values.append(QString::number(i * 20 + 25));
        values.append(QString::number(qrand() % 10 + 1));
        values.append(QString::number(qrand() % 50 + 1));
        query_insert("armies", values);

        // army_has_trooper
        for (int j = 0; j < 5; j++)
        {
            QStringList values;
            values.append(QString::number(i + 1));
            values.append(QString::number(10 + i * 5 + j + 1));
            query_insert("army_has_trooper", values);
        }
    }

    // vehicle
    for (int i = 0; i < 60; i++)
    {
        QStringList values;
        values.append(QString::number(i + 1));
        values.append(QString::number(55 + (i % 10) * 3));
        values.append(QString::number(55 + (i % 10) * 3));
        values.append(QString::number(i % VEHICLE_TYPES.size()));
        values.append(QString::number(((float) qrand() / RAND_MAX) + 26 + (i % 10)));
        values.append(QString::number(((float) qrand() / RAND_MAX) + 45 + (i % 10)));
        values.append(QString::number(80 + (i % 10) * 7));
        values.append(QString::number(5 + (i % 10) * 1));
        values.append(QString::number((i % 10) % VEHICLE_FUEL_TYPES.size()));
        values.append(QString::number(25 + (i % 10) * 7));
        values.append(QString::number(5 + (i % 10)));
        values.append(QString::number(1 + (i % 10) * 1));
        query_insert("vehicles", values);

        // base has vehicle
        if (i < 30)
        {
            QStringList values;
            values.append(QString::number(i / 3 + 1));
            values.append(QString::number(i + 1));
            query_insert("base_has_vehicle", values);
        }
        else // army has vehicle
        {
            QStringList values;
            values.append(QString::number(i / 3 + 1 - 10));
            values.append(QString::number(i + 1));
            query_insert("army_has_vehicle", values);
        }
    }

    // suit
    for (int i = 0; i < 90; i++)
    {
        QStringList values;
        values.append(QString::number(i + 1));
        values.append(QString::number(i % SUIT_TYPES.size()));
        values.append(QString::number((i % 10)));
        values.append(QString::number(50 + (i % 10) * 3));
        values.append(QString::number((i < 30) ? 0 : 1));
        query_insert("suits", values);

        // base has suit
        if (i < 30)
        {
            QStringList values;
            values.append(QString::number(i / 3 + 1));
            values.append(QString::number(i + 1));
            query_insert("base_has_suit", values);
        }
        else // trooper has suit
        {
            QStringList values;
            values.append(QString::number(i - 30 + 1));
            values.append(QString::number(i + 1));
            query_insert("trooper_has_suit", values);
        }
    }

    // ammo
    for (int i = 0; i < 50; i++)
    {
        QStringList values;
        values.append(QString::number(i + 1));
        values.append("Ammo_Name_" + QString::number(i));
        values.append(QString::number(i % AMMO_TYPES.size()));
        values.append(QString::number(i % AMMO_SURFACE_MATERAIL.size()));
        values.append(QString::number(i % AMMO_EXPLOSION_MATERIAL.size()));
        values.append(QString::number(.2 + (i % 10) * 7));
        values.append(QString::number(17 + (i % 10) * 1));
        values.append(QString::number(.1 + (i % 10) * .1));
        values.append(QString::number(.1 + (i % 10) * .1));
        values.append(QString::number(.1 + (i % 10)));
        query_insert("ammo", values);

        // army_has_ammo
        {
            QStringList values;
            values.append(QString::number(i / 5 + 1));
            values.append(QString::number(i + 1));
            query_insert("army_has_ammo", values);
        }
    }
}


QueryData DB::query(const QString &query)
{
    QueryData result;
    for (auto singleQuery : query.split(";"))
    {
        QSqlQuery q(database);
        q.exec(singleQuery);

        if (q.lastError().type() != q.lastError().NoError)
        {
            qDebug() << "sql:" << q.lastError().text();
            result.error = q.lastError().text();
            return result;
        }

        result.columns.clear();
        for (int i = 0; i < q.record().count(); i++)
            result.columns.append(q.record().fieldName(i));

        result.rows.clear();
        while (q.next())
        {
            QVariantList values;
            for (int i = 0; i < q.record().count(); i++)
                values.append(q.record().value(i));
            result.rows.append(values);
        }
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
