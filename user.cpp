#include "user.h"
#include "ui_user.h"
#include <QMessageBox>
#include "login.h"

user::user(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::user)
{
    ui->setupUi(this);
    this->setWindowTitle("SMART LIBRARY");
    QPixmap bg(":/img/1.jpg");
    ui->label->setPixmap(bg);
}

user::~user()
{
    delete ui;
}

void user::on_events_clicked()
{
    x=1;
    sound->play();
    this->ui->stackedWidget->setCurrentIndex(0);
      ui->afficher->setModel(e.afficher());

}

void user::on_livres_clicked()
{
    x=2;
    sound->play();
    this->ui->stackedWidget->setCurrentIndex(0);
      ui->afficher->setModel(l.afficher());
}

void user::on_stocks_clicked()
{
    x=3;
    sound->play();
    this->ui->stackedWidget->setCurrentIndex(0);
      ui->afficher->setModel(s.afficher());
}

void user::on_commandes_clicked()
{
    x=4;
    sound->play();
    this->ui->stackedWidget->setCurrentIndex(0);
      ui->afficher->setModel(com.afficher());
}

void user::on_clients_clicked()
{
    x=5;
    sound->play();
    this->ui->stackedWidget->setCurrentIndex(0);
      ui->afficher->setModel(c.afficher());

}

void user::on_agents_clicked()
{
    x=0;
    sound->play();
    this->ui->stackedWidget->setCurrentIndex(1);
      ui->afficher_2->setModel(a.afficher());
}

void user::on_pushButton_clicked()
{
    sound->play();
    this->ui->stackedWidget->setCurrentIndex(2);
}

void user::on_pushButton_2_clicked()
{
    sound->play();
    this->ui->stackedWidget->setCurrentIndex(3);
}

void user::on_pushButton_3_clicked()
{
    sound->play();
    this->ui->stackedWidget->setCurrentIndex(3);
}

void user::on_retour_8_clicked()
{    sound->play();
     this->ui->stackedWidget->setCurrentIndex(1);

}

void user::on_pushButton_7_clicked()
{
    sound->play();
    QString role;
    int CIN=ui->cin_agent_aj->text().toInt();
    QString nom = ui->nom_agent_aj->text();
    QString prenom= ui->prenom_agent_aj->text();
    QString mail=ui->mail_agent_aj->text();
    QString mdp=ui->password_agent_aj->text();
    if(ui->radioButton->isChecked())
       role="Agent";
    if(ui->radioButton_2->isChecked())
       role="Administrateur";
  agent a(CIN,nom,prenom,mail,mdp,role);
  a.ajouter();
   ui->afficher_2->setModel(a.afficher());
   this->ui->stackedWidget->setCurrentIndex(1);
}

void user::on_SupprimerID_6_clicked()
{
    sound->play();
    int CIN=ui->lineEdit_cin_agent->text().toInt();
        agent a;
        a.supprimer(CIN);
         ui->afficher_2->setModel(a.afficher());
    this->ui->stackedWidget->setCurrentIndex(1);
}

void user::on_ModifierID_9_clicked()
{
    sound->play();
    QSqlQuery qry;
    QString role;
    QString CIN=ui->lineEdit_cin_agent->text();
    qry.prepare("select * from userr where CIN='"+CIN+"'");
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->cin_agent_mod->setText(qry.value(0).toString());
            ui->nom_agent_mod->setText(qry.value(1).toString());
            ui->prenom_agent_mod->setText(qry.value(2).toString());
            ui->mail_agent_mod->setText(qry.value(3).toString());
            ui->password_agent_mod->setText(qry.value(4).toString());
            ui->role_agent_mod->setText(qry.value(5).toString());

        }
    }
    this->ui->stackedWidget->setCurrentIndex(4);

}

void user::on_retour_9_clicked()
{
   sound->play();
    this->ui->stackedWidget->setCurrentIndex(3);
}

void user::on_pushButton_8_clicked()
{
    sound->play();
    int CIN=ui->cin_agent_mod->text().toInt();
    QString nom = ui->nom_agent_mod->text();
    QString prenom= ui->prenom_agent_mod->text();
    QString mail=ui->mail_agent_mod->text();
    QString password=ui->password_agent_mod->text();
    QString role= ui->role_agent_mod->text();
  a.modifier(CIN,nom,prenom,mail,password,role);
  ui->afficher_2->setModel(a.afficher());
    this->ui->stackedWidget->setCurrentIndex(1);
}

void user::on_rechercher_textChanged(const QString &arg1)
{
    sound->play();
    if(x==1)
    {
    if (arg1=="")
    ui->afficher->setModel(e.afficher());
    else
    this->ui->afficher->setModel(e.rechercher(arg1));
    }
    if(x==2)
    {
    if (arg1=="")
    ui->afficher->setModel(l.afficher());
    else
    this->ui->afficher->setModel(l.rechercher(arg1));
    }
    if(x==3)
    {
    if (arg1=="")
    ui->afficher->setModel(s.afficher());
    else
    this->ui->afficher->setModel(s.rechercher(arg1));
    }
    if(x==4)
    {
    if (arg1=="")
    ui->afficher->setModel(com.afficher());
    else
    this->ui->afficher->setModel(com.rechercher(arg1));
    }
    if(x==5)
    {
    if (arg1=="")
    ui->afficher->setModel(c.afficher());
    else
    this->ui->afficher->setModel(c.rechercher(arg1));
    }
}

void user::on_pushButton_4_clicked()
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

void user::on_rechercher_2_textChanged(const QString &arg1)
{
    if (arg1=="")
    ui->afficher_2->setModel(a.afficher());
    else
    this->ui->afficher_2->setModel(a.rechercher(arg1));

}

void user::on_Sretour_6_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(1);
}

void user::on_deconnexion_clicked()
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
