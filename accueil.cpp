#include "accueil.h"
#include "ui_accueil.h"
#include "mainwindow.h"
#include <QVBoxLayout>
#include "evenement.h"
Accueil::Accueil(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Accueil)
{
    ui->setupUi(this);
   // ui->tabeevenement->setModel(tmpevenement.afficher());
    QPixmap pix(":/img/image/BackGround.jpg");
    ui->label_BG->setPixmap(pix);
    stackedlayout=new QStackedLayout();
}

Accueil::~Accueil()
{
    delete ui;
}

void Accueil::on_PB_D_clicked()
{
    hide();
}


void Accueil::on_PB_E_clicked()
{
    Evenement=new evenement(this);
    Evenement->show();

}
