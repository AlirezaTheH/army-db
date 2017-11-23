#include "info_dialog.h"
#include "ui_info_dialog.h"

#include <QtCore>

#include "form_dialog.h"
#include "message_dialog.h"


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
    QList<Item*> items;
    for (auto item : dataColumns)
    {
        Item *i = new Item();
        *i = item;
        items.append(i);
    }

    FormDialog creationForm("Create " + windowTitle(), items, this);
    creationForm.exec();
    if (!creationForm.wasDone())
        return;

    int row = ui->tableWidget_data->rowCount();
    ui->tableWidget_data->insertRow(row);

    for (int i = 0; i < items.size(); i++)
    {
        QTableWidgetItem *tableItem = new QTableWidgetItem(items[i]->value<QString>());
        tableItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_data->setItem(row, i, tableItem);
    }
}

void InfoDialog::on_pushButton_edit_clicked()
{
    if (ui->tableWidget_data->currentRow() == -1)
    {
        MessageDialog::instance()->err("Please select an entry to edit!", this);
        return;
    }

    QList<Item*> items;
    for (int i = 0; i < dataColumns.size(); i++)
    {
        Item *item = new Item();
        *item = dataColumns[i];
        items.append(item);

        QString text = ui->tableWidget_data->item(ui->tableWidget_data->currentRow(), i)->text();
        switch (item->type())
        {
            case ItemType::String:
                item->setValue(text);
                break;
            case ItemType::Integer:
                item->setValue(text.toInt());
                break;
            case ItemType::Real:
                item->setValue(text.toDouble());
                break;
            case ItemType::Boolean:
                item->setValue((text == "true") ? true : false);
                break;
        }
    }

    FormDialog editionForm("Edit " + windowTitle(), items, this);
    editionForm.exec();
    if (!editionForm.wasDone())
        return;


    int row = ui->tableWidget_data->currentRow();

    for (int i = 0; i < items.size(); i++)
    {
        QTableWidgetItem *tableItem = new QTableWidgetItem(items[i]->value<QString>());
        tableItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_data->setItem(row, i, tableItem);
    }
}

void InfoDialog::on_pushButton_delete_clicked()
{
    if (ui->tableWidget_data->currentRow() == -1)
    {
        MessageDialog::instance()->err("Please select an entry to delete!", this);
        return;
    }

    ui->tableWidget_data->removeRow(ui->tableWidget_data->currentRow());
}
