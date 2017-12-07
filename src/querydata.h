#ifndef QUERYDATA_H
#define QUERYDATA_H

#include <QStringList>
#include <QVariantList>


struct QueryData
{
    QStringList columns;
    QList<QVariantList> rows;
    QString error;
};

#endif // QUERYDATA_H
