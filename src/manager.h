#ifndef MANAGER_H
#define MANAGER_H

#include "item_factory.h"


class Manager
{
public:
    Manager();
    void exec();

private:
    ItemFactory itemFactory;
};

#endif // MANAGER_H
