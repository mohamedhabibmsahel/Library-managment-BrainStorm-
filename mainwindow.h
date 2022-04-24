#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtMultimedia/qsound.h>
#include <QMainWindow>
#include "livre.h"
#include <QString>
#include "eve.h"
#include "commandes.h"
#include "agent.h"
#include "stock.h"
#include "client.h"
#include <QSystemTrayIcon>
#include <QMessageBox>
#include "arduino.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
livre l;
eve e;
agent a,*ag;
stock s,*st;
client cl,*cll;
QSound *sound= new QSound(":/img/click.wav");
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

void update_label();
void on_events_clicked();

void on_livres_clicked();

void on_retour_clicked();

void on_Sretour_clicked();

void on_Mretour_clicked();

void on_ajouter_clicked();

void on_pushButton_2_clicked();

void on_supprimer_clicked();

void on_modifier_clicked();

void on_ModifierID_clicked();

void on_SupprimerID_clicked();

void on_Mvalider_clicked();

void on_rechercher_textChanged(const QString &arg1);

void on_rechercher_2_textChanged(const QString &arg1);

void on_ajouter_2_clicked();

void on_supprimer_2_clicked();

void on_modifier_2_clicked();

void on_retour_2_clicked();

void on_pb_ajouter_clicked();

void on_ModifierID_2_clicked();

void on_SupprimerID_2_clicked();

void on_Sretour_2_clicked();

void on_retour_3_clicked();

void on_pushButton_4_clicked();

void on_commandes_clicked();

void on_ajouter_5_clicked();

void on_supprimer_5_clicked();

void on_ModifierID_7_clicked();

void on_modifier_5_clicked();

void on_rechercher_5_textChanged(const QString &arg1);

void on_retour_7_clicked();

void on_Sretour_5_clicked();

void on_Mretour_3_clicked();

void on_pushButton_6_clicked();

void on_SupprimerID_5_clicked();

void on_Mvalider_3_clicked();

void on_ajouter_6_clicked();

void on_supprimer_6_clicked();

void on_modifier_6_clicked();

void on_retour_8_clicked();

void on_Sretour_6_clicked();

void on_ModifierID_9_clicked();

void on_SupprimerID_6_clicked();

void on_retour_9_clicked();

void on_rechercher_6_textChanged(const QString &arg1);

void on_ajouter_7_clicked();

void on_supprimer_7_clicked();

void on_modifier_7_clicked();

void on_retour_10_clicked();

void on_pushButton_9_clicked();

void on_Sretour_7_clicked();

void on_ModifierID_10_clicked();

void on_SupprimerID_7_clicked();

void on_retour_11_clicked();

void on_pushButton_10_clicked();

void on_stocks_clicked();

void on_rechercher_7_textChanged(const QString &arg1);

void on_ajouter_8_clicked();

void on_supprimer_8_clicked();

void on_modifier_8_clicked();

void on_retour_12_clicked();

void on_pushButton_11_clicked();

void on_clients_clicked();

void on_Sretour_8_clicked();

void on_SupprimerID_8_clicked();

void on_ModifierID_11_clicked();

void on_retour_13_clicked();

void on_pushButton_12_clicked();

void on_rechercher_8_textChanged(const QString &arg1);

void notif(QString t,QString m);


void on_Excel_livre_clicked();

void on_fichiertxt_eve_clicked();

void on_pushButton_clicked();

void on_fichiertxt_agent_clicked();

void on_fichiertxt_stock_clicked();

void on_fichiertxt_client_clicked();

void on_Dconnexion_clicked();

void on_pushButton_3_clicked();

void on_ajouter_13_clicked();

void on_supprimer_13_clicked();

void on_modifier_13_clicked();

void on_pushButton_5_clicked();

void on_retour_21_clicked();

void on_Sretour_13_clicked();

void on_SupprimerID_13_clicked();

void on_ModifierID_17_clicked();

void on_pushButton_25_clicked();

void on_pushButton_26_clicked();



void on_rechercher_13_textChanged(const QString &arg1);

void on_pushButton_13_clicked();

void on_commandes_2_clicked();

void on_fumer_clicked();

void on_pushButton_16_clicked();

void on_pushButton_15_clicked();

private:
    Ui::MainWindow *ui;
    livre tmplivre;
    eve tmpevenement;
    commandes c,*com;
    livre *li;
    eve *ev;
    QByteArray data1; // variable contenant les données reçues

    Arduino A; // objet temporaire
};
#endif // MAINWINDOW_H
