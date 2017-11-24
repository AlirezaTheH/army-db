#include "manager.h"

#include <QtCore>

#include "consts.h"
#include "info_dialog.h"


Manager::Manager()
{
}

void Manager::exec()
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
    Item startDatetime = itemFactory.createString("start_datetime", "2017-02-12 23:43");
    startDatetime.setProperty(ALLOW_NULL, false);
    startDatetime.setProperty(MINIMUM_LENGTH, -1);
    startDatetime.setProperty(MAXIMUM_LENGTH, -1);
    startDatetime.setProperty(PATTERN, DATETIME_PATTERN);

    // end datetime
    Item endDatetime = itemFactory.createString("end_datetime", "2018-02-12 23:43");
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
        items.append(QString("2018-22-11 19:0%1").arg(i));
        items.append(QString("2018-25-11 19:0%1").arg(i));
        rows.append(items);
    }

    InfoDialog battleFieldInfo("BattleField", columns, rows, QList<Action>({Action(ActionType::ShowBases)}));
    battleFieldInfo.exec();
    Action selectedAction = battleFieldInfo.getSelectedAction();
    if (selectedAction.type() != ActionType::None)
    {
        qDebug() << selectedAction.name();
    }
}
