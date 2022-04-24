
#include "stock.h"
#include <QDebug>

/*stock::stock(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stock)
{
    ui->setupUi(this);
}

stock::~stock()
{
    delete ui;
}*/
stock::stock()
{
   idstock=0 ;
    adresse="" ;
     categorie="";


}
stock::stock(int idstock,QString adresse,QString categorie)
{
    this->idstock=idstock;
    this->categorie=categorie;
    this->adresse=adresse ;

}
int stock::get_idstock(){return idstock;}
QString stock::get_adresse(){return  adresse;}
QString stock::get_categorie(){return  categorie;}

bool stock::ajouter()
{
QSqlQuery query;
QString res= QString::number(idstock);

query.prepare("INSERT INTO STOCK (ID,CATEGORIE,ADRESSE) "
                    "VALUES (:idstock, :categorie, :adresse)");

query.bindValue(":idstock", res);
query.bindValue(":categorie",adresse);
query.bindValue(":adresse", categorie);

return    query.exec();
}
QSqlQueryModel * stock::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from STOCK ORDER BY CATEGORIE ");

model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID Stock "));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Catégorie"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));

    return model;
}
bool stock::supprimer(int idstock)
{
QSqlQuery query;
//QString res= QString::number(idd);
query.prepare("Delete from STOCK where ID = :idstock ");
query.bindValue(":idstock", idstock);
return    query.exec();
}
bool stock::modifier(int idstock,QString adresse,QString categorie)
{QSqlQuery query;
  QString res= QString::number(idstock);
   query.prepare("UPDATE STOCK SET ID=:idstock,CATEGORIE=:categorie,ADRESSE=:adresse WHERE ID=:idstock ") ;
   query.bindValue(":idstock", res);
   query.bindValue(":categorie",categorie);
   query.bindValue(":adresse", adresse);

   return    query.exec();
}
QSqlQueryModel * stock :: rechercher(QString ch)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QString str="select * from stock where ID like '"+ch+"%'";
    model->setQuery(str);
    model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID stock"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("Catégorie"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("Adresse"));
    return model;
}
