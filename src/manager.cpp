#include "manager.h"

#include <QtCore>

#include "info_dialog.h"


Manager::Manager()
{
}

void Manager::exec()
{
    QList<Item> columns;
    QList<QList<QVariant>> rows;

    // position latitude
    Item positionLatitude(
        ItemType::Real,
        "position_latitude",
        QList<QString> ({"limit_minimum", "limit_maximum", "minimum", "maximum"}),
        30.0f
    );
    positionLatitude.setProperty("limit_minimum", true);
    positionLatitude.setProperty("minimum", 25.2919f);
    positionLatitude.setProperty("limit_maximum", true);
    positionLatitude.setProperty("maximum", 39.6482f);

    InfoDialog battleFieldInfo("BattleField", columns, rows);
    battleFieldInfo.exec();
}
