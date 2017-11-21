#include "info_dialog.h"
#include "ui_info_dialog.h"

InfoDialog::InfoDialog(const QString &title, const QList<Item> &dataColumns,
        const QList<QList<QVariant> > &dataRows, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoDialog),
    dataColumns(dataColumns),
    dataRows(dataRows)
{
    ui->setupUi(this);
    setFixedSize(size());
    setWindowTitle(title);
}

InfoDialog::~InfoDialog()
{
    delete ui;
}
