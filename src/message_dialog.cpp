#include "message_dialog.h"

#include <QMessageBox>


MessageDialog *MessageDialog::ins = new MessageDialog();

MessageDialog::MessageDialog()
{
}


MessageDialog *MessageDialog::instance()
{
    return ins;
}

void MessageDialog::message(const QString &title, const QString &text, QWidget *parent) const
{
    QMessageBox msg(parent);
    msg.setWindowTitle(title);
    msg.setText(text);
    msg.exec();
}

void MessageDialog::err(const QString &text, QWidget *parent) const
{
    message("Error", text, parent);
}
