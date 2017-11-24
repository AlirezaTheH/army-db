#ifndef ACTION_H
#define ACTION_H

#include <QtCore>


enum class ActionType;

class Action
{
public:
    Action(const ActionType &type);

    ActionType type() const;
    QString name() const;

private:
    ActionType _type;
    QStringList names;
};


enum class ActionType
{
    None,
    ShowBases,
    ShowArmies,
    ShowTroopers,
    ShowTrooperSkills
};

#endif // ACTION_H
