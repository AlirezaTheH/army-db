#include "form_dialog.h"
#include "ui_form_dialog.h"

#include "item.h"


FormDialog::FormDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormDialog)
{
    ui->setupUi(this);
}

FormDialog::~FormDialog()
{
    delete ui;
}
