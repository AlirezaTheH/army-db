#ifndef INFO_DIALOG_H
#define INFO_DIALOG_H

#include <QDialog>

#include "item.h"
#include "action.h"


namespace Ui {
class InfoDialog;
}

class InfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InfoDialog(const QString &title, const QList<Item> &dataColumns,
        const QList<QList<QVariant>> &dataRows, const QList<Action> actions, QWidget *parent = 0);
    ~InfoDialog();

    Action getSelectedAction() const;

private slots:
    void on_pushButton_create_clicked();

    void on_pushButton_edit_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_doAction_clicked();

private:
    void showData();
    void showActions();

private:
    Ui::InfoDialog *ui;
    QList<Item> dataColumns;
    QList<QList<QVariant>> dataRows;
    QList<Action> actions;
    Action selectedAction;
};

#endif // INFO_DIALOG_H
