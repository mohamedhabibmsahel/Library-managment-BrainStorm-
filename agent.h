#ifndef AGENT_H
#define AGENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class agent
{
public:
    agent();
    agent(int,QString,QString,QString,QString,QString);
    QString get_nom();
    QString get_mail();
    QString get_role();
    QString get_prenom();
    bool verifier_compte(QString,QString);
    int verifier_statut(QString,QString);
    int get_CIN();
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int,QString,QString,QString,QString,QString);
    QSqlQueryModel * rechercher(const QString);
private:
    QString nom,prenom,role, mail,mdp;
    int CIN;


};

#endif // AGENT_H
