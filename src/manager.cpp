#include "manager.h"

#include <QtCore>
#include <random>

#include "consts.h"
#include "global_storage.h"
#include "roles.h"
#include "info_dialog.h"
#include "query_dialog.h"


Manager::Manager()
{
}

void Manager::exec()
{
    // TODO: Add a mainwindow and move QueryDialog to mainwindow
    if (GlobalStorage::instance()->get<int>(USER_ROLE) == Roles::Admin)
    {
        QueryDialog queryDialog;
        queryDialog.exec();
    }

    actionsHistory.push_back(Action(ActionType::ShowBattlefields));
    Action action;

    while (!actionsHistory.empty())
    {
        action = actionsHistory.back();
        currentAction = action;
        if (action.type() == ActionType::None)
        {
            actionsHistory.pop_back();
            actionsHistory.pop_back();
            continue;
        }

        switch (action.type()) {
            case ActionType::ShowBattlefields:
                action = execBattlefieldsWindow();
                break;
            case ActionType::ShowBases:
                action = execBasesWindow();
                break;
            case ActionType::ShowArmies:
                action = execArmiesWindow();
                break;
            case ActionType::ShowTroopers:
                action = execTroopersWindow();
                break;
            case ActionType::ShowTrooperSkills:
                action = execTrooperSkillsWindow();
                break;
            case ActionType::ShowFortifications:
                action = execFortificationsWindow();
                break;
            case ActionType::ShowVehicles:
                action = execVehiclesWindow();
                break;
            case ActionType::ShowAmmo:
                action = execAmmoWindow();
                break;
            case ActionType::ShowWeapons:
                action = execWeaponsWindow();
                break;
            case ActionType::ShowSuits:
                action = execSuitsWindow();
                break;
            default:
                break;
        }

        actionsHistory.push_back(action);
    }
}


Action Manager::execBattlefieldsWindow()
{
    QList<Item> columns;

    // position latitude
    Item positionLatitude = itemFactory.createReal("position_latitude", 30);
    positionLatitude.setProperty(LIMIT_MINIMUM, true);
    positionLatitude.setProperty(MINIMUM, 25.2919f);
    positionLatitude.setProperty(LIMIT_MAXIMUM, true);
    positionLatitude.setProperty(MAXIMUM, 39.6482f);

    // position longitude
    Item positionLongitude = itemFactory.createReal("position_longitude", 50);
    positionLongitude.setProperty(LIMIT_MINIMUM, true);
    positionLongitude.setProperty(MINIMUM, 44.7653f);
    positionLongitude.setProperty(LIMIT_MAXIMUM, true);
    positionLongitude.setProperty(MAXIMUM, 61.4949f);

    // radius
    Item radius = itemFactory.createReal("radius", 1000);
    radius.setProperty(LIMIT_MINIMUM, true);
    radius.setProperty(MINIMUM, 100);
    radius.setProperty(LIMIT_MAXIMUM, true);
    radius.setProperty(MAXIMUM, 20000);

    // start datetime
    Item startDatetime = itemFactory.createString("start_datetime", "2018-02-12 23:43");
    startDatetime.setProperty(ALLOW_NULL, false);
    startDatetime.setProperty(MINIMUM_LENGTH, -1);
    startDatetime.setProperty(MAXIMUM_LENGTH, -1);
    startDatetime.setProperty(PATTERN, DATETIME_PATTERN);

    // end datetime
    Item endDatetime = itemFactory.createString("end_datetime", "2018-04-12 23:43");
    endDatetime.setProperty(ALLOW_NULL, false);
    endDatetime.setProperty(MINIMUM_LENGTH, -1);
    endDatetime.setProperty(MAXIMUM_LENGTH, -1);
    endDatetime.setProperty(PATTERN, DATETIME_PATTERN);

    columns.append(positionLatitude);
    columns.append(positionLongitude);
    columns.append(radius);
    columns.append(startDatetime);
    columns.append(endDatetime);

    QString viewQuery = ""
        "select id, position_latitude, position_longitude, radius, start_datetime, end_datetime "
        "from battlefields"
        "";

    QString insertQuery = ""
        "insert into battlefields "
        "(id, position_latitude, position_longitude, radius, start_datetime, end_datetime) "
        "values(NULL, %1)"
        "";

    QString updateQuery = ""
        "replace into battlefields "
        "(id, position_latitude, position_longitude, radius, start_datetime, end_datetime) "
        "values(%1, %2)"
        "";

    QString deleteQuery = "delete from battlefields where id=%1";

    InfoDialog battleFieldsInfo("BattleField", columns, viewQuery, insertQuery, updateQuery, deleteQuery,
        QList<Action>({Action(ActionType::ShowBases), Action(ActionType::ShowFortifications)}));
    battleFieldsInfo.exec();
    Action selectedAction = battleFieldsInfo.getSelectedAction();
    return selectedAction;
}


Action Manager::execBasesWindow()
{
    QList<Item> columns;

    // name
    Item name = itemFactory.createString("name", "Base_0");
    name.setProperty(ALLOW_NULL, false);
    name.setProperty(MINIMUM_LENGTH, -1);
    name.setProperty(MAXIMUM_LENGTH, -1);
    name.setProperty(PATTERN, "");

    // position latitude
    Item positionLatitude = itemFactory.createReal("position_latitude", 30);
    positionLatitude.setProperty(LIMIT_MINIMUM, true);
    positionLatitude.setProperty(MINIMUM, 25.2919f);
    positionLatitude.setProperty(LIMIT_MAXIMUM, true);
    positionLatitude.setProperty(MAXIMUM, 39.6482f);

    // position longitude
    Item positionLongitude = itemFactory.createReal("position_longitude", 50);
    positionLongitude.setProperty(LIMIT_MINIMUM, true);
    positionLongitude.setProperty(MINIMUM, 44.7653f);
    positionLongitude.setProperty(LIMIT_MAXIMUM, true);
    positionLongitude.setProperty(MAXIMUM, 61.4949f);

    // radius
    Item radius = itemFactory.createReal("radius", 1000);
    radius.setProperty(LIMIT_MINIMUM, true);
    radius.setProperty(MINIMUM, 100);
    radius.setProperty(LIMIT_MAXIMUM, true);
    radius.setProperty(MAXIMUM, 20000);

    // vehicle capacity
    Item vehicleCapacity = itemFactory.createInteger("vehicle_capacity", 100);
    vehicleCapacity.setProperty(LIMIT_MINIMUM, true);
    vehicleCapacity.setProperty(MINIMUM, 0);
    vehicleCapacity.setProperty(LIMIT_MAXIMUM, true);
    vehicleCapacity.setProperty(MAXIMUM, 200);

    // trooper capacity
    Item trooperCapacity = itemFactory.createInteger("trooper_capacity", 200);
    trooperCapacity.setProperty(LIMIT_MINIMUM, true);
    trooperCapacity.setProperty(MINIMUM, 0);
    trooperCapacity.setProperty(LIMIT_MAXIMUM, true);
    trooperCapacity.setProperty(MAXIMUM, 500);


    columns.append(name);
    columns.append(positionLatitude);
    columns.append(positionLongitude);
    columns.append(radius);
    columns.append(vehicleCapacity);
    columns.append(trooperCapacity);

    QString viewQuery = QString(""
        "select id, name, position_latitude, position_longitude, radius, vehicle_capacity, trooper_capacity "
        "from bases "
        "where battlefield_fk=%1"
        "").arg(currentAction.id());


    QString insertQuery = QString(""
        "insert into bases "
        "(id, name, position_latitude, position_longitude, radius, vehicle_capacity, trooper_capacity, battlefield_fk) "
        "values(NULL, %1, %2)"
        "").arg("%1", currentAction.id());

    QString updateQuery = QString(""
        "replace into bases "
        "(id, name, position_latitude, position_longitude, radius, vehicle_capacity, trooper_capacity, battlefield_fk) "
        "values(%1, %2, %3)"
        "").arg("%1", "%2", currentAction.id());

    QString deleteQuery = "delete from bases where id=%1";

    InfoDialog basesInfo("Base", columns, viewQuery, insertQuery, updateQuery, deleteQuery,
        QList<Action>({Action(ActionType::ShowArmies), Action(ActionType::ShowVehicles), Action(ActionType::ShowSuits)}));
    basesInfo.exec();
    Action selectedAction = basesInfo.getSelectedAction();
    return selectedAction;
}


Action Manager::execArmiesWindow()
{
    QList<Item> columns;
    QList<QList<QVariant>> rows;

    // name
    Item name = itemFactory.createString("name", "Army_0");
    name.setProperty(ALLOW_NULL, false);
    name.setProperty(MINIMUM_LENGTH, -1);
    name.setProperty(MAXIMUM_LENGTH, -1);
    name.setProperty(PATTERN, "");

    // force type
    Item forceType = itemFactory.createEnum("force_type", ARMY_FORCE_TYPES, 0);

    // size type
    Item sizeType = itemFactory.createEnum("size_type", ARMY_SIZE_TYPES, 0);

    // position latitude
    Item positionLatitude = itemFactory.createReal("position_latitude", 30);
    positionLatitude.setProperty(LIMIT_MINIMUM, true);
    positionLatitude.setProperty(MINIMUM, 25.2919f);
    positionLatitude.setProperty(LIMIT_MAXIMUM, true);
    positionLatitude.setProperty(MAXIMUM, 39.6482f);

    // position longitude
    Item positionLongitude = itemFactory.createReal("position_longitude", 50);
    positionLongitude.setProperty(LIMIT_MINIMUM, true);
    positionLongitude.setProperty(MINIMUM, 44.7653f);
    positionLongitude.setProperty(LIMIT_MAXIMUM, true);
    positionLongitude.setProperty(MAXIMUM, 61.4949f);

    // radius
    Item radius = itemFactory.createReal("radius", 1000);
    radius.setProperty(LIMIT_MINIMUM, true);
    radius.setProperty(MINIMUM, 100);
    radius.setProperty(LIMIT_MAXIMUM, true);
    radius.setProperty(MAXIMUM, 20000);

    // vehicle capacity
    Item vehicleCapacity = itemFactory.createInteger("vehicle_capacity", 100);
    vehicleCapacity.setProperty(LIMIT_MINIMUM, true);
    vehicleCapacity.setProperty(MINIMUM, 0);
    vehicleCapacity.setProperty(LIMIT_MAXIMUM, true);
    vehicleCapacity.setProperty(MAXIMUM, 200);

    // trooper capacity
    Item trooperCapacity = itemFactory.createInteger("trooper_capacity", 200);
    trooperCapacity.setProperty(LIMIT_MINIMUM, true);
    trooperCapacity.setProperty(MINIMUM, 0);
    trooperCapacity.setProperty(LIMIT_MAXIMUM, true);
    trooperCapacity.setProperty(MAXIMUM, 500);


    columns.append(name);
    columns.append(forceType);
    columns.append(sizeType);
    columns.append(positionLatitude);
    columns.append(positionLongitude);
    columns.append(radius);
    columns.append(vehicleCapacity);
    columns.append(trooperCapacity);

    for (int i = 0; i < 10; i++)
    {
        QList<QVariant> items;
        items.append("Army_" + QString::number(i));
        items.append(ARMY_FORCE_TYPES[i % ARMY_FORCE_TYPES.size()]);
        items.append(ARMY_SIZE_TYPES[i % ARMY_SIZE_TYPES.size()]);
        items.append(QString::number(((float) qrand() / RAND_MAX) + 26 + i).toDouble());
        items.append(QString::number(((float) qrand() / RAND_MAX) + 45 + i).toDouble());
        items.append(100 + i);
        items.append(i * 10 + 5);
        items.append(i * 20 + 25);
        rows.append(items);
    }

    InfoDialog armiesInfo("Army", columns, rows, QList<Action>({Action(ActionType::ShowTroopers),
                                                                Action(ActionType::ShowVehicles),
                                                                Action(ActionType::ShowAmmo),
                                                                Action(ActionType::ShowWeapons)}));
    armiesInfo.exec();
    Action selectedAction = armiesInfo.getSelectedAction();
    return selectedAction;
}

Action Manager::execTroopersWindow()
{
    QList<Item> columns;
    QList<QList<QVariant>> rows;

    // first name
    Item firstName = itemFactory.createString("first_name", "FirstName_0");
    firstName.setProperty(ALLOW_NULL, false);
    firstName.setProperty(MINIMUM_LENGTH, -1);
    firstName.setProperty(MAXIMUM_LENGTH, -1);
    firstName.setProperty(PATTERN, "");

    // last name
    Item lastName = itemFactory.createString("last_name", "LastName_0");
    lastName.setProperty(ALLOW_NULL, false);
    lastName.setProperty(MINIMUM_LENGTH, -1);
    lastName.setProperty(MAXIMUM_LENGTH, -1);
    lastName.setProperty(PATTERN, "");

    // type
    Item type = itemFactory.createEnum("type", TROOPER_TYPES, 0);

    // position latitude
    Item positionLatitude = itemFactory.createReal("position_latitude", 30);
    positionLatitude.setProperty(LIMIT_MINIMUM, true);
    positionLatitude.setProperty(MINIMUM, 25.2919f);
    positionLatitude.setProperty(LIMIT_MAXIMUM, true);
    positionLatitude.setProperty(MAXIMUM, 39.6482f);

    // position longitude
    Item positionLongitude = itemFactory.createReal("position_longitude", 50);
    positionLongitude.setProperty(LIMIT_MINIMUM, true);
    positionLongitude.setProperty(MINIMUM, 44.7653f);
    positionLongitude.setProperty(LIMIT_MAXIMUM, true);
    positionLongitude.setProperty(MAXIMUM, 61.4949f);

    // birth datetime
    Item birthDatetime = itemFactory.createString("birth_datetime", "2018-02-12 23:43");
    birthDatetime.setProperty(ALLOW_NULL, false);
    birthDatetime.setProperty(MINIMUM_LENGTH, -1);
    birthDatetime.setProperty(MAXIMUM_LENGTH, -1);
    birthDatetime.setProperty(PATTERN, DATETIME_PATTERN);

    // grade
    Item grade = itemFactory.createInteger("grade", 0);
    grade.setProperty(LIMIT_MINIMUM, true);
    grade.setProperty(MINIMUM, 0);
    grade.setProperty(LIMIT_MAXIMUM, true);
    grade.setProperty(MAXIMUM, 30);

    // health
    Item health = itemFactory.createReal("health", 100);
    health.setProperty(LIMIT_MINIMUM, true);
    health.setProperty(MINIMUM, 0);
    health.setProperty(LIMIT_MAXIMUM, true);
    health.setProperty(MAXIMUM, 100);

    // weight
    Item weight = itemFactory.createReal("weight", 75);
    weight.setProperty(LIMIT_MINIMUM, true);
    weight.setProperty(MINIMUM, 50);
    weight.setProperty(LIMIT_MAXIMUM, true);
    weight.setProperty(MAXIMUM, 200);

    // height
    Item height = itemFactory.createReal("height", 1.75);
    height.setProperty(LIMIT_MINIMUM, true);
    height.setProperty(MINIMUM, 1.5);
    height.setProperty(LIMIT_MAXIMUM, true);
    height.setProperty(MAXIMUM, 2.5);

    // is single
    Item isSingle = itemFactory.createBoolean("is_single", true);

    // children count
    Item childrenCount = itemFactory.createInteger("children_count", 0);
    childrenCount.setProperty(LIMIT_MINIMUM, true);
    childrenCount.setProperty(MINIMUM, 0);
    childrenCount.setProperty(LIMIT_MAXIMUM, true);
    childrenCount.setProperty(MAXIMUM, 10);


    columns.append(firstName);
    columns.append(lastName);
    columns.append(type);
    columns.append(positionLatitude);
    columns.append(positionLongitude);
    columns.append(birthDatetime);
    columns.append(grade);
    columns.append(health);
    columns.append(weight);
    columns.append(height);
    columns.append(isSingle);
    columns.append(childrenCount);

    for (int i = 0; i < 10; i++)
    {
        QList<QVariant> items;
        items.append("Trooper_FName_" + QString::number(i));
        items.append("Trooper_LName_" + QString::number(i));
        items.append(TROOPER_TYPES[i % TROOPER_TYPES.size()]);
        items.append(QString::number(((float) qrand() / RAND_MAX) + 26 + i).toDouble());
        items.append(QString::number(((float) qrand() / RAND_MAX) + 45 + i).toDouble());
        items.append(QString("2018-04-11 19:0%1").arg(i));
        items.append(i * 2 + 5);
        items.append(55 + i * 3);
        items.append(80 + i * 2);
        items.append(1.6 + ((float) i / 30.0));
        items.append(i % 2 == 1);
        items.append(i / 2);
        rows.append(items);
    }

    InfoDialog troopersInfo("Trooper", columns, rows, QList<Action>({Action(ActionType::ShowTrooperSkills)}));
    troopersInfo.exec();
    Action selectedAction = troopersInfo.getSelectedAction();
    return selectedAction;
}


Action Manager::execTrooperSkillsWindow()
{
    QList<Item> columns;
    QList<QList<QVariant>> rows;

    // skill
    Item skill = itemFactory.createEnum("skill", TROOPER_SKILLS, 0);


    columns.append(skill);

    for (int i = 0; i < 3; i++)
    {
        QList<QVariant> items;
        items.append(TROOPER_SKILLS[i % TROOPER_SKILLS.size()]);
        rows.append(items);
    }

    InfoDialog trooperSkillsInfo("Trooper Skill", columns, rows, QList<Action>({}));
    trooperSkillsInfo.exec();
    Action selectedAction = trooperSkillsInfo.getSelectedAction();
    return selectedAction;
}


Action Manager::execFortificationsWindow()
{
    QList<Item> columns;

    // is natural
    Item isNatural = itemFactory.createBoolean("is_natural", true);

    // health
    Item health = itemFactory.createReal("health", 100);
    health.setProperty(LIMIT_MINIMUM, true);
    health.setProperty(MINIMUM, 0);
    health.setProperty(LIMIT_MAXIMUM, true);
    health.setProperty(MAXIMUM, 100);

    // armor
    Item armor = itemFactory.createReal("armor", 100);
    armor.setProperty(LIMIT_MINIMUM, true);
    armor.setProperty(MINIMUM, 0);
    armor.setProperty(LIMIT_MAXIMUM, true);
    armor.setProperty(MAXIMUM, 100);

    // type
    Item type = itemFactory.createEnum("type", FORTIFICATION_TYPES, 0);

    // position latitude
    Item positionLatitude = itemFactory.createReal("position_latitude", 30);
    positionLatitude.setProperty(LIMIT_MINIMUM, true);
    positionLatitude.setProperty(MINIMUM, 25.2919f);
    positionLatitude.setProperty(LIMIT_MAXIMUM, true);
    positionLatitude.setProperty(MAXIMUM, 39.6482f);

    // position longitude
    Item positionLongitude = itemFactory.createReal("position_longitude", 50);
    positionLongitude.setProperty(LIMIT_MINIMUM, true);
    positionLongitude.setProperty(MINIMUM, 44.7653f);
    positionLongitude.setProperty(LIMIT_MAXIMUM, true);
    positionLongitude.setProperty(MAXIMUM, 61.4949f);

    // radius
    Item radius = itemFactory.createReal("radius", 1000);
    radius.setProperty(LIMIT_MINIMUM, true);
    radius.setProperty(MINIMUM, 100);
    radius.setProperty(LIMIT_MAXIMUM, true);
    radius.setProperty(MAXIMUM, 20000);


    columns.append(isNatural);
    columns.append(health);
    columns.append(armor);
    columns.append(type);
    columns.append(positionLatitude);
    columns.append(positionLongitude);
    columns.append(radius);

    QString viewQuery = QString(""
        "select id, is_natural, health, armor, type, position_latitude, position_longitude, radius "
        "from fortifications "
        "where battlefield_fk=%1"
        "").arg(currentAction.id());

    QString insertQuery = QString(""
        "insert into fortifications "
        "(id, is_natural, health, armor, type, position_latitude, position_longitude, radius, battlefield_fk) "
        "values(NULL, %1, %2)"
        "").arg("%1", currentAction.id());

    QString updateQuery = QString(""
        "replace into fortifications "
        "(id, is_natural, health, armor, type, position_latitude, position_longitude, radius, battlefield_fk) "
        "values(%1, %2, %3)"
        "").arg("%1", "%2", currentAction.id());

    QString deleteQuery = "delete from fortifications where id=%1";

    InfoDialog fortificationsInfo("Fortification", columns, viewQuery, insertQuery, updateQuery, deleteQuery,
        QList<Action>({}));
    fortificationsInfo.exec();
    Action selectedAction = fortificationsInfo.getSelectedAction();
    return selectedAction;
}


Action Manager::execVehiclesWindow()
{
    QList<Item> columns;
    QList<QList<QVariant>> rows;

    // health
    Item health = itemFactory.createReal("health", 100);
    health.setProperty(LIMIT_MINIMUM, true);
    health.setProperty(MINIMUM, 0);
    health.setProperty(LIMIT_MAXIMUM, true);
    health.setProperty(MAXIMUM, 100);

    // armor
    Item armor = itemFactory.createReal("armor", 100);
    armor.setProperty(LIMIT_MINIMUM, true);
    armor.setProperty(MINIMUM, 0);
    armor.setProperty(LIMIT_MAXIMUM, true);
    armor.setProperty(MAXIMUM, 100);


    // type
    Item type = itemFactory.createEnum("type", VEHICLE_TYPES, 0);

    // position latitude
    Item positionLatitude = itemFactory.createReal("position_latitude", 30);
    positionLatitude.setProperty(LIMIT_MINIMUM, true);
    positionLatitude.setProperty(MINIMUM, 25.2919f);
    positionLatitude.setProperty(LIMIT_MAXIMUM, true);
    positionLatitude.setProperty(MAXIMUM, 39.6482f);

    // position longitude
    Item positionLongitude = itemFactory.createReal("position_longitude", 50);
    positionLongitude.setProperty(LIMIT_MINIMUM, true);
    positionLongitude.setProperty(MINIMUM, 44.7653f);
    positionLongitude.setProperty(LIMIT_MAXIMUM, true);
    positionLongitude.setProperty(MAXIMUM, 61.4949f);

    // max speed
    Item max_speed = itemFactory.createInteger("max_speed", 100);
    max_speed.setProperty(LIMIT_MINIMUM, true);
    max_speed.setProperty(MINIMUM, 80);
    max_speed.setProperty(LIMIT_MAXIMUM, true);
    max_speed.setProperty(MAXIMUM, 200);

    // max acceleration
    Item max_acceleration = itemFactory.createInteger("max_acceleration", 10);
    max_acceleration.setProperty(LIMIT_MINIMUM, true);
    max_acceleration.setProperty(MINIMUM, 5);
    max_acceleration.setProperty(LIMIT_MAXIMUM, true);
    max_acceleration.setProperty(MAXIMUM, 20);

    // fuel type
    Item fuel_type = itemFactory.createEnum("fuel_type", VEHICLE_FUEL_TYPES, 0);

    // fuel max capacity
    Item fuel_max_capacity = itemFactory.createInteger("fuel_max_capacity", 50);
    fuel_max_capacity.setProperty(LIMIT_MINIMUM, true);
    fuel_max_capacity.setProperty(MINIMUM, 25);
    fuel_max_capacity.setProperty(LIMIT_MAXIMUM, true);
    fuel_max_capacity.setProperty(MAXIMUM, 100);

    // fuel consuming unit
    Item fuel_consuming_unit = itemFactory.createInteger("fuel_consuming_unit", 5);
    fuel_consuming_unit.setProperty(LIMIT_MINIMUM, true);
    fuel_consuming_unit.setProperty(MINIMUM, 3);
    fuel_consuming_unit.setProperty(LIMIT_MAXIMUM, true);
    fuel_consuming_unit.setProperty(MAXIMUM, 20);

    // max passengers
    Item max_passengers = itemFactory.createInteger("max_passengers", 5);
    max_passengers.setProperty(LIMIT_MINIMUM, true);
    max_passengers.setProperty(MINIMUM, 1);
    max_passengers.setProperty(LIMIT_MAXIMUM, true);
    max_passengers.setProperty(MAXIMUM, 10);


    columns.append(health);
    columns.append(armor);
    columns.append(type);
    columns.append(positionLatitude);
    columns.append(positionLongitude);
    columns.append(max_speed);
    columns.append(max_acceleration);
    columns.append(fuel_type);
    columns.append(fuel_max_capacity);
    columns.append(fuel_consuming_unit);
    columns.append(max_passengers);

    for (int i = 0; i < 10; i++)
    {
        QList<QVariant> items;
        items.append(55 + i * 3);
        items.append(55 + i * 3);
        items.append(VEHICLE_TYPES[i % VEHICLE_TYPES.size()]);
        items.append(QString::number(((float) qrand() / RAND_MAX) + 26 + i).toDouble());
        items.append(QString::number(((float) qrand() / RAND_MAX) + 45 + i).toDouble());
        items.append(80 + i * 7);
        items.append(5 + i * 1);
        items.append(VEHICLE_FUEL_TYPES[i % VEHICLE_FUEL_TYPES.size()]);
        items.append(25 + i * 7);
        items.append(5 + i);
        items.append(1 + i * 1);
        rows.append(items);
    }

    InfoDialog vehiclesInfo("Vehicle", columns, rows, QList<Action>({}));
    vehiclesInfo.exec();
    Action selectedAction = vehiclesInfo.getSelectedAction();
    return selectedAction;
}


Action Manager::execAmmoWindow()
{
    QList<Item> columns;
    QList<QList<QVariant>> rows;

    // name
    Item name = itemFactory.createString("name", "Name_0");
    name.setProperty(ALLOW_NULL, false);
    name.setProperty(MINIMUM_LENGTH, -1);
    name.setProperty(MAXIMUM_LENGTH, -1);
    name.setProperty(PATTERN, "");

    // type
    Item type = itemFactory.createEnum("type", AMMO_TYPES, 0);

    // surface material
    Item surface_material = itemFactory.createEnum("surface_material", AMMO_SURFACE_MATERAIL, 0);

    // explosion material
    Item explosion_material = itemFactory.createEnum("explosion_material", AMMO_EXPLOSION_MATERIAL, 0);

    // weight
    Item weight = itemFactory.createReal("weight", .1);
    weight.setProperty(LIMIT_MINIMUM, true);
    weight.setProperty(MINIMUM, .1f);
    weight.setProperty(LIMIT_MAXIMUM, true);
    weight.setProperty(MAXIMUM, 200);

    // count
    Item count = itemFactory.createInteger("count", 10);
    count.setProperty(LIMIT_MINIMUM, true);
    count.setProperty(MINIMUM, 0);
    count.setProperty(LIMIT_MAXIMUM, true);
    count.setProperty(MAXIMUM, 1000000);

    // width
    Item width = itemFactory.createReal("width", .02);
    width.setProperty(LIMIT_MINIMUM, true);
    width.setProperty(MINIMUM, .01f);
    width.setProperty(LIMIT_MAXIMUM, true);
    width.setProperty(MAXIMUM, 1);

    // length
    Item length = itemFactory.createReal("length", .02);
    length.setProperty(LIMIT_MINIMUM, true);
    length.setProperty(MINIMUM, .01f);
    length.setProperty(LIMIT_MAXIMUM, true);
    length.setProperty(MAXIMUM, 1);

    // height
    Item height = itemFactory.createReal("height", .02);
    height.setProperty(LIMIT_MINIMUM, true);
    height.setProperty(MINIMUM, .01f);
    height.setProperty(LIMIT_MAXIMUM, true);
    height.setProperty(MAXIMUM, 10);


    columns.append(name);
    columns.append(type);
    columns.append(surface_material);
    columns.append(explosion_material);
    columns.append(weight);
    columns.append(count);
    columns.append(width);
    columns.append(length);
    columns.append(height);

    for (int i = 0; i < 10; i++)
    {
        QList<QVariant> items;
        items.append("Ammo_Name_" + QString::number(i));
        items.append(AMMO_TYPES[i % AMMO_TYPES.size()]);
        items.append(AMMO_SURFACE_MATERAIL[i % AMMO_SURFACE_MATERAIL.size()]);
        items.append(AMMO_EXPLOSION_MATERIAL[i % AMMO_EXPLOSION_MATERIAL.size()]);
        items.append(.2 + i * 7);
        items.append(17 + i * 1);
        items.append(.1 + i * .1);
        items.append(.1 + i * .1);
        items.append(.1 + i);
        rows.append(items);
    }

    InfoDialog ammoInfo("Ammo", columns, rows, QList<Action>({}));
    ammoInfo.exec();
    Action selectedAction = ammoInfo.getSelectedAction();
    return selectedAction;
}


Action Manager::execWeaponsWindow()
{
    QList<Item> columns;
    QList<QList<QVariant>> rows;

    // name
    Item name = itemFactory.createString("name", "Name_0");
    name.setProperty(ALLOW_NULL, false);
    name.setProperty(MINIMUM_LENGTH, -1);
    name.setProperty(MAXIMUM_LENGTH, -1);
    name.setProperty(PATTERN, "");

    // type
    Item type = itemFactory.createEnum("type", WEAPON_TYPES, 0);

    // model
    Item model = itemFactory.createEnum("type", WEAPON_MODELS, 0);

    // weight
    Item weight = itemFactory.createReal("weight", .1);
    weight.setProperty(LIMIT_MINIMUM, true);
    weight.setProperty(MINIMUM, .1f);
    weight.setProperty(LIMIT_MAXIMUM, true);
    weight.setProperty(MAXIMUM, 200);

    // count
    Item count = itemFactory.createInteger("count", 10);
    count.setProperty(LIMIT_MINIMUM, true);
    count.setProperty(MINIMUM, 0);
    count.setProperty(LIMIT_MAXIMUM, true);
    count.setProperty(MAXIMUM, 1000000);

    // width
    Item width = itemFactory.createReal("width", .02);
    width.setProperty(LIMIT_MINIMUM, true);
    width.setProperty(MINIMUM, .01f);
    width.setProperty(LIMIT_MAXIMUM, true);
    width.setProperty(MAXIMUM, 1);

    // length
    Item length = itemFactory.createReal("length", .02);
    length.setProperty(LIMIT_MINIMUM, true);
    length.setProperty(MINIMUM, .01f);
    length.setProperty(LIMIT_MAXIMUM, true);
    length.setProperty(MAXIMUM, 1);

    // height
    Item height = itemFactory.createReal("height", .02);
    height.setProperty(LIMIT_MINIMUM, true);
    height.setProperty(MINIMUM, .01f);
    height.setProperty(LIMIT_MAXIMUM, true);
    height.setProperty(MAXIMUM, 10);

    // fire speed
    Item fire_speed = itemFactory.createInteger("fire_speed", 5);
    fire_speed.setProperty(LIMIT_MINIMUM, true);
    fire_speed.setProperty(MINIMUM, 1);
    fire_speed.setProperty(LIMIT_MAXIMUM, true);
    fire_speed.setProperty(MAXIMUM, 50);

    // max range
    Item max_range = itemFactory.createReal("max_range", 1000);
    max_range.setProperty(LIMIT_MINIMUM, true);
    max_range.setProperty(MINIMUM, 500);
    max_range.setProperty(LIMIT_MAXIMUM, true);
    max_range.setProperty(MAXIMUM, 4000);

    // average realod time
    Item average_realod_time = itemFactory.createReal("average_realod_time", 10);
    average_realod_time.setProperty(LIMIT_MINIMUM, true);
    average_realod_time.setProperty(MINIMUM, 3);
    average_realod_time.setProperty(LIMIT_MAXIMUM, true);
    average_realod_time.setProperty(MAXIMUM, 20);

    // magazine size
    Item magazine_size = itemFactory.createInteger("magazine_size", 16);
    magazine_size.setProperty(LIMIT_MINIMUM, true);
    magazine_size.setProperty(MINIMUM, 6);
    magazine_size.setProperty(LIMIT_MAXIMUM, true);
    magazine_size.setProperty(MAXIMUM, 100);


    columns.append(name);
    columns.append(type);
    columns.append(model);
    columns.append(weight);
    columns.append(count);
    columns.append(width);
    columns.append(length);
    columns.append(height);
    columns.append(fire_speed);
    columns.append(max_range);
    columns.append(average_realod_time);
    columns.append(magazine_size);

    for (int i = 0; i < 10; i++)
    {
        QList<QVariant> items;
        items.append("Weapon_Name_" + QString::number(i));
        items.append(WEAPON_TYPES[i % WEAPON_TYPES.size()]);
        items.append(WEAPON_MODELS[i % WEAPON_MODELS.size()]);
        items.append(.2 + i * 7);
        items.append(17 + i * 1);
        items.append(.1 + i * .1);
        items.append(.1 + i * .1);
        items.append(.1 + i);
        items.append(i);
        items.append(500 + i * 120);
        items.append(3 + i);
        items.append(6 + i * 7);
        rows.append(items);
    }

    InfoDialog weaponsInfo("Ammo", columns, rows, QList<Action>({}));
    weaponsInfo.exec();
    Action selectedAction = weaponsInfo.getSelectedAction();
    return selectedAction;
}

Action Manager::execSuitsWindow()
{
    QList<Item> columns;
    QList<QList<QVariant>> rows;

    // type
    Item type = itemFactory.createEnum("type", SUIT_TYPES, 0);

    // size
    Item size = itemFactory.createInteger("size", 5);
    size.setProperty(LIMIT_MINIMUM, true);
    size.setProperty(MINIMUM, 0);
    size.setProperty(LIMIT_MAXIMUM, true);
    size.setProperty(MAXIMUM, 10);

    // armor
    Item armor = itemFactory.createReal("armor", 100);
    armor.setProperty(LIMIT_MINIMUM, true);
    armor.setProperty(MINIMUM, 0);
    armor.setProperty(LIMIT_MAXIMUM, true);
    armor.setProperty(MAXIMUM, 100);

    // in use
    Item inUse = itemFactory.createBoolean("in_use", true);


    columns.append(type);
    columns.append(size);
    columns.append(armor);
    columns.append(inUse);

    for (int i = 0; i < 10; i++)
    {
        QList<QVariant> items;
        items.append(SUIT_TYPES[i % SUIT_TYPES.size()]);
        items.append(i);
        items.append(50 + i * 3);
        items.append(i % 2 == 1);
        rows.append(items);
    }

    InfoDialog suitInfo("Suit", columns, rows, QList<Action>({}));
    suitInfo.exec();
    Action selectedAction = suitInfo.getSelectedAction();
    return selectedAction;
}
