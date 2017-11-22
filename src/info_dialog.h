#ifndef INFO_DIALOG_H
#define INFO_DIALOG_H

#include <QDialog>

#include "item.h"


namespace Ui {
class InfoDialog;
}

class InfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InfoDialog(const QString &title, const QList<Item> &dataColumns,
        const QList<QList<QVariant>> &dataRows, QWidget *parent = 0);
    ~InfoDialog();

private slots:
    void on_pushButton_create_clicked();

private:
    void showData();

private:
    Ui::InfoDialog *ui;
    QList<Item> dataColumns;
    QList<QList<QVariant>> dataRows;
};

#endif // INFO_DIALOG_H
