#ifndef INFO_WINDOW_H
#define INFO_WINDOW_H

#include <QMainWindow>

#include "item.h"


namespace Ui {
class InfoWindow;
}

class InfoWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit InfoWindow(const QList<Item> &dataColumns,
        const QList<QList<QVariant>> &dataRows, QWidget *parent = 0);
    ~InfoWindow();

private:
    Ui::InfoWindow *ui;
    QList<Item> dataColumns;
    QList<QList<QVariant>> dataRows;
};

#endif // INFO_WINDOW_H
