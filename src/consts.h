#ifndef CONSTS_H
#define CONSTS_H

#include <QString>


const QString USER_ROLE = "USER_ROLE";
const QString DATETIME_PATTERN = "^(\\d{4})-(\\d{2})-(\\d{2}) (\\d{2}):(\\d{2})$";

const QString ALLOW_NULL = "ALLOW_NULL";
const QString MINIMUM = "MINIMUM";
const QString MAXIMUM = "MAXIMUM";
const QString MINIMUM_LENGTH = "MINIMUM_LENGTH";
const QString MAXIMUM_LENGTH = "MAXIMUM_LENGTh";
const QString LIMIT_MINIMUM = "LIMIT_MINIMUM";
const QString LIMIT_MAXIMUM = "LIMIT_MAXIMUM";
const QString PATTERN = "PATTERN";
const QString ENUM_ATTRS = "ENUM_ATTRS";

const QStringList ALL_COUNTRIES({
    "Iran",
    "Iraq"
});

#endif // CONSTS_H
