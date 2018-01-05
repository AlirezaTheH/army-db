#ifndef MENU_DIALOG_H
#define MENU_DIALOG_H

#include <QDialog>

namespace Ui {
class MenuDialog;
}

class MenuDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MenuDialog(QWidget *parent = 0);
    ~MenuDialog();

private slots:
    void on_pushButton_app_clicked();

    void on_pushButton_queries_clicked();

private:
    Ui::MenuDialog *ui;
};

#endif // MENU_DIALOG_H
