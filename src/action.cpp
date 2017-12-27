#include "action.h"

Action::Action(const ActionType &type):
    _type(type)
{
    names = QStringList({
        "",
        "Show Battlefields",
        "Show Bases",
        "Show Armies",
        "Show Troopers",
        "Show Trooper Skills",
        "Show Fortifications",
        "Show Vehicles",
        "Show Ammo",
        "Show Weapons",
        "Show Suits",
        "Show Weapon Can Use Ammo"
    });
}

ActionType Action::type() const
{
    return _type;
}

QString Action::name() const
{
    return names[(int) type()];
}

void Action::setId(const QString &id)
{
    _id = id;
}

QString Action::id() const
{
    return _id;
}
