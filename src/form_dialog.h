#ifndef FORM_DIALOG_H
#define FORM_DIALOG_H

#include <QDialog>

#include "item.h"


namespace Ui {
class FormDialog;
}

class FormDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FormDialog(const QString &title, const QList<Item*> &items, QWidget *parent = 0);
    ~FormDialog();
    bool wasDone() const;

private slots:
    void on_pushButton_cancel_clicked();

    void on_pushButton_done_clicked();

private:
    void setupProperties();

private:
    Ui::FormDialog *ui;
    QList<Item*> items;
    bool done;
};

#endif // FORM_DIALOG_H
