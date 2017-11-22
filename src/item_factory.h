#ifndef ITEM_FACTORY_H
#define ITEM_FACTORY_H

#include "item.h"


class ItemFactory
{
public:
    ItemFactory();

    Item createString(const QString &name, const QString &value) const;
    Item createString(const QString &name, const QList<QString> &values) const;

    Item createInteger(const QString &name, const int &value) const;
    Item createInteger(const QString &name, const QList<int> &values) const;

    Item createReal(const QString &name, const double &value) const;
    Item createReal(const QString &name, const QList<double> &values) const;

    Item createBoolean(const QString &name, const bool &value) const;
    Item createBoolean(const QString &name, const QList<bool> &values) const;
};

#endif // ITEM_FACTORY_H
