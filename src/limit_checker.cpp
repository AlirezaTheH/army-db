#include "limit_checker.h"


LimitChecker *LimitChecker::ins = new LimitChecker();

LimitChecker::LimitChecker()
{
}

LimitChecker *LimitChecker::instance()
{
    return ins;
}


QString LimitChecker::check(const QString &text, bool nullOrEmpty, int minLength,
    int maxLength, const QString pattern) const
{
    if (nullOrEmpty)
        if (text.isNull() || text.isEmpty())
            return "can not be empty";

    if (minLength != -1)
        if (text.size() < minLength)
            return QString("must be at least %1 charecters long").arg(minLength);

    if (maxLength != -1)
        if (text.size() > maxLength)
            return QString("must be at most %1 charecters long").arg(minLength);

    return "";
}


QString LimitChecker::check(double number, bool limitMinimum, bool limitMaximum,
    double minimum, double maximum) const
{
    if (limitMinimum)
        if (number < minimum)
            return QString("can be at least %1").arg(QString::number(minimum));

    if (limitMaximum)
        if (number > maximum)
            return QString("can be at most %1").arg(minimum);

    return "";
}
