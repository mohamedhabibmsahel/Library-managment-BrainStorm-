#ifndef CLIENT_H
#define CLIENT_H


#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class client
{public:
    client();
    client(int,QString,QString,int,QString);
    QString get_nom();
    QString get_prenom();
    QString get_adresse();
    int get_id();
    int get_age();
    bool ajouter();
    bool ajouter_fid();
    bool modifier(int,QString,QString,int,QString);
    bool modifier_fid(int,QString,QString,int,QString);
    QSqlQueryModel * afficher();
     QSqlQueryModel * afficher_fid();
    QSqlQueryModel * afficher2(QString);
    QSqlQueryModel * rechercher(const QString);
    QSqlQueryModel * rechercher_fid(const QString);

    bool supprimer(int);
    bool supprimer_fid(int);
    void chercher();
private:
    QString nom,prenom,adresse;
    int id,age;

};



class client_fid
{public:
    client_fid();
    client_fid(int,QString,QString,int,QString,int);
    QString get_nom();
    QString get_prenom();
    QString get_adresse();
    int get_id();
    int get_age();
    bool ajouter_fid();
    bool modifier_fid(int,QString,QString,int,QString,int);
     QSqlQueryModel * afficher_fid();
    QSqlQueryModel * rechercher_fid(const QString);

    bool supprimer(int);
    bool supprimer_fid(int);

private:
    QString nom,prenom,adresse;
    int id,age,num_carte;

};

#endif // CLIENT_H
