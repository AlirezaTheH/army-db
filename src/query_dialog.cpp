#include "query_dialog.h"
#include "ui_query_dialog.h"

#include <QtCore>

#include "db.h"
#include "message_dialog.h"


QueryDialog::QueryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QueryDialog)
{
    ui->setupUi(this);
    init();

    ui->comboBox_queries->addItems(queryTitles);
}

QueryDialog::~QueryDialog()
{
    delete ui;
}


void QueryDialog::init()
{
    queryTitles = QStringList({
        "Query1",
        "Query2"
    });

    queryDescriptions = QStringList({
        "Desc1",
        "Desc2"
    });

    queries = QStringList({
        "select * from battlefields",
        "select * from bases"
    });
}

void QueryDialog::on_pushButton_doQuery_clicked()
{
    QueryData result = DB::instance()->query(ui->plainTextEdit_query->toPlainText());

    if (!(result.error.isEmpty() && result.error.isNull()))
    {
        MessageDialog::instance()->err(result.error);
        return;
    }

    ui->tableWidget_data->setColumnCount(0);
    ui->tableWidget_data->setRowCount(0);
    ui->tableWidget_data->setColumnCount(result.columns.size());
    ui->tableWidget_data->setHorizontalHeaderLabels(result.columns);

    for (int row = 0; row < result.rows.size(); row++)
    {
        ui->tableWidget_data->insertRow(row);
        for (int col = 0; col < result.rows[row].size(); col++)
        {
            auto x = new QTableWidgetItem(result.rows[row][col].toString());
            x->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_data->setItem(row, col, x);
        }
    }

    ui->tableWidget_data->resizeColumnsToContents();
    ui->tableWidget_data->resizeRowsToContents();
    for (int i = 0; i < ui->tableWidget_data->columnCount(); i++)
        ui->tableWidget_data->setColumnWidth(i, ui->tableWidget_data->columnWidth(i) + 20);
}

void QueryDialog::on_comboBox_queries_currentIndexChanged(int index)
{
    ui->label_queryDescription->setText(queryDescriptions[index]);
    ui->plainTextEdit_query->setPlainText(queries[index]);
}
