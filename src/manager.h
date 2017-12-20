#ifndef MANAGER_H
#define MANAGER_H

#include "item_factory.h"
#include "action.h"
#include "db.h"


class Manager
{
public:
    Manager();
    void exec();

private:
    Action execBattlefieldsWindow();
    Action execBasesWindow();
    Action execArmiesWindow();
    Action execTroopersWindow();
    Action execTrooperSkillsWindow();
    Action execFortificationsWindow();
    Action execVehiclesWindow();
    Action execAmmoWindow();
    Action execWeaponsWindow();
    Action execSuitsWindow();

private:
    ItemFactory itemFactory;
    QList<Action> actionsHistory;
    Action currentAction;
};

#endif // MANAGER_H
