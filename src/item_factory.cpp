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


Item ItemFactory::createInteger(const QString &name, const int &value) const
{
    return Item (
        ItemType::Integer,
        name,
        QList<QString> ({LIMIT_MINIMUM, LIMIT_MAXIMUM, MINIMUM, MAXIMUM}),
        value
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


Item ItemFactory::createBoolean(const QString &name, const bool &value) const
{
    return Item (
        ItemType::Boolean,
        name,
        QList<QString> ({}),
        value
    );
}


Item ItemFactory::createEnum(const QString &name, const QStringList &attrs, const int &value) const
{
    Item item(
        ItemType::Enumeration,
        name,
        QList<QString> ({ENUM_ATTRS, MINIMUM, MAXIMUM}),
        value
    );

    item.setProperty(ENUM_ATTRS, attrs);
    item.setProperty(MINIMUM, 0);
    item.setProperty(MAXIMUM, attrs.size() - 1);

    return item;
}


Item ItemFactory::createStringList(const QString &name, const QStringList &attrs, const QString &value) const
{
    Item item(
        ItemType::StringList,
        name,
        QList<QString> ({LIST_ATTRS}),
        value
    );

    item.setProperty(LIST_ATTRS, attrs);

    return item;
}
