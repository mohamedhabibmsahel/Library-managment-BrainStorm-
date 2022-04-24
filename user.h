#ifndef USER_H
#define USER_H

#include <QDialog>
#include <QtMultimedia/qsound.h>
#include <QString>
#include "eve.h"
#include "commandes.h"
#include "agent.h"
#include "stock.h"
#include "client.h"
#include "livre.h"
#include <QFile>
#include <QFileDialog>

namespace Ui {
class user;
}

class user : public QDialog
{
    Q_OBJECT
    eve e;
    client c;
    commandes com;
    stock s;
    livre l;
    agent a,*ag;
    QSound *sound= new QSound(":/img/click.wav");
    int x;


public:
    explicit user(QWidget *parent = nullptr);
    ~user();

private slots:
    void on_events_clicked();

    void on_livres_clicked();

    void on_stocks_clicked();

    void on_commandes_clicked();

    void on_clients_clicked();

    void on_agents_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_retour_8_clicked();

    void on_pushButton_7_clicked();

    void on_SupprimerID_6_clicked();

    void on_ModifierID_9_clicked();

    void on_retour_9_clicked();

    void on_pushButton_8_clicked();

    void on_rechercher_textChanged(const QString &arg1);

    void on_pushButton_4_clicked();


    void on_rechercher_2_textChanged(const QString &arg1);

    void on_Sretour_6_clicked();

    void on_deconnexion_clicked();

private:
    Ui::user *ui;
};

#endif // USER_H
