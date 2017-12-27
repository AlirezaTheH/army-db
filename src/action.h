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
    ShowWeapons,
    ShowSuits,
    ShowWeaponCanUseAmmo
};


class Action
{
public:
    Action(const ActionType &type = ActionType::None);

    ActionType type() const;
    QString name() const;

    void setId(const QString &id);
    QString id() const;

private:
    ActionType _type;
    QStringList names;
    QString _id;
};


#endif // ACTION_H
