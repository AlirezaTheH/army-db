#include "info_dialog.h"
#include "ui_info_dialog.h"

#include <QtCore>

#include "consts.h"
#include "global_storage.h"
#include "roles.h"
#include "form_dialog.h"
#include "message_dialog.h"
#include "db.h"


InfoDialog::InfoDialog(const QString &title, const QList<Item> &dataColumns,
        const QList<QList<QVariant> > &dataRows, const QList<Action> actions, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoDialog),
    dataColumns(dataColumns),
    dataRows(dataRows),
    actions(actions),
    selectedAction(ActionType::None)
{
}

InfoDialog::InfoDialog(const QString &title, const QList<Item> &dataColumns,
        const QString &viewQuery, const QString &insertQuery, const QString &updateQuery, const QString &deleteQuery,
        const QList<Action> actions, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoDialog),
    dataColumns(dataColumns),
    viewQuery(viewQuery),
    insertQuery(insertQuery),
    updateQuery(updateQuery),
    deleteQuery(deleteQuery),
    actions(actions),
    selectedAction(ActionType::None)
{
    ui->setupUi(this);
    setFixedSize(size());
    setWindowTitle(title);

    ui->tableWidget_data->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_data->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_data->setSelectionMode(QAbstractItemView::SingleSelection);

    if (GlobalStorage::instance()->get<int>(USER_ROLE) == Roles::Guest)
    {
        ui->pushButton_create->setVisible(false);
        ui->pushButton_edit->setVisible(false);
        ui->pushButton_delete->setVisible(false);
    }

    if (updateQuery.isNull() || updateQuery.isEmpty())
        ui->pushButton_edit->setVisible(false);

    showData();
    showActions();
}

InfoDialog::~InfoDialog()
{
    delete ui;
}

Action InfoDialog::getSelectedAction() const
{
    return selectedAction;
}


void InfoDialog::showData()
{
    if (viewQuery.isNull())
        return;

    ui->tableWidget_data->setColumnCount(0);
    ui->tableWidget_data->setRowCount(0);
    rowIds.clear();

    QueryData result = DB::instance()->query(viewQuery);

    QStringList headers;
    for (Item item : dataColumns)
    {
        int col = ui->tableWidget_data->columnCount();
        ui->tableWidget_data->insertColumn(col);
        headers.append(item.name());
    }
    ui->tableWidget_data->setHorizontalHeaderLabels(headers);

    for (int row = 0; row < result.rows.size(); row++)
    {
        ui->tableWidget_data->insertRow(row);
        rowIds.append(result.rows[row][0]);
        for (int col = 0; col < result.rows[row].size() - 1; col++)
        {
            QString val = result.rows[row][col + 1].toString();
            if (dataColumns[col].name().endsWith("datetime"))
                val.remove(val.size() - 3, 3);
            if (dataColumns[col].type() == ItemType::Enumeration)
                val = dataColumns[col].property<QStringList>(ENUM_ATTRS)[val.toInt()];
            if (dataColumns[col].type() == ItemType::Boolean)
                val = (val.toInt() == 1) ? "true" : "false";

            auto x = new QTableWidgetItem(val);
            x->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_data->setItem(row, col, x);
        }
    }

    ui->tableWidget_data->resizeColumnsToContents();
    ui->tableWidget_data->resizeRowsToContents();
    for (int i = 0; i < ui->tableWidget_data->columnCount(); i++)
        ui->tableWidget_data->setColumnWidth(i, ui->tableWidget_data->columnWidth(i) + 20);
}


void InfoDialog::showActions()
{
    for (auto action : actions)
        ui->comboBox_actions->addItem(action.name());
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

    QStringList values;
    for (auto item : items)
    {
        if (item->type() == ItemType::Boolean)
            values.append("'" + QString((item->value<QString>() == "true") ? '1' : '0') + "'");
        else if (item->type() == ItemType::Enumeration)
            values.append("'" + QString::number(item->value<int>()) + "'");
        else if (item->name().endsWith("datetime"))
            values.append("'" + item->value<QString>() + ":00'");
        else
            values.append("'" + item->value<QString>() + "'");
    }

    QueryData result = DB::instance()->query(insertQuery.arg(values.join(", ")));
    if (!(result.error.isEmpty() && result.error.isNull()))
    {
        MessageDialog::instance()->err(result.error);
        return;
    }

    showData();
}

void InfoDialog::on_pushButton_edit_clicked()
{
    int currentRow = ui->tableWidget_data->currentRow();
    if (currentRow == -1)
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

        QString text = ui->tableWidget_data->item(currentRow, i)->text();
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
            case ItemType::Enumeration:
                item->setValue(item->property<QStringList>(ENUM_ATTRS).indexOf(text));
                break;
            default:
                break;
        }
    }

    FormDialog editionForm("Edit " + windowTitle(), items, this);
    editionForm.exec();
    if (!editionForm.wasDone())
        return;

    QStringList values;
    for (auto item : items)
    {
        if (item->type() == ItemType::Boolean)
            values.append("'" + QString((item->value<QString>() == "true") ? '1' : '0') + "'");
        else if (item->type() == ItemType::Enumeration)
            values.append("'" + QString::number(item->value<int>()) + "'");
        else if (item->name().endsWith("datetime"))
            values.append("'" + item->value<QString>() + ":00'");
        else
            values.append("'" + item->value<QString>() + "'");
    }

    QueryData result = DB::instance()->query(
        updateQuery.arg(rowIds[currentRow].toString(), values.join(", "))
    );
    if (!(result.error.isEmpty() && result.error.isNull()))
    {
        MessageDialog::instance()->err(result.error);
        return;
    }

    showData();
    ui->tableWidget_data->setCurrentCell(currentRow, 0);
}

void InfoDialog::on_pushButton_delete_clicked()
{
    if (ui->tableWidget_data->currentRow() == -1)
    {
        MessageDialog::instance()->err("Please select an entry to delete!", this);
        return;
    }

    QueryData result = DB::instance()->query(
        deleteQuery.arg(rowIds[ui->tableWidget_data->currentRow()].toString())
    );
    if (!(result.error.isEmpty() && result.error.isNull()))
    {
        MessageDialog::instance()->err(result.error);
        return;
    }

    showData();
}

void InfoDialog::on_pushButton_doAction_clicked()
{
    if (actions.size() == 0)
    {
        MessageDialog::instance()->err("There is no action!", this);
        return;
    }

    if (ui->tableWidget_data->currentRow() == -1)
    {
        MessageDialog::instance()->err("Please select an entry!", this);
        return;
    }

    selectedAction = actions[ui->comboBox_actions->currentIndex()];
    selectedAction.setId(rowIds[ui->tableWidget_data->currentRow()].toString());
    close();
}
