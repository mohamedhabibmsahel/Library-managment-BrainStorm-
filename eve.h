#ifndef EVE_H
#define EVE_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include"QString"
#include <QVariant>

class eve
{
    int Id;
    QString Titre,Date,Adresse;
public:

    eve();
    eve(int,QString,QString,QString);
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int,QString,QString,QString);
    QSqlQueryModel * rechercher(const QString);




//private:

};


#endif // EVE_H
