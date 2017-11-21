#include "info_window.h"
#include "ui_info_window.h"

InfoWindow::InfoWindow(const QList<Item> &dataColumns, const QList<QList<QVariant> > &dataRows,
        QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InfoWindow),
    dataColumns(dataColumns),
    dataRows(dataRows)
{
    ui->setupUi(this);
    setFixedSize(size());
}

InfoWindow::~InfoWindow()
{
    delete ui;
}
