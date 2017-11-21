#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include <QMainWindow>


namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

private:
    bool checkLogin(const QString &username, const QString &password);
    bool doLogin(const QString &username, const QString &password);

private slots:
    void on_pushButton_login_clicked();

private:
    Ui::LoginWindow *ui;
};

#endif // LOGIN_WINDOW_H
