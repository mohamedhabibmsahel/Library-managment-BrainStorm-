#include <QApplication>
#include <QMessageBox>
#include "connexion.h"
#include <QtDebug>
#include <QApplication>
#include<QSqlQuery>
#include "mainwindow.h"
#include "login.h"

int main(int argc, char *argv[])
   {
    QApplication a(argc, argv);
    Connexion c;
    login w;
    c.ouvrirConnexion();

    w.show();


      return a.exec();
}

