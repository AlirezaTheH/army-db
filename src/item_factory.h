#ifndef ITEM_FACTORY_H
#define ITEM_FACTORY_H

#include "item.h"


class ItemFactory
{
public:
    ItemFactory();

    Item createString(const QString &name, const QString &value) const;

    Item createInteger(const QString &name, const int &value) const;

    Item createReal(const QString &name, const double &value) const;

    Item createBoolean(const QString &name, const bool &value) const;

    Item createEnum(const QString &name, const QStringList &attrs, const int &value) const;

    Item createStringList(const QString &name, const QStringList &attrs, const QString &value) const;
};

#endif // ITEM_FACTORY_H
