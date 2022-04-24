#include "client.h"
#include <QDebug>
client::client()
{
id=0;
nom="";
prenom="";
age=0;
adresse="";
}

client_fid::client_fid()
{
id=0;
nom="";
prenom="";
age=0;
adresse="";
num_carte=0;
}
client::client(int id,QString nom,QString prenom,int age, QString adresse)
{
  this->id=id;
  this->nom=nom;
  this->prenom=prenom;
  this->age=age;
  this->adresse=adresse;
}
client_fid::client_fid(int id,QString nom,QString prenom,int age, QString adresse,int num_carte)
{
  this->id=id;
  this->nom=nom;
  this->prenom=prenom;
  this->age=age;
  this->adresse=adresse;
  this->num_carte=num_carte;
}
QString client::get_nom(){return  nom;}
QString client::get_prenom(){return prenom;}
QString client::get_adresse(){return adresse;}
int client::get_id(){return  id;}
int client::get_age(){return  age;}

bool client::ajouter()
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("INSERT INTO client (ID, NOM, PRENOM, AGE,ADRESSE) "
                    "VALUES (:id, :nom, :prenom, :age, :adresse)");
query.bindValue(":id", res);
query.bindValue(":nom", nom);
query.bindValue(":prenom", prenom);
query.bindValue(":age", age);
query.bindValue(":adresse", adresse);

return    query.exec();
}

bool client_fid::ajouter_fid()
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("INSERT INTO client_fid (ID, NOM, PRENOM, AGE,ADRESSE,NUM_CARTE) "
                    "VALUES (:id, :nom, :prenom, :age, :adresse, :num_carte)");
query.bindValue(":id", res);
query.bindValue(":nom", nom);
query.bindValue(":prenom", prenom);
query.bindValue(":age", age);
query.bindValue(":adresse", adresse);
query.bindValue(":num_carte", num_carte);

return    query.exec();
}
QSqlQueryModel * client::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from client ORDER BY Nom");
model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID client"));
model->setHeaderData(1, Qt::Horizontal,QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal,QObject::tr("Prenom"));
model->setHeaderData(3, Qt::Horizontal,QObject::tr("Age"));
model->setHeaderData(4, Qt::Horizontal,QObject::tr("Adresse"));
    return model;
}

QSqlQueryModel * client_fid::afficher_fid()
{QSqlQueryModel * model1= new QSqlQueryModel();

model1->setQuery("select * from CLIENT_FID ORDER BY Nom");
model1->setHeaderData(0, Qt::Horizontal,QObject::tr("ID client"));
model1->setHeaderData(1, Qt::Horizontal,QObject::tr("Nom"));
model1->setHeaderData(2, Qt::Horizontal,QObject::tr("Prenom"));
model1->setHeaderData(3, Qt::Horizontal,QObject::tr("Age"));
model1->setHeaderData(4, Qt::Horizontal,QObject::tr("Adresse"));
model1->setHeaderData(5, Qt::Horizontal,QObject::tr("Numéro Carte de Fidélité"));
    return model1;
}
QSqlQueryModel * client::afficher2(QString val)
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from client where ID= '"+val+"'or NOM='"+val+"'or PRENOM='"+val+"' ORDER BY Nom" );

model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID client"));
model->setHeaderData(1, Qt::Horizontal,QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal,QObject::tr("Prenom"));
model->setHeaderData(3, Qt::Horizontal,QObject::tr("Age"));
model->setHeaderData(4, Qt::Horizontal,QObject::tr("Adresse"));
    return model;
}

bool client::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from client where ID = :id ");
query.bindValue(":id", res);
return    query.exec();
}

bool client_fid::supprimer_fid(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from client_fid where ID = :id ");
query.bindValue(":id", res);
return    query.exec();
}

bool client::modifier(int id,QString nom,QString prenom,int age,QString adresse)
{
  QSqlQuery query;
  QString res= QString::number(id);
query.prepare("update client set  Nom= :nom, Prenom= :prenom , age= :age, adresse= :adresse where ID= :id") ;
query.bindValue(":id", res);
query.bindValue(":nom", nom);
query.bindValue(":prenom", prenom);
query.bindValue(":age", age);
query.bindValue(":adresse", adresse);
return    query.exec();
}

bool client_fid::modifier_fid(int id,QString nom,QString prenom,int age,QString adresse, int num_carte)
{
  QSqlQuery query;
  QString res= QString::number(id);
query.prepare("update client_fid set  NOM= :nom, PRENOM= :prenom , AGE= :age, ADRESSE= :adresse,NUM_CARTE= :num_carte where ID= :id") ;
query.bindValue(":id", res);
query.bindValue(":nom", nom);
query.bindValue(":prenom", prenom);
query.bindValue(":age", age);
query.bindValue(":adresse", adresse);
query.bindValue(":num_carte", num_carte);
return    query.exec();
}


QSqlQueryModel * client :: rechercher(QString ch)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QString str="select * from client_fid where ID like '"+ch+"%'";
    model->setQuery(str);
    model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID client"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("Age"));
    model->setHeaderData(4, Qt::Horizontal,QObject::tr("Adresse"));
    model->setHeaderData(5, Qt::Horizontal,QObject::tr("Num Carte Fidélité"));

    return model;
}

QSqlQueryModel * client_fid :: rechercher_fid(QString ch)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QString str="select * from client_fid where ID like '"+ch+"%'";
    model->setQuery(str);
    model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID client"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("Age"));
    model->setHeaderData(4, Qt::Horizontal,QObject::tr("Adresse"));
    model->setHeaderData(5, Qt::Horizontal,QObject::tr("Numéro Carte de Fidélité"));
    return model;
}
