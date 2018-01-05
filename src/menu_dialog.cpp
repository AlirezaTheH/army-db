#include "menu_dialog.h"
#include "ui_menu_dialog.h"

#include "manager.h"
#include "query_dialog.h"
#include "global_storage.h"
#include "roles.h"
#include "consts.h"
#include "message_dialog.h"


MenuDialog::MenuDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MenuDialog)
{
    ui->setupUi(this);
    setFixedSize(size());
}

MenuDialog::~MenuDialog()
{
    delete ui;
}

void MenuDialog::on_pushButton_app_clicked()
{
    Manager m;
    m.exec();
}

void MenuDialog::on_pushButton_queries_clicked()
{
    if (GlobalStorage::instance()->get<int>(USER_ROLE) == Roles::Admin)
    {
        QueryDialog queryDialog;
        queryDialog.exec();
    }
    else
        MessageDialog::instance()->err("You are not admin");
}
