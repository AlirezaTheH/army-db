#ifndef QUERY_DIALOG_H
#define QUERY_DIALOG_H

#include <QDialog>


namespace Ui {
class QueryDialog;
}

class QueryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QueryDialog(QWidget *parent = 0);
    ~QueryDialog();

private slots:
    void on_pushButton_doQuery_clicked();

    void on_comboBox_queries_currentIndexChanged(int index);

private:
    void init();

private:
    Ui::QueryDialog *ui;
    QStringList queryTitles;
    QStringList queryDescriptions;
    QStringList queries;
};

#endif // QUERY_DIALOG_H
