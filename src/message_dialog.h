#ifndef MESSAGE_DIALOG_H
#define MESSAGE_DIALOG_H

#include <QWidget>


class MessageDialog
{
public:
    static MessageDialog *instance();
    void message(const QString &title, const QString &text, QWidget *parent = nullptr) const;
    void err(const QString &text, QWidget *parent = nullptr) const;

private:
    MessageDialog();

private:
    static MessageDialog *ins;
};

#endif // MESSAGE_DIALOG_H
