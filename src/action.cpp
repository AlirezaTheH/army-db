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
        "Show Vehicles"
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
