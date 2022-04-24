#include "agent.h"
#include <QDebug>
#include "login.h"


agent::agent()
{
    CIN=0;
    nom="";
    prenom="";
    mail="";
    role="";
    mdp="";
}


agent::agent(int CIN,QString nom,QString prenom,QString mail, QString mdp,QString role)
{
  this->CIN=CIN;
  this->nom=nom;
  this->prenom=prenom;
  this->mail=mail;
  this->mdp=mdp;
  this->role=role;
}
    QString agent::get_nom(){return  nom;}
    QString agent::get_prenom(){return prenom;}
    QString agent::get_mail(){return mail;}
    QString agent::get_role() {return role;}
    int agent ::get_CIN(){return  CIN;}


bool agent::ajouter()
{
QSqlQuery query;
QString res= QString::number(CIN);
query.prepare("INSERT INTO userr (CIN,NOM,PRENOM,MAIL,PASSWORD,ROLE) "
                    "VALUES (:CIN,:nom,:prenom,:mail,:mdp,:role)");
query.bindValue(":CIN", res);
query.bindValue(":nom", nom);
query.bindValue(":prenom", prenom);
query.bindValue(":mail", mail);
query.bindValue(":mdp", mdp);
query.bindValue(":role", role);

return    query.exec();
}

QSqlQueryModel * agent::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from userr ORDER BY CIN");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Mail"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Mot de passe"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Role"));


    return model;

}

bool agent::supprimer(int CIN)
{
QSqlQuery query;
QString res= QString::number(CIN);
query.prepare("Delete from userr where CIN= :CIN");
query.bindValue(":CIN", res);
return    query.exec();
}

bool agent::modifier(int CIN,QString nom, QString prenom,QString mail,QString mdp,QString role)
{


     QSqlQuery query;
    QString res= QString::number(CIN);
    query.prepare("UPDATE userr SET NOM=:nom ,PRENOM=:prenom,MAIL=:mail,PASSWORD=:mdp,ROLE=:role where CIN=:CIN");
    query.bindValue(":CIN", res);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":mail", mail);
    query.bindValue(":mdp", mdp);
    query.bindValue(":role", role);
     return    query.exec();
}
QSqlQueryModel * agent :: rechercher(QString ch)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QString str="select * from userr where CIN like '"+ch+"%'";
    model->setQuery(str);
    model->setHeaderData(0, Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("Mail"));
    model->setHeaderData(4, Qt::Horizontal,QObject::tr("Mot de passe"));
    model->setHeaderData(4, Qt::Horizontal,QObject::tr("Role"));
    return model;
}
bool agent::verifier_compte(QString mail, QString mdp)
{
    QSqlQuery query;
    QString mdpbd,nomcombd;

    if (mdp=="" || mail=="")
    {
        return  false;
    }
   query.exec("select password,mail FROM userr");
  while (query.next()){

       nomcombd = query.value("mail").toString();
       mdpbd= query.value("password").toString();
       if(mdpbd==mdp && mail==nomcombd)
           return true;
}
  return  false;
}

int agent::verifier_statut(QString mail, QString mdp)
{
    QSqlQuery query;
    QString role;
    query.exec("SELECT ROLE FROM userr WHERE"
               " MAIL= '"+mail+"' AND"
               " PASSWORD= '"+mdp+"'");
    while (query.next())
    {
        role=query.value("ROLE").toString();
    }
    //qDebug()<<role;
    if (role=="Administrateur")
        return 1;
    else if (role=="Agent")
        return 2;
    else return 0;
}
