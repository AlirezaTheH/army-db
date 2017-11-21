#ifndef FORM_DIALOG_H
#define FORM_DIALOG_H

#include <QDialog>

namespace Ui {
class FormDialog;
}

class FormDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FormDialog(QWidget *parent = 0);
    ~FormDialog();

private:
    Ui::FormDialog *ui;
};

#endif // FORM_DIALOG_H
