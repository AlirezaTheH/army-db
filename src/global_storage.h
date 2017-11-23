#ifndef GLOBAL_STORAGE_H
#define GLOBAL_STORAGE_H

#include <QtCore>


class GlobalStorage
{
public:
    static GlobalStorage *instance()
    {
        static GlobalStorage *ins = new GlobalStorage();
        return ins;
    }

    void put(const QString &key, const QVariant &value)
    {
        data.insert(key, value);
    }

    template <typename T>
    const T get(const QString &key) const
    {
        const QVariant value = data.value(key);
        return qvariant_cast<T> (value);
    }


private:
    GlobalStorage() {}

private:
    QMap<QString, QVariant> data;
};


#endif // GLOBAL_STORAGE_H
