#include "item_factory.h"

#include "consts.h"


ItemFactory::ItemFactory()
{
}


Item ItemFactory::createString(const QString &name, const QString &value) const
{
    return Item(
        ItemType::String,
        name,
        QList<QString> ({ALLOW_NULL, MINIMUM_LENGTH, MAXIMUM_LENGTH, PATTERN}),
        value
    );
}

Item ItemFactory::createString(const QString &name, const QList<QString> &values) const
{
    QList<QVariant> variantValues;
    for (auto x : values)
        variantValues.append(x);

    return Item(
        ItemType::String,
        name,
        QList<QString> ({ALLOW_NULL, MINIMUM_LENGTH, MAXIMUM_LENGTH}),
        variantValues
    );
}


Item ItemFactory::createInteger(const QString &name, const int &value) const
{
    return Item (
        ItemType::Integer,
        name,
        QList<QString> ({LIMIT_MINIMUM, LIMIT_MAXIMUM, MINIMUM, MAXIMUM}),
        value
    );
}

Item ItemFactory::createInteger(const QString &name, const QList<int> &values) const
{
    QList<QVariant> variantValues;
    for (auto x : values)
        variantValues.append(x);

    return Item (
        ItemType::Integer,
        name,
        QList<QString> ({LIMIT_MINIMUM, LIMIT_MAXIMUM, MINIMUM, MAXIMUM}),
        variantValues
    );
}


Item ItemFactory::createReal(const QString &name, const double &value) const
{
    return Item (
        ItemType::Real,
        name,
        QList<QString> ({LIMIT_MINIMUM, LIMIT_MAXIMUM, MINIMUM, MAXIMUM}),
        value
    );
}

Item ItemFactory::createReal(const QString &name, const QList<double> &values) const
{
    QList<QVariant> variantValues;
    for (auto x : values)
        variantValues.append(x);

    return Item (
        ItemType::Real,
        name,
        QList<QString> ({LIMIT_MINIMUM, LIMIT_MAXIMUM, MINIMUM, MAXIMUM}),
        variantValues
    );
}


Item ItemFactory::createBoolean(const QString &name, const bool &value) const
{
    return Item (
        ItemType::Boolean,
        name,
        QList<QString> ({}),
        value
    );
}

Item ItemFactory::createBoolean(const QString &name, const QList<bool> &values) const
{
    QList<QVariant> variantValues;
    for (auto x : values)
        variantValues.append(x);

    return Item (
        ItemType::Boolean,
        name,
        QList<QString> ({}),
        variantValues
    );
}
