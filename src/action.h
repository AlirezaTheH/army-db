#ifndef ACTION_H
#define ACTION_H

#include <QtCore>


enum class ActionType
{
    None,
    ShowBattlefields,
    ShowBases,
    ShowArmies,
    ShowTroopers,
    ShowTrooperSkills,
    ShowFortifications,
    ShowVehicles,
    ShowAmmo,
    ShowWeapons
};


class Action
{
public:
    Action(const ActionType &type = ActionType::None);

    ActionType type() const;
    QString name() const;

private:
    ActionType _type;
    QStringList names;
};


#endif // ACTION_H
