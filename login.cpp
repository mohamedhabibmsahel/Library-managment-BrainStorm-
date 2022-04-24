#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>


login::login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
    this->setWindowTitle("LOGIN");
    setWindowIcon(QIcon(":/img/icon.png"));
    QPixmap pix(":/img/Books.jpg");
    ui->label_pix->setPixmap(pix);
    QPixmap pix_log_img1(":/img/loginImg1.png");
    ui->label_Login_img1->setPixmap(pix_log_img1);
}

login::~login()
{
    delete ui;
}




void login::on_PBconnexion_clicked()
{
    sound->play();
    QString username =ui->LEidentifiant->text();
    QString Password =ui->LEmotdepasse->text();
    bool test=a.verifier_compte(username,Password);
   if (username=="admin" && Password=="admin")
        {
            close();
            User= new user(this);
            User->show();
        }

   else if (test)
        {
            QMessageBox::information(this,"Login","ID et MDP correct");

           if (a.verifier_statut(username,Password)==1)
            {
                close();
                User= new user(this);
                User->show();

            }
            else if (a.verifier_statut(username,Password)==2)
            {

                mainwindow = new MainWindow(this);
                      close();
                      mainwindow->show();
            }

        }
        else
        {
                QMessageBox::critical(this,"Login","ID et MDP non correct");
        }


}
