#ifndef MANAGER_H
#define MANAGER_H

#include "item_factory.h"
#include "action.h"


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

private:
    ItemFactory itemFactory;
    QList<Action> actionsHistory;
};

#endif // MANAGER_H
