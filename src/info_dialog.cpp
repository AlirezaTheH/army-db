#include "info_dialog.h"
#include "ui_info_dialog.h"

#include <QtCore>

#include "form_dialog.h"


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
    ui->tableWidget_data->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_data->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_data->setSelectionMode(QAbstractItemView::SingleSelection);
    showData();
}

InfoDialog::~InfoDialog()
{
    delete ui;
}


void InfoDialog::showData()
{
    QStringList headers;
    for (Item item : dataColumns)
    {
        int col = ui->tableWidget_data->columnCount();
        ui->tableWidget_data->insertColumn(col);
        headers.append(item.name());
    }
    ui->tableWidget_data->setHorizontalHeaderLabels(headers);

    for (int row = 0; row < dataRows.size(); row++)
    {
        ui->tableWidget_data->insertRow(row);
        for (int col = 0; col < dataRows[row].size(); col++)
        {
            auto x = new QTableWidgetItem(dataRows[row][col].toString());
            x->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_data->setItem(row, col, x);
        }
    }

    ui->tableWidget_data->resizeColumnsToContents();
    ui->tableWidget_data->resizeRowsToContents();
    for (int i = 0; i < ui->tableWidget_data->columnCount(); i++)
        ui->tableWidget_data->setColumnWidth(i, ui->tableWidget_data->columnWidth(i) + 20);
}


void InfoDialog::on_pushButton_create_clicked()
{
    FormDialog creationForm(this);
    creationForm.exec();
}
