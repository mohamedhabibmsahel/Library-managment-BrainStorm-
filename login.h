#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "mainwindow.h"
#include "user.h"
#include "agent.h"

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_PBconnexion_clicked();


private:
    Ui::login *ui;
    MainWindow *mainwindow;
    user *User;
    QSound *sound= new QSound(":/img/click.wav");
    agent a;

};

#endif // LOGIN_H
