#ifndef LIVRE_H
#define LIVRE_H
#include"QString"
#include <QSqlQuery>
#include <QVariant>
#include <QSqlQueryModel>
class livre
{
    int ID;
    int nbr_pages;
    int prix;
    QString nom_livre;
    QString nom_ecrivain ;
    QString langue;

public:
    livre();
  bool  ajouter();
    livre(int, int, int, QString, QString, QString);
    QSqlQueryModel * afficher();
    void  supprimer(QString ID);
    bool modifier(int, int, int, QString, QString, QString);
    QSqlQueryModel * rechercher(const QString);

};

#endif // LIVRE_H
