#ifndef COMMANDES_H
#define COMMANDES_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

/*namespace Ui {
class commandes;
}*/

class commandes
{ public:
    commandes() ;
    commandes(int,QString,QString,QString,double);
     bool modifier(int,QString,QString,QString,double);
  QString get_nomlivre() ;
 int get_idclient() ;
  QString get_adresse() ;
  float get_prix ;
  QString get_datedelivraison();
  bool ajouter();
    QSqlQueryModel * afficher();
     bool supprimer(int);
     QSqlQueryModel * rechercher(const QString);

private:
    QString adresse,nomlivre,datedelivraison;
    int idclient;
    double prix ;



/*
public:
    explicit commandes(QWidget *parent = nullptr);
    ~commandes();

private:
    Ui::commandes *ui;*/
};

#endif // COMMANDES_H
