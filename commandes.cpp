#include "commandes.h"
#include <QString>


commandes::commandes()
{
   idclient=0 ;
   nomlivre="";
    adresse="" ;
    prix =0.0;
    datedelivraison="";

}
commandes::commandes(int idclient ,QString nomlivre,QString datedelivraison,QString adresse,double prix)
{
    this->nomlivre=nomlivre;
    this->idclient=idclient;
    this->adresse=adresse ;
    this->prix=prix ;
    this->datedelivraison=datedelivraison ;


}
QString commandes::get_nomlivre(){return  nomlivre;}
int commandes::get_idclient(){return idclient;}
QString commandes::get_datedelivraison(){return  datedelivraison;}

QString commandes::get_adresse(){return adresse ;}
bool commandes::ajouter()
{
QSqlQuery query;
QString res= QString::number(idclient);
QString res1= QString::number(prix);


query.prepare("INSERT INTO COMMANDES (NOM_LIVRE,ID_CLIENT,ADRESSE,DATEDELIVRAISON,PRIX) "
                    "VALUES (:nomlivre, :idclient, :adresse, :datedelivraison, :prix)");
query.bindValue(":nomlivre",nomlivre);
query.bindValue(":idclient", res);
query.bindValue(":adresse", adresse);
query.bindValue(":datedelivraison", datedelivraison);
query.bindValue(":prix", prix);

return    query.exec();
}
QSqlQueryModel * commandes::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from COMMANDES ORDER BY NOM_LIVRE ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID client"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom du livre "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date de livraison"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix"));
    return model;
}
bool commandes::supprimer(int idclient)
{
QSqlQuery query;
QString res= QString::number(idclient);
query.prepare("Delete from COMMANDES where ID_CLIENT = :idclient ");
query.bindValue(":idclient", res);
return    query.exec();
}
bool commandes::modifier(int idclient,QString nomlivre,QString adresse,QString datedelivraison,double prix)
{
    QSqlQuery query ;
    QString res2=QString::number(idclient) ;
    QString res1= QString::number(prix);
    query.prepare("update COMMANDES set NOM_LIVRE=:nomlivre,ADRESSE=:adresse,DATEDELIVRAISON=:datedelivraison,PRIX=:prix where ID_CLIENT= :idclient ");
    query.bindValue(":idclient", res2);
    query.bindValue(":nomlivre",nomlivre );
    query.bindValue(":adresse", adresse);
    query.bindValue(":datedelivraison", datedelivraison);
    query.bindValue(":prix", res1);
    return  query.exec();
}

QSqlQueryModel * commandes :: rechercher(QString ch)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QString str="select * from commandes where ID_CLIENT like '"+ch+"%'";
    model->setQuery(str);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID client"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom du livre "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date de livraison"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix"));

    return model;
}
