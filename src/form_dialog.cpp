#include "form_dialog.h"
#include "ui_form_dialog.h"

#include <QtCore>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>

#include "consts.h"
#include "item.h"
#include "limit_checker.h"
#include "message_dialog.h"


FormDialog::FormDialog(const QString &title, const QList<Item*> &items, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormDialog),
    items(items),
    done(false)
{
    ui->setupUi(this);
    setFixedSize(size());
    setWindowTitle(title);
    ui->tableWidget_properties->setEditTriggers(QAbstractItemView::NoEditTriggers);

    setupProperties();
}

FormDialog::~FormDialog()
{
    delete ui;
}

bool FormDialog::wasDone() const
{
    return done;
}

void FormDialog::setupProperties()
{
    ui->tableWidget_properties->setRowCount(items.size());

    for (int i = 0; i < items.size(); i++)
    {
        QWidget *tableItem = nullptr;
        ui->tableWidget_properties->setItem(i, 0, new QTableWidgetItem(items[i]->name()));

        switch (items[i]->type())
        {
            case ItemType::String:
                tableItem = new QLineEdit(items[i]->value<QString>());
                break;
            case ItemType::Integer:
                tableItem = new QLineEdit(QString::number(items[i]->value<int>()));
                break;
            case ItemType::Real:
                tableItem = new QLineEdit(QString::number(items[i]->value<double>()));
                break;
            case ItemType::Boolean:
                tableItem = new QCheckBox();
                ((QCheckBox*) tableItem)->setChecked(items[i]->value<bool>());
                break;
            case ItemType::Enumeration:
                tableItem = new QComboBox();
                ((QComboBox*) tableItem)->addItems(items[i]->property<QStringList>(ENUM_ATTRS));
                ((QComboBox*) tableItem)->setCurrentIndex(items[i]->value<int>());
                break;
            case ItemType::StringList:
                tableItem = new QComboBox();
                ((QComboBox*) tableItem)->addItems(items[i]->property<QStringList>(LIST_ATTRS));
                ((QComboBox*) tableItem)->setCurrentText(items[i]->value<QString>());
                break;
            default:
                break;
        }
        ui->tableWidget_properties->setCellWidget(i, 1, tableItem);
    }

    ui->tableWidget_properties->resizeRowsToContents();
    ui->tableWidget_properties->setColumnWidth(0, ui->tableWidget_properties->columnWidth(0) + 20);
    ui->tableWidget_properties->setColumnWidth(1, ui->tableWidget_properties->width() - ui->tableWidget_properties->columnWidth(0) - 21);
}

void FormDialog::on_pushButton_cancel_clicked()
{
    close();
}

void FormDialog::on_pushButton_done_clicked()
{
    for (int i = 0; i < items.size(); i++)
    {
        QWidget *cell = ui->tableWidget_properties->cellWidget(i, 1);
        QString text;
        QString error;
        int intValue;
        double realValue;
        bool converted;

        switch (items[i]->type())
        {
            case ItemType::String:
                text = ((QLineEdit *) cell)->text();
                error = LimitChecker::instance()->check(
                    text,
                    !items[i]->property<bool>(ALLOW_NULL),
                    items[i]->property<int>(MINIMUM_LENGTH),
                    items[i]->property<int>(MAXIMUM_LENGTH),
                    items[i]->property<QString>(PATTERN)
                );
                if (error != "")
                {
                    MessageDialog::instance()->err(QString("%1 %2!").arg(items[i]->name(), error), this);
                    return;
                }
                if (items[i]->property<QString>(PATTERN) == DATETIME_PATTERN)
                {
                    QDateTime dt = QDateTime::fromString(text, Qt::ISODate);
                    if (dt.toSecsSinceEpoch() <= QDateTime::currentSecsSinceEpoch())
                    {
                        error = "must be greater than now";
                        MessageDialog::instance()->err(QString("%1 %2!").arg(items[i]->name(), error), this);
                        return;
                    }
                }
                items[i]->setValue(text);
                break;

            case ItemType::Integer:
                text = ((QLineEdit *) cell)->text();
                intValue = text.toInt(&converted);
                if (!converted)
                {
                    MessageDialog::instance()->err(QString("%1 must be an integer!").arg(items[i]->name()), this);
                    return;
                }

                error = LimitChecker::instance()->check(
                    intValue,
                    items[i]->property<bool>(LIMIT_MINIMUM),
                    items[i]->property<bool>(LIMIT_MAXIMUM),
                    items[i]->property<int>(MINIMUM),
                    items[i]->property<int>(MAXIMUM)
                );
                if (error != "")
                {
                    MessageDialog::instance()->err(QString("%1 %2!").arg(items[i]->name(), error), this);
                    return;
                }

                items[i]->setValue(intValue);
                break;

            case ItemType::Real:
                text = ((QLineEdit *) cell)->text();
                realValue = text.toDouble(&converted);
                if (!converted)
                {
                    MessageDialog::instance()->err(QString("%1 must be a real number!").arg(items[i]->name()), this);
                    return;
                }

                error = LimitChecker::instance()->check(
                    realValue,
                    items[i]->property<bool>(LIMIT_MINIMUM),
                    items[i]->property<bool>(LIMIT_MAXIMUM),
                    items[i]->property<double>(MINIMUM),
                    items[i]->property<double>(MAXIMUM)
                );
                if (error != "")
                {
                    MessageDialog::instance()->err(QString("%1 %2!").arg(items[i]->name(), error), this);
                    return;
                }
                items[i]->setValue(realValue);
                break;

            case ItemType::Boolean:
                items[i]->setValue(((QCheckBox *) cell)->isChecked());
                break;

            case ItemType::Enumeration:
                items[i]->setValue(((QComboBox*) cell)->currentIndex());
                break;

            case ItemType::StringList:
                items[i]->setValue(((QComboBox*) cell)->currentText());
                break;

            default:
                break;
        }
    }

    done = true;
    close();
}
