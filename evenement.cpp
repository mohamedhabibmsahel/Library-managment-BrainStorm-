#include "evenement.h"
#include "ui_evenement.h"
#include <QMessageBox>

evenement::evenement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::evenement)
{
    ui->setupUi(this);
    ui->tabevenement->setModel(tmpevenement.afficher());
}

evenement::~evenement()
{
    delete ui;
}

void evenement::on_pb_ajouter_clicked()
{
    QString Titre = ui->lineEdit_id->text();
    QString Date= ui->lineEdit_nom->text();
    QString Adresse= ui->lineEdit_prenom->text();
  eve e(Titre,Date,Adresse);
  bool test=e.ajouter();
  if(test)
  {
     ui->tabevenement->setModel(tmpevenement.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("Ajouter un évenement"),
                  QObject::tr("Evenement ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un événement"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}

void evenement::on_pb_supprimer_clicked()
{
    QString Titre = ui->lineEdit_id_2->text();
    bool test=tmpevenement.supprimer(Titre);
    if(test)
    {ui->tabevenement->setModel(tmpevenement.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer un événement"),
                    QObject::tr("Evenement supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un événement"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}


void evenement::on_pb_modifier_clicked()
{
    QString Titre = ui->lineEdit_id_3->text();
    QString Date= ui->lineEdit_date->text();
    QString Adresse= ui->lineEdit_Adresse->text();
  //eve e(Titre,Date,Adresse);
  bool test=tmpevenement.modifier(Titre,Date,Adresse);
  if(test)
  {
     ui->tabevenement->setModel(tmpevenement.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("Modifier un évenement"),
                  QObject::tr("Evenement Modifié.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}
  else
      QMessageBox::critical(nullptr, QObject::tr("Modifier un événement"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}




void evenement::on_pushButton_chercher_clicked()
{
    QString Titre=ui->lineEdit_chercher->text();
    ui->tabevenement->setModel(tmpevenement.afficher2(Titre));
}
