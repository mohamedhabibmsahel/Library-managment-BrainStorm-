#include "livre.h"

livre::livre()
{
    ID=0;
    nbr_pages=0;
    prix=0;
    nom_livre="";
    nom_ecrivain="" ;
    langue="";

}
livre::livre(int ID, int nbr_pages, int prix, QString nom_livre, QString nom_ecrivain,QString langue)
{
    this->ID=ID;
    this->nbr_pages=nbr_pages;
    this->prix=prix;
    this->nom_livre=nom_livre;
    this->nom_ecrivain=nom_ecrivain ;
    this->langue=langue;
}

bool livre :: ajouter()
{
    QSqlQuery query;
    QString res1=QString::number(ID);
    QString res2=QString::number(nbr_pages);
    QString res3=QString::number(prix);
printf("test");
         query.prepare("INSERT INTO livre(ID, NBR_PAGES, PRIX, NOM_LIVRE,NOM_ECRIVAIN, LANGUE) "
                       "VALUES (:ID, :nbr_pages,:prix, :nom_livre, :nom_ecrivain, :langue)");
         query.bindValue(":ID",res1);
         query.bindValue(":nbr_pages",res2);
         query.bindValue(":prix", res3);
         query.bindValue(":nom_livre", nom_livre);
         query.bindValue(":nom_ecrivain", nom_ecrivain);
         query.bindValue(":langue", langue);
         return query.exec();
}

QSqlQueryModel * livre :: afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("Select * from livre order by ID");
    model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("Nombre de pages"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("Nom ecrivain"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("Prix"));
    model->setHeaderData(4, Qt::Horizontal,QObject::tr("Nom livre"));
    model->setHeaderData(5, Qt::Horizontal,QObject::tr("Langue"));
    return model;
}


void livre :: supprimer(QString ID)
{
    QSqlQuery query;
    query.prepare("DELETE FROM livre WHERE ID=:ID");
    query.bindValue(":ID",ID);
    query.exec();

}


bool livre :: modifier(int ID, int nbr_pages, int prix, QString nom_livre, QString nom_ecrivain, QString langue)
{
    QSqlQuery query;
    QString res1=QString::number(ID);
    QString res2=QString::number(nbr_pages);
    QString res3=QString::number(prix);
    query.prepare("UPDATE livre SET NBR_PAGES=:modifnbr_pages,NOM_ECRIVAIN=:modifnom_ecrivains,LANGUE=:modiflangue , PRIX=:modifPrix, NOM_LIVRE=:modifnom_livre WHERE ID =:modifID;");
         query.bindValue(":modifID",ID);
         query.bindValue(":modifPrix",prix);
         query.bindValue(":modifnom_livre",nom_livre);
         query.bindValue(":modifnbr_pages",nbr_pages);
         query.bindValue(":modifnom_ecrivains",nom_ecrivain);
       query.bindValue(":modiflangue",langue);
          /* query.bindValue(":modifID",res1);
         query.bindValue(":modifnbr_pages",res2);
         query.bindValue(":modifprix",res3);*/
         return query.exec();
}
QSqlQueryModel * livre :: rechercher(QString strr)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QString str="Select * from livre where ID like '"+strr+"%'";
    model->setQuery(str);

    model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("Nombre de pages"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("Nom ecrivain"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("Prix"));
    model->setHeaderData(4, Qt::Horizontal,QObject::tr("Nom livre"));
    model->setHeaderData(5, Qt::Horizontal,QObject::tr("Langue"));
    return model;
}

