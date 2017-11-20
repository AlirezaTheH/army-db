#ifndef LIMIT_CHECKER_H
#define LIMIT_CHECKER_H

#include <QtCore>

class LimitChecker
{
public:
    static LimitChecker *instance();

    QString check(const QString &text, bool nullOrEmpty = true,
               int minLength = -1, int maxLength = -1, const QString pattern = "") const;

    QString check(double number, bool limitMinimum = false, bool limitMaximum = false,
               double minimum = -1, double maximum = -1) const;

private:
    LimitChecker();

private:
    static LimitChecker *ins;
};


#endif // LIMIT_CHECKER_H
