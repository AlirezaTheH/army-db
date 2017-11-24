#include "action.h"

Action::Action(const ActionType &type):
    _type(type)
{
    names = QStringList({
        "",
        "Show Bases",
        "Show Armies",
        "Show Troopers",
        "Show Trooper Skills"
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
