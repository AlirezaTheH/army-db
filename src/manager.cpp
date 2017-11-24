#include "manager.h"

#include <QtCore>
#include <random>

#include "consts.h"
#include "info_dialog.h"


Manager::Manager()
{
}

void Manager::exec()
{
    actionsHistory.push_back(Action(ActionType::ShowBattlefields));
    Action action;

    while (!actionsHistory.empty())
    {
        action = actionsHistory.back();
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
            default:
                break;
        }

        actionsHistory.push_back(action);
    }
}


Action Manager::execBattlefieldsWindow()
{
    QList<Item> columns;
    QList<QList<QVariant>> rows;

    // position latitude
    Item positionLatitude = itemFactory.createReal("position_latitude", 30);
    positionLatitude.setProperty(LIMIT_MINIMUM, true);
    positionLatitude.setProperty(MINIMUM, 25.2919f);
    positionLatitude.setProperty(LIMIT_MAXIMUM, true);
    positionLatitude.setProperty(MAXIMUM, 39.6482f);

    // position latitude
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

    for (int i = 0; i < 10; i++)
    {
        QList<QVariant> items;
        items.append(QString::number(((float) qrand() / RAND_MAX) + 26 + i).toDouble());
        items.append(QString::number(((float) qrand() / RAND_MAX) + 45 + i).toDouble());
        items.append(100 + i);
        items.append(QString("2018-04-11 19:0%1").arg(i));
        items.append(QString("2018-09-13 19:0%1").arg(i));
        rows.append(items);
    }

    InfoDialog battleFieldsInfo("BattleField", columns, rows, QList<Action>({Action(ActionType::ShowBases)}));
    battleFieldsInfo.exec();
    Action selectedAction = battleFieldsInfo.getSelectedAction();
    return selectedAction;
}


Action Manager::execBasesWindow()
{
    QList<Item> columns;
    QList<QList<QVariant>> rows;

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

    // position latitude
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

    // soldier capacity
    Item soldierCapacity = itemFactory.createInteger("soldier_capacity", 200);
    soldierCapacity.setProperty(LIMIT_MINIMUM, true);
    soldierCapacity.setProperty(MINIMUM, 0);
    soldierCapacity.setProperty(LIMIT_MAXIMUM, true);
    soldierCapacity.setProperty(MAXIMUM, 500);


    columns.append(name);
    columns.append(positionLatitude);
    columns.append(positionLongitude);
    columns.append(radius);
    columns.append(vehicleCapacity);
    columns.append(soldierCapacity);

    for (int i = 0; i < 10; i++)
    {
        QList<QVariant> items;
        items.append("Base_" + QString::number(i));
        items.append(QString::number(((float) qrand() / RAND_MAX) + 26 + i).toDouble());
        items.append(QString::number(((float) qrand() / RAND_MAX) + 45 + i).toDouble());
        items.append(100 + i);
        items.append(i * 10 + 5);
        items.append(i * 20 + 25);
        rows.append(items);
    }

    InfoDialog basesInfo("Base", columns, rows, QList<Action>({Action(ActionType::ShowArmies)}));
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

    // position latitude
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

    // soldier capacity
    Item soldierCapacity = itemFactory.createInteger("soldier_capacity", 200);
    soldierCapacity.setProperty(LIMIT_MINIMUM, true);
    soldierCapacity.setProperty(MINIMUM, 0);
    soldierCapacity.setProperty(LIMIT_MAXIMUM, true);
    soldierCapacity.setProperty(MAXIMUM, 500);


    columns.append(name);
    columns.append(forceType);
    columns.append(sizeType);
    columns.append(positionLatitude);
    columns.append(positionLongitude);
    columns.append(radius);
    columns.append(vehicleCapacity);
    columns.append(soldierCapacity);

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

    InfoDialog armiesInfo("Army", columns, rows, QList<Action>({Action(ActionType::ShowTroopers)}));
    armiesInfo.exec();
    Action selectedAction = armiesInfo.getSelectedAction();
    return selectedAction;
}

Action Manager::execTroopersWindow()
{
    return ActionType::None;
}


Action Manager::execTrooperSkillsWindow()
{
    return ActionType::None;
}
