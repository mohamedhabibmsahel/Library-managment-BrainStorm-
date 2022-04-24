#ifndef STOCK_H
#define STOCK_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDialog>


class stock
{
public:
    stock() ;
    stock(int,QString,QString);
  QString get_categorie() ;
 int get_idstock() ;
  QString get_adresse() ;
  bool ajouter();
    QSqlQueryModel * afficher();
     bool supprimer(int);
     bool modifier(int,QString,QString);
     QSqlQueryModel * rechercher(const QString);

private:
    QString categorie,adresse;
    int idstock ;
};



#endif // STOCK_H
