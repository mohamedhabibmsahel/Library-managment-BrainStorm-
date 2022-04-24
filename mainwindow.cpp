#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QPropertyAnimation>
#include <QDesktopServices>
#include <QUrl>
#include "login.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
     livre l;
    QPixmap bg(":/img/bg1.png");
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).
     ui->setupUi(this);
     ui->label->setPixmap(bg);
this->setWindowTitle("SMART LIBRARY");

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_events_clicked()
{
    sound->play();
    this->ui->stackedWidget->setCurrentIndex(4);
     this->ui->tabevenement->setModel(tmpevenement.afficher());

}

void MainWindow::on_livres_clicked()
{
    sound->play();
    QPropertyAnimation *animation = new QPropertyAnimation(ui->label_20, "geometry");
        animation->setDuration(1000);
        animation->setStartValue(ui->label_20->geometry());
        animation->setEndValue(QRect(370, 120, 300, 300));

        animation->start();
    this->ui->stackedWidget->setCurrentIndex(0);
    ui->afficher->setModel(tmplivre.afficher());
}

void MainWindow::on_retour_clicked()
{
    sound->play();
   this->ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_Sretour_clicked()
{
    sound->play();
  this->ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_Mretour_clicked()
{
    sound->play();
    this->ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_ajouter_clicked()
{
    sound->play();
    this->ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_2_clicked()
{
    sound->play();
    int id=ui->id_ajout->text().toInt();
        int prix=ui->prix_ajout->text().toInt();
        int nbrp=ui->nbr_ajout->text().toInt();
    livre l(id,nbrp,prix,this->ui->nom_ajout->text(),this->ui->nomecri_ajout->text(),this->ui->langue_ajout->text());
   l.ajouter();
    this->ui->stackedWidget->setCurrentIndex(0);
      ui->afficher->setModel(tmplivre.afficher());
      MainWindow::notif("Livre","Ajout d'un livre est reussite");
}

void MainWindow::on_supprimer_clicked()
{
    sound->play();
    this->ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_modifier_clicked()
{
    sound->play();
    this->ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_ModifierID_clicked()
{
    sound->play();
    QSqlQuery qry;
    QString Id=ui->lineEdit_ID->text();
    qry.prepare("select * from livre where ID='"+Id+"'");
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->lineEdit_MID->setText(qry.value(0).toString());
            ui->lineEdit_Mlivre->setText(qry.value(1).toString());
            ui->lineEdit_9->setText(qry.value(2).toString());
            ui->lineEdit_MnbrPage->setText(qry.value(3).toString());
            ui->lineEdit_Mlangue->setText(qry.value(4).toString());
            ui->lineEdit_Mprix->setText(qry.value(5).toString());

        }
    }
    this->ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_SupprimerID_clicked()
{
    sound->play();
    QString id=ui->lineEdit_ID->text();
        livre l;
        l.supprimer(id);
        this->ui->stackedWidget->setCurrentIndex(0);
         ui->afficher->setModel(tmplivre.afficher());
         MainWindow::notif("Livre","Supprision d'un livre est reussite");

}

void MainWindow::on_Mvalider_clicked()
{
    sound->play();
    int id=ui->lineEdit_MID->text().toInt();
        int prix=ui->lineEdit_Mprix->text().toInt();
        int nbrp=ui->lineEdit_MnbrPage->text().toInt();

 l.modifier(id, nbrp, prix, this->ui->lineEdit_Mlivre->text(),this->ui->lineEdit_9->text(),this->ui->lineEdit_Mlangue->text() );

     this->ui->stackedWidget->setCurrentIndex(0);
   ui->afficher->setModel(tmplivre.afficher());
   MainWindow::notif("Livre","Modification d'un livre est reussite");

}

void MainWindow::on_rechercher_textChanged(const QString &arg1)
{
    if (arg1=="")
    ui->afficher->setModel(l.afficher());
    else
     this->ui->afficher->setModel(l.rechercher(arg1));
}


void MainWindow::on_rechercher_2_textChanged(const QString &arg1)
{
    sound->play();
    if (arg1=="")
    ui->tabevenement->setModel(e.afficher());
    else
    this->ui->tabevenement->setModel(e.rechercher(arg1));
}

void MainWindow::on_ajouter_2_clicked()
{
    sound->play();
    this->ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_supprimer_2_clicked()
{
    sound->play();
   this->ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_modifier_2_clicked()
{
    sound->play();
    this->ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_retour_2_clicked()
{
    sound->play();
    this->ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_pb_ajouter_clicked()
{
    sound->play();
    int Id=ui->lineEdit_id_eve->text().toInt();
    QString Titre = ui->lineEdit_titre_eve->text();
    QString Date= ui->lineEdit_date_eve->text();
    QString Adresse= ui->lineEdit_adresse_eve->text();
  eve e(Id,Titre,Date,Adresse);
  e.ajouter();
   ui->tabevenement->setModel(tmpevenement.afficher());
  this->ui->stackedWidget->setCurrentIndex(4);
   MainWindow::notif("Evenement ","Ajout d'un Evenement reussite");
}

void MainWindow::on_ModifierID_2_clicked()
{
    sound->play();
    QSqlQuery qry;
    QString Id=ui->lineEdit_id_d_eve->text();
    qry.prepare("select * from eve where ID='"+Id+"'");
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->lineEdit_Mid->setText(qry.value(0).toString());
            ui->lineEdit_Mtitre->setText(qry.value(1).toString());
            ui->lineEdit_Mdate->setDate(qry.value(2).toDate());
            ui->lineEdit_MAdresse->setText(qry.value(3).toString());

        }
    }
   this->ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_SupprimerID_2_clicked()
{
    sound->play();
    int Id = ui->lineEdit_id_d_eve->text().toInt();
    tmpevenement.supprimer(Id);
    ui->tabevenement->setModel(tmpevenement.afficher());//refresh
    this->ui->stackedWidget->setCurrentIndex(4);
    MainWindow::notif("Evenement ","Supprision d'un Evenement reussite");


}

void MainWindow::on_Sretour_2_clicked()
{
    sound->play();
    this->ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_retour_3_clicked()
{
    sound->play();
    this->ui->stackedWidget->setCurrentIndex(4);

}

void MainWindow::on_pushButton_4_clicked()
{
    sound->play();
    int Id = ui->lineEdit_Mid->text().toInt();
    QString Titre = ui->lineEdit_Mtitre->text();
    QString Date= ui->lineEdit_Mdate->text();
    QString Adresse= ui->lineEdit_MAdresse->text();
  tmpevenement.modifier(Id,Titre,Date,Adresse);
  ui->tabevenement->setModel(tmpevenement.afficher());
    this->ui->stackedWidget->setCurrentIndex(4);
  MainWindow::notif("Evenement ","Modiification d'un Evenement reussite");

}

void MainWindow::on_commandes_clicked()
{
    sound->play();
     ui->tabcommande->setModel(c.afficher());
  this->ui->stackedWidget->setCurrentIndex(8);
}

void MainWindow::on_ajouter_5_clicked()
{
    sound->play();
    this->ui->stackedWidget->setCurrentIndex(9);
}

void MainWindow::on_supprimer_5_clicked()
{
    sound->play();
    this->ui->stackedWidget->setCurrentIndex(10);
}

void MainWindow::on_ModifierID_7_clicked()
{
    sound->play();
    QSqlQuery qry;
    QString idclinet=ui->lineEdit_ID_client_com->text();
    qry.prepare("select * from COMMANDES where ID_CLIENT='"+idclinet+"'");
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->lineEdit_MID_client_com->setText(qry.value(0).toString());
            ui->lineEdit_Mnom_livre_com->setText(qry.value(1).toString());
            ui->lineEdit_MDDL_com->setDate(qry.value(2).toDate());
            ui->lineEdit_MAdre_com->setText(qry.value(3).toString());
            ui->lineEdit_Mprix_com->setText(qry.value(4).toString());

        }
    }
    this->ui->stackedWidget->setCurrentIndex(11);
}

void MainWindow::on_modifier_5_clicked()
{
    sound->play();
    this->ui->stackedWidget->setCurrentIndex(10);
}

void MainWindow::on_rechercher_5_textChanged(const QString &arg1)
{
    sound->play();
    if (arg1=="")
    ui->tabcommande->setModel(c.afficher());
    else
    this->ui->tabcommande->setModel(c.rechercher(arg1));
}

void MainWindow::on_retour_7_clicked()
{
    sound->play();
    this->ui->stackedWidget->setCurrentIndex(8);
}

void MainWindow::on_Sretour_5_clicked()
{
    sound->play();
    this->ui->stackedWidget->setCurrentIndex(8);
}

void MainWindow::on_Mretour_3_clicked()
{
    sound->play();
   this->ui->stackedWidget->setCurrentIndex(8);
}

void MainWindow::on_pushButton_6_clicked()
{
    sound->play();
    int idclient=ui->id_client_aj_com->text().toInt();
    QString nomlivre = ui->Nom_livre_aj_com->text();
    QString datedelivraison= ui->date_livraison_aj_com->text();
    QString Adresse= ui->adresse_aj_com->text();
    double prix=ui->Prix_aj_com->text().toDouble();
  commandes c(idclient,nomlivre,datedelivraison,Adresse,prix);
  c.ajouter();
   ui->tabcommande->setModel(c.afficher());
    this->ui->stackedWidget->setCurrentIndex(8);
   MainWindow::notif("Commande","Ajout d'un commande est reussite");
}

void MainWindow::on_SupprimerID_5_clicked()
{
    sound->play();
    int id=ui->lineEdit_ID_client_com->text().toInt();
        commandes c;
        c.supprimer(id);
        this->ui->stackedWidget->setCurrentIndex(8);
         ui->tabcommande->setModel(c.afficher());
          MainWindow::notif("Commande","Supprision d'un commande est reussite");
}

void MainWindow::on_Mvalider_3_clicked()
{
    sound->play();
    int idclient=ui->lineEdit_MID_client_com->text().toInt();
    QString nomlivre = ui->lineEdit_Mnom_livre_com->text();
    QString datedelivraison= ui->lineEdit_MDDL_com->text();
    QString Adresse= ui->lineEdit_MAdre_com->text();
    double prix=ui->lineEdit_Mprix_com->text().toDouble();
  c.modifier(idclient,nomlivre,datedelivraison,Adresse,prix);
  ui->tabcommande->setModel(c.afficher());
    this->ui->stackedWidget->setCurrentIndex(8);
   MainWindow::notif("Commande","Modification d'un commande est reussite");
}

void MainWindow::on_ajouter_6_clicked()
{
    sound->play();
  this->ui->stackedWidget->setCurrentIndex(13);
}

void MainWindow::on_supprimer_6_clicked()
{
    sound->play();
    this->ui->stackedWidget->setCurrentIndex(14);
}

void MainWindow::on_modifier_6_clicked()
{
    sound->play();
    this->ui->stackedWidget->setCurrentIndex(14);
}


void MainWindow::on_retour_8_clicked()
{
    sound->play();
    this->ui->stackedWidget->setCurrentIndex(12);
}

/*void MainWindow::on_pushButton_7_clicked()
{
    sound->play();
    int CIN=ui->cin_agent_aj->text().toInt();
    QString nom = ui->nom_agent_aj->text();
    QString prenom= ui->prenom_agent_aj->text();
    QString role= ui->role_agent_aj->text();
    QString mail=ui->mail_agent_aj->text();
  agent a(CIN,nom,prenom,role,mail);
  a.ajouter();
   ui->tabagent->setModel(a.afficher());
   this->ui->stackedWidget->setCurrentIndex(12);
   MainWindow::notif("Agent","Ajout d'un agent est reussite");
}*/

void MainWindow::on_Sretour_6_clicked()
{
    sound->play();
    this->ui->stackedWidget->setCurrentIndex(12);
}

void MainWindow::on_ModifierID_9_clicked()
{
    sound->play();
    QSqlQuery qry;
    QString CIN=ui->lineEdit_cin_agent->text();
    qry.prepare("select * from agent where CIN='"+CIN+"'");
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->cin_agent_mod->setText(qry.value(0).toString());
            ui->nom_agent_mod->setText(qry.value(1).toString());
            ui->prenom_agent_mod->setText(qry.value(2).toString());
            ui->role_agent_mod->setText(qry.value(3).toString());
            ui->mail_agent_mod->setText(qry.value(4).toString());

        }
    }
    this->ui->stackedWidget->setCurrentIndex(15);
}

void MainWindow::on_SupprimerID_6_clicked()
{
    sound->play();
    int CIN=ui->lineEdit_cin_agent->text().toInt();
        agent a;
        a.supprimer(CIN);
         ui->tabagent->setModel(a.afficher());
    this->ui->stackedWidget->setCurrentIndex(12);
         MainWindow::notif("Agent","Supprision d'un agent est reussite");
}

void MainWindow::on_retour_9_clicked()
{
    sound->play();
    this->ui->stackedWidget->setCurrentIndex(12);
}

/*void MainWindow::on_pushButton_8_clicked()
{
    sound->play();
    int CIN=ui->cin_agent_mod->text().toInt();
    QString nom = ui->nom_agent_mod->text();
    QString prenom= ui->prenom_agent_mod->text();
    QString role= ui->role_agent_mod->text();
    QString mail=ui->mail_agent_mod->text();
  a.modifier(CIN,nom,prenom,role,mail);
  ui->tabagent->setModel(a.afficher());
    this->ui->stackedWidget->setCurrentIndex(12);
  MainWindow::notif("Agent","Modification d'un agent est reussite");
}*/



void MainWindow::on_rechercher_6_textChanged(const QString &arg1)
{
    sound->play();
    if (arg1=="")
    ui->tabagent->setModel(a.afficher());
    else
    this->ui->tabagent->setModel(a.rechercher(arg1));
}



void MainWindow::on_ajouter_7_clicked()
{
    sound->play();
  this->ui->stackedWidget->setCurrentIndex(17);
}

void MainWindow::on_supprimer_7_clicked()
{
    sound->play();
  this->ui->stackedWidget->setCurrentIndex(18);
}

void MainWindow::on_modifier_7_clicked()
{
    sound->play();
  this->ui->stackedWidget->setCurrentIndex(18);
}

void MainWindow::on_retour_10_clicked()
{
    sound->play();
    this->ui->stackedWidget->setCurrentIndex(16);
}

void MainWindow::on_pushButton_9_clicked()
{
    sound->play();
    int idstock=ui->id_stock_aj->text().toInt();
    QString categorie = ui->categorie_stock_aj->text();
    QString adresse= ui->adresse_stock->text();
  stock s(idstock,categorie,adresse);
  s.ajouter();
   ui->tabstock->setModel(s.afficher());
    this->ui->stackedWidget->setCurrentIndex(16);
   MainWindow::notif("Stock ","Ajout d'un stock est reussite");
}

void MainWindow::on_Sretour_7_clicked()
{
    sound->play();
    this->ui->stackedWidget->setCurrentIndex(16);
}

void MainWindow::on_ModifierID_10_clicked()
{
    sound->play();
    QSqlQuery qry;
    QString idstock=ui->lineEdit_ID_stock->text();
    qry.prepare("select * from stock where ID='"+idstock+"'");
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->id_stock_mod->setText(qry.value(0).toString());
            ui->categorie_stock_mod->setText(qry.value(1).toString());
            ui->adresse_stock_mod->setText(qry.value(2).toString());
        }
    }
    this->ui->stackedWidget->setCurrentIndex(19);
}

void MainWindow::on_SupprimerID_7_clicked()
{
    sound->play();
    int idstock=ui->lineEdit_ID_stock->text().toInt();
        stock s;
        s.supprimer(idstock);
         ui->tabstock->setModel(s.afficher());
    this->ui->stackedWidget->setCurrentIndex(16);
          MainWindow::notif("Stock ","Supprision d'un stock est reussite");
}

void MainWindow::on_retour_11_clicked()
{
    sound->play();
    this->ui->stackedWidget->setCurrentIndex(16);
}

void MainWindow::on_pushButton_10_clicked()
{
    sound->play();
    int idstock=ui->id_stock_mod->text().toInt();
    QString categorie = ui->categorie_stock_mod->text();
    QString adresse= ui->adresse_stock_mod->text();
  s.modifier(idstock,categorie,adresse);
  ui->tabstock->setModel(s.afficher());
    this->ui->stackedWidget->setCurrentIndex(16);
   MainWindow::notif("Stock ","Modification d'un stock est reussite");
}

void MainWindow::on_stocks_clicked()
{
    sound->play();
    ui->tabstock->setModel(s.afficher());
    this->ui->stackedWidget->setCurrentIndex(16);
}

void MainWindow::on_rechercher_7_textChanged(const QString &arg1)
{
    sound->play();
    if (arg1=="")
    ui->tabstock->setModel(s.afficher());
    else
     this->ui->tabstock->setModel(s.rechercher(arg1));
}

void MainWindow::on_ajouter_8_clicked()
{
    sound->play();
  this->ui->stackedWidget->setCurrentIndex(22);
}

void MainWindow::on_supprimer_8_clicked()
{
    sound->play();
 this->ui->stackedWidget->setCurrentIndex(23);
}

void MainWindow::on_modifier_8_clicked()
{
    sound->play();
   this->ui->stackedWidget->setCurrentIndex(24);
}

void MainWindow::on_retour_12_clicked()
{
    sound->play();
    this->ui->stackedWidget->setCurrentIndex(21);
}

void MainWindow::on_pushButton_11_clicked()
{
    sound->play();
    int id=ui->id_client_aj->text().toInt();
    QString nom = ui->nom_client_aj->text();
    QString prenom= ui->prenom_client_aj->text();
    QString adresse= ui->adresse_client_aj->text();
    int age=ui->age_client_aj->text().toInt();
  client cl(id,nom,prenom,age,adresse);
  cl.ajouter();
   ui->tabclient->setModel(cl.afficher());
    this->ui->stackedWidget->setCurrentIndex(20);
   MainWindow::notif("Client","Ajout d'un client est reussite");

}

void MainWindow::on_clients_clicked()
{
    sound->play();
    QPropertyAnimation *animation = new QPropertyAnimation(ui->label_18, "geometry");
        animation->setDuration(1000);
        animation->setStartValue(ui->label_18->geometry());
        animation->setEndValue(QRect(0, 80, 300, 300));

        animation->start();
    ui->tabclient->setModel(cl.afficher());
    this->ui->stackedWidget->setCurrentIndex(20);
}

void MainWindow::on_Sretour_8_clicked()
{
    sound->play();
    this->ui->stackedWidget->setCurrentIndex(21);
}

void MainWindow::on_SupprimerID_8_clicked()
{
    sound->play();
    int id=ui->lineEdit_ID_client_3->text().toInt();
        client cl;
        cl.supprimer(id);
         ui->tabclient_fid->setModel(cl.afficher());
    this->ui->stackedWidget->setCurrentIndex(21);
         MainWindow::notif("Client","Supprision d'un client est reussite");

}

void MainWindow::on_ModifierID_11_clicked()
{
    sound->play();
    QSqlQuery qry;
    QString id=ui->lineEdit_ID_client->text();
    qry.prepare("select * from client where ID='"+id+"'");
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->id_client_mod->setText(qry.value(0).toString());
            ui->nom_client_mod->setText(qry.value(1).toString());
            ui->prenom_client_mod->setText(qry.value(2).toString());
            ui->age_client_mod->setText(qry.value(3).toString());
            ui->adresse_client_mod->setText(qry.value(4).toString());

        }
    }
    this->ui->stackedWidget->setCurrentIndex(24);

}

void MainWindow::on_retour_13_clicked()
{
    sound->play();
    this->ui->stackedWidget->setCurrentIndex(21);

}

void MainWindow::on_pushButton_12_clicked()
{
    sound->play();
    int id=ui->id_client_mod->text().toInt();
    QString nom = ui->nom_client_mod->text();
    QString prenom= ui->prenom_client_mod->text();
    int age= ui->age_client_mod->text().toInt();
    QString adresse=ui->adresse_client_mod->text();
  cl.modifier(id,nom,prenom,age,adresse);
  ui->tabclient->setModel(cl.afficher());
    this->ui->stackedWidget->setCurrentIndex(21);
  MainWindow::notif("Client","Modification d'un client est reussite");

}

void MainWindow::on_rechercher_8_textChanged(const QString &arg1)
{
    sound->play();
    if (arg1=="")
    ui->tabclient->setModel(cl.afficher());
    else
    this->ui->tabclient->setModel(cl.rechercher(arg1));
}

void MainWindow::notif(QString t,QString m)
{

    QPixmap p(32,32);
    p.load("C:/Users/user16/Desktop/notification.png");
    QIcon icon(p);
    QSystemTrayIcon n(icon);
    n.setVisible(true);
    n.showMessage(t,m,QSystemTrayIcon::Information,1000);
}



void MainWindow::on_Excel_livre_clicked()
{
    sound->play();
    QSqlQueryModel  *model = new QSqlQueryModel() ;

    QString linki = QFileDialog::getSaveFileName(this, tr("Export TXT"),"/livre.txt", tr("Comma Separated Values (*.txt)"));


    li=new (livre);

        int x = 0;

        QString exportdata;

        model=li->afficher();

        int counthidden = 0, jint = 0;

        while (jint < model->columnCount()) {

        counthidden+=ui->tabevenement->isColumnHidden(jint);

        jint++;
        }


        while (x < model->columnCount())
        {

        if (!ui->afficher->isColumnHidden(x))
        {

        exportdata.append(model->headerData(x,Qt::Horizontal,Qt::DisplayRole).toString());

        //msgbox(exportdata);

        if (model->columnCount() - x != counthidden)

        exportdata.append(";");

        else

        exportdata.append("\n");

        }
        x++;

        }

        int z = 0;

        exportdata.append("\n");

        while (z < model->rowCount()) {

        x = 0;

        while (x < model->columnCount()) {

        if (!ui->afficher->isColumnHidden(x)) {


        exportdata.append(model->data(model->index(z,x),Qt::DisplayRole).toString());


        if (model->columnCount() - x != counthidden)
        {
            exportdata.append(";");

        }
        else
        {
        exportdata.append("\n");

        }
        }

        x++;

        }
        exportdata.append("\n");

        z++;
        }



           QFile file;

           if (!linki.isEmpty()) {

         file.setFileName(linki);

                if (!file.open(QIODevice::WriteOnly | QIODevice::Text))

                    return;
        }
        QByteArray ttext;

        ttext.append(exportdata);

        file.write(ttext);

        /* closing the file */
}

void MainWindow::on_fichiertxt_eve_clicked()
{
    sound->play();
    QSqlQueryModel  *model = new QSqlQueryModel() ;

    QString linki = QFileDialog::getSaveFileName(this, tr("Export TXT"),"/evenement.txt", tr("Comma Separated Values (*.txt)"));


    com=new (commandes);

        int x = 0;

        QString exportdata;

        model=com->afficher();

        int counthidden = 0, jint = 0;

        while (jint < model->columnCount()) {

        counthidden+=ui->tabcommande->isColumnHidden(jint);

        jint++;
        }


        while (x < model->columnCount())
        {

        if (!ui->tabcommande->isColumnHidden(x))
        {

        exportdata.append(model->headerData(x,Qt::Horizontal,Qt::DisplayRole).toString());

        //msgbox(exportdata);

        if (model->columnCount() - x != counthidden)

        exportdata.append(";");

        else

        exportdata.append("\n");

        }
        x++;

        }

        int z = 0;

        exportdata.append("\n");

        while (z < model->rowCount()) {

        x = 0;

        while (x < model->columnCount()) {

        if (!ui->afficher->isColumnHidden(x)) {


        exportdata.append(model->data(model->index(z,x),Qt::DisplayRole).toString());


        if (model->columnCount() - x != counthidden)
        {
            exportdata.append(";");

        }
        else
        {
        exportdata.append("\n");

        }
        }

        x++;

        }
        exportdata.append("\n");

        z++;
        }



           QFile file;

           if (!linki.isEmpty()) {

         file.setFileName(linki);

                if (!file.open(QIODevice::WriteOnly | QIODevice::Text))

                    return;
        }
        QByteArray ttext;

        ttext.append(exportdata);

        file.write(ttext);
}

void MainWindow::on_pushButton_clicked()
{
    sound->play();
    QSqlQueryModel  *model = new QSqlQueryModel() ;

    QString linki = QFileDialog::getSaveFileName(this, tr("Export TXT"),"/commandes.txt", tr("Comma Separated Values (*.txt)"));


    ev=new (eve);

        int x = 0;

        QString exportdata;

        model=ev->afficher();

        int counthidden = 0, jint = 0;

        while (jint < model->columnCount()) {

        counthidden+=ui->afficher->isColumnHidden(jint);

        jint++;
        }


        while (x < model->columnCount())
        {

        if (!ui->afficher->isColumnHidden(x))
        {

        exportdata.append(model->headerData(x,Qt::Horizontal,Qt::DisplayRole).toString());

        //msgbox(exportdata);

        if (model->columnCount() - x != counthidden)

        exportdata.append(";");

        else

        exportdata.append("\n");

        }
        x++;

        }

        int z = 0;

        exportdata.append("\n");

        while (z < model->rowCount()) {

        x = 0;

        while (x < model->columnCount()) {

        if (!ui->afficher->isColumnHidden(x)) {


        exportdata.append(model->data(model->index(z,x),Qt::DisplayRole).toString());


        if (model->columnCount() - x != counthidden)
        {
            exportdata.append(";");

        }
        else
        {
        exportdata.append("\n");

        }
        }

        x++;

        }
        exportdata.append("\n");

        z++;
        }



           QFile file;

           if (!linki.isEmpty()) {

         file.setFileName(linki);

                if (!file.open(QIODevice::WriteOnly | QIODevice::Text))

                    return;
        }
        QByteArray ttext;

        ttext.append(exportdata);

        file.write(ttext);
}

void MainWindow::on_fichiertxt_agent_clicked()
{
    sound->play();
    QSqlQueryModel  *model = new QSqlQueryModel() ;

    QString linki = QFileDialog::getSaveFileName(this, tr("Export TXT"),"/agent.txt", tr("Comma Separated Values (*.txt)"));


    ag=new (agent);

        int x = 0;

        QString exportdata;

        model=ag->afficher();

        int counthidden = 0, jint = 0;

        while (jint < model->columnCount()) {

        counthidden+=ui->tabagent->isColumnHidden(jint);

        jint++;
        }


        while (x < model->columnCount())
        {

        if (!ui->tabagent->isColumnHidden(x))
        {

        exportdata.append(model->headerData(x,Qt::Horizontal,Qt::DisplayRole).toString());

        //msgbox(exportdata);

        if (model->columnCount() - x != counthidden)

        exportdata.append(";");

        else

        exportdata.append("\n");

        }
        x++;

        }

        int z = 0;

        exportdata.append("\n");

        while (z < model->rowCount()) {

        x = 0;

        while (x < model->columnCount()) {

        if (!ui->afficher->isColumnHidden(x)) {


        exportdata.append(model->data(model->index(z,x),Qt::DisplayRole).toString());


        if (model->columnCount() - x != counthidden)
        {
            exportdata.append(";");

        }
        else
        {
        exportdata.append("\n");

        }
        }

        x++;

        }
        exportdata.append("\n");

        z++;
        }



           QFile file;

           if (!linki.isEmpty()) {

         file.setFileName(linki);

                if (!file.open(QIODevice::WriteOnly | QIODevice::Text))

                    return;
        }
        QByteArray ttext;

        ttext.append(exportdata);

        file.write(ttext);
}

void MainWindow::on_fichiertxt_stock_clicked()
{
    sound->play();
    QSqlQueryModel  *model = new QSqlQueryModel() ;

    QString linki = QFileDialog::getSaveFileName(this, tr("Export TXT"),"/stock.txt", tr("Comma Separated Values (*.txt)"));


    st=new (stock);

        int x = 0;

        QString exportdata;

        model=st->afficher();

        int counthidden = 0, jint = 0;

        while (jint < model->columnCount()) {

        counthidden+=ui->tabstock->isColumnHidden(jint);

        jint++;
        }


        while (x < model->columnCount())
        {

        if (!ui->tabstock->isColumnHidden(x))
        {

        exportdata.append(model->headerData(x,Qt::Horizontal,Qt::DisplayRole).toString());

        //msgbox(exportdata);

        if (model->columnCount() - x != counthidden)

        exportdata.append(";");

        else

        exportdata.append("\n");

        }
        x++;

        }

        int z = 0;

        exportdata.append("\n");

        while (z < model->rowCount()) {

        x = 0;

        while (x < model->columnCount()) {

        if (!ui->afficher->isColumnHidden(x)) {


        exportdata.append(model->data(model->index(z,x),Qt::DisplayRole).toString());


        if (model->columnCount() - x != counthidden)
        {
            exportdata.append(";");

        }
        else
        {
        exportdata.append("\n");

        }
        }

        x++;

        }
        exportdata.append("\n");

        z++;
        }



           QFile file;

           if (!linki.isEmpty()) {

         file.setFileName(linki);

                if (!file.open(QIODevice::WriteOnly | QIODevice::Text))

                    return;
        }
        QByteArray ttext;

        ttext.append(exportdata);

        file.write(ttext);
}

void MainWindow::on_fichiertxt_client_clicked()
{
    sound->play();
    QSqlQueryModel  *model = new QSqlQueryModel() ;

    QString linki = QFileDialog::getSaveFileName(this, tr("Export TXT"),"/client.txt", tr("Comma Separated Values (*.txt)"));


    cll=new (client);

        int x = 0;

        QString exportdata;

        model=cll->afficher();

        int counthidden = 0, jint = 0;

        while (jint < model->columnCount()) {

        counthidden+=ui->tabclient->isColumnHidden(jint);

        jint++;
        }


        while (x < model->columnCount())
        {

        if (!ui->tabclient->isColumnHidden(x))
        {

        exportdata.append(model->headerData(x,Qt::Horizontal,Qt::DisplayRole).toString());

        //msgbox(exportdata);

        if (model->columnCount() - x != counthidden)

        exportdata.append(";");

        else

        exportdata.append("\n");

        }
        x++;

        }

        int z = 0;

        exportdata.append("\n");

        while (z < model->rowCount()) {

        x = 0;

        while (x < model->columnCount()) {

        if (!ui->afficher->isColumnHidden(x)) {


        exportdata.append(model->data(model->index(z,x),Qt::DisplayRole).toString());


        if (model->columnCount() - x != counthidden)
        {
            exportdata.append(";");

        }
        else
        {
        exportdata.append("\n");

        }
        }

        x++;

        }
        exportdata.append("\n");

        z++;
        }



           QFile file;

           if (!linki.isEmpty()) {

         file.setFileName(linki);

                if (!file.open(QIODevice::WriteOnly | QIODevice::Text))

                    return;
        }
        QByteArray ttext;

        ttext.append(exportdata);

        file.write(ttext);
}

void MainWindow::on_Dconnexion_clicked()
{
    sound->play();
    QMessageBox msgBox;
        QPushButton *connectButton = msgBox.addButton(tr("Confirmer"), QMessageBox::ActionRole);
         QPushButton *abortButton = msgBox.addButton(QMessageBox::Cancel);
         msgBox.setWindowTitle("Déconnexion");
         msgBox.setText("Voulez-vous vraiment vous déconnecter ?");
         msgBox.exec();

         if (msgBox.clickedButton() == connectButton)
         {
             msgBox.close();
             close();
             login c;
             c.exec();

         }
         else if (msgBox.clickedButton() == abortButton) {
             msgBox.close();
         }
}

void MainWindow::on_pushButton_3_clicked()
{
    sound->play();
  this->ui->stackedWidget->setCurrentIndex(21);
}

void MainWindow::on_ajouter_13_clicked()
{ sound->play();
    this->ui->stackedWidget->setCurrentIndex(26);

}

void MainWindow::on_supprimer_13_clicked()
{
    sound->play();
        this->ui->stackedWidget->setCurrentIndex(27);
}

void MainWindow::on_modifier_13_clicked()
{
    sound->play();
        this->ui->stackedWidget->setCurrentIndex(28);
}

void MainWindow::on_pushButton_5_clicked()
{
    sound->play();
    QPropertyAnimation *animation = new QPropertyAnimation(ui->label_19, "geometry");
        animation->setDuration(1000);
        animation->setStartValue(ui->label_19->geometry());
        animation->setEndValue(QRect(400, 90, 300, 300));

        animation->start();
    this->ui->stackedWidget->setCurrentIndex(25);
    client_fid cl;
     ui->tabclient_fid->setModel(cl.afficher_fid());

}

void MainWindow::on_retour_21_clicked()
{
    sound->play();
        this->ui->stackedWidget->setCurrentIndex(25);
}

void MainWindow::on_Sretour_13_clicked()
{
    sound->play();
        this->ui->stackedWidget->setCurrentIndex(25);
}

void MainWindow::on_SupprimerID_13_clicked()
{

    sound->play();
    int id=ui->lineEdit_ID_client_3->text().toInt();
        client_fid cl;
        cl.supprimer_fid(id);
         ui->tabclient_fid->setModel(cl.afficher_fid());
    this->ui->stackedWidget->setCurrentIndex(25);
         MainWindow::notif("Client","Suppression d'un client est reussite");
}

void MainWindow::on_ModifierID_17_clicked()
{
    sound->play();
        this->ui->stackedWidget->setCurrentIndex(28);
}

void MainWindow::on_pushButton_25_clicked()
{
    sound->play();
    int id=ui->id_client_aj_3->text().toInt();
    QString nom = ui->nom_client_aj_3->text();
    QString prenom= ui->prenom_client_aj_3->text();
    QString adresse= ui->adresse_client_aj_3->text();
    int age=ui->age_client_aj->text().toInt();
    int num_carte=ui->carte_client_fid->text().toInt();
  client_fid cl(id,nom,prenom,age,adresse,num_carte);
  cl.ajouter_fid();
   ui->tabclient_fid->setModel(cl.afficher_fid());
    this->ui->stackedWidget->setCurrentIndex(25);
   MainWindow::notif("Client","Ajout d'un client est reussite");

}

void MainWindow::on_pushButton_26_clicked()
{client_fid cl;
    sound->play();
    int id=ui->id_client_aj_4->text().toInt();
    QString nom = ui->nom_client_aj_4->text();
    QString prenom= ui->prenom_client_aj_4->text();
    int age= ui->age_client_aj_4->text().toInt();
    QString adresse=ui->adresse_client_aj_4->text();
    int num_carte= ui->carte_client_fid_2->text().toInt();
  cl.modifier_fid(id,nom,prenom,age,adresse,num_carte);
  ui->tabclient_fid->setModel(cl.afficher_fid());
    this->ui->stackedWidget->setCurrentIndex(25);
  MainWindow::notif("Client","Modification d'un client est reussite");
}

void MainWindow::on_rechercher_13_textChanged(const QString &arg1)
{client_fid cl;
    sound->play();
    if (arg1=="")
    ui->tabclient_fid->setModel(cl.afficher_fid());
    else
    this->ui->tabclient_fid->setModel(cl.rechercher_fid(arg1));
}

void MainWindow::on_pushButton_13_clicked()
{
    QString link = "https://mail.google.com";
       QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_commandes_2_clicked()
{
   sound->play();
  this->ui->stackedWidget->setCurrentIndex(29);
}


void MainWindow::on_fumer_clicked()
{
    sound->play();
  A.write_to_arduino("1");
}

void MainWindow::update_label()
{
    data1=A.read_from_arduino();

    if(data1=="1")
    {
  MainWindow::notif("Danger","Detection de fumée");
  this->ui->stackedWidget->setCurrentIndex(29);

    }
    if(data1=="2")
    {
  MainWindow::notif("Service","Client souhaite demander une inforamation ");
   this->ui->stackedWidget->setCurrentIndex(29);
    }

    if(data1=="3")
    {
  MainWindow::notif("Service","Client souhaite chercher un livre");
   this->ui->stackedWidget->setCurrentIndex(29);
    }

    if(data1=="4")
    {
  MainWindow::notif("Service","Client souhaite reclamer");
   this->ui->stackedWidget->setCurrentIndex(29);
    }
    if(data1=="5")
    {
  MainWindow::notif("Poubelle","vider la poubelle");
  this->ui->stackedWidget->setCurrentIndex(29);

    }

}


void MainWindow::on_pushButton_16_clicked()
{
    sound->play();
  A.write_to_arduino("1");
}

void MainWindow::on_pushButton_15_clicked()
{
    sound->play();
  A.write_to_arduino("1");
}
