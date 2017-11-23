#ifndef ITEM_H
#define ITEM_H

#include <QVariant>
#include <QList>
#include <QMap>

#include <stdexcept>


enum class ItemType;

class Item
{
public:

    Item() {}

    Item(const ItemType &type, const QString &name,
            const QList<QString> &allowedProperties, const QVariant &value):
        _multivalue(false),
        _type(type),
        _name(name),
        _allowedProperties(allowedProperties),
        _value(value)
    {
    }

    Item(const ItemType &type, const QString &name,
            const QList<QString> &allowedProperties, const QList<QVariant> &values):
        _multivalue(true),
        _type(type),
        _name(name),
        _allowedProperties(allowedProperties),
        _values(values)
    {
    }

    const ItemType &type() const
    {
        return _type;
    }

    bool multivalue() const
    {
        return _multivalue;
    }

    const QString &name() const
    {
        return _name;
    }

    template <typename T>
    const T value() const
    {
        if (multivalue())
            throw std::runtime_error("This item is a multivalue item");
        return qvariant_cast<T> (_value);
    }

    void setValue(const QVariant &value)
    {
        if (multivalue())
            throw std::runtime_error("This item is a multivalue item");
        _value = value;
    }

    template<typename T>
    const QList<T> values() const
    {
        if (!multivalue())
            throw std::runtime_error("This item is not a multivalue item");
        QList<T> result;
        for (auto x : _values)
            result.append(qvariant_cast<T> (x));
        return result;
    }

    void setValues(const QList<QVariant> &values)
    {
        if (!multivalue())
            throw std::runtime_error("This item is not a multivalue item");
        _values = values;
    }

    template<typename T>
    const T property(const QString &key) const
    {
        if (!_allowedProperties.contains(key))
            throw std::runtime_error(QString("%1 is not in item properties").arg(key).toStdString());
        return qvariant_cast<T> (_properties.value(key));
    }

    void setProperty(const QString key, const QVariant &value)
    {
        if (!_allowedProperties.contains(key))
            throw std::runtime_error(QString("%1 is not in item properties").arg(key).toStdString());
        _properties.insert(key, value);
    }


private:
    bool _multivalue;
    ItemType _type;
    QString _name;
    QVariant _value;
    QList<QVariant> _values;
    QList<QString> _allowedProperties;
    QMap<QString, QVariant> _properties;
};


enum class ItemType
{
    String,
    Integer,
    Real,
    Boolean,
    Enumeration
};

#endif // ITEM_H
