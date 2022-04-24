#ifndef EVENEMENT_H
#define EVENEMENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDialog>
#include "eve.h"

namespace Ui {
class evenement;
}

class evenement : public QDialog
{
    Q_OBJECT

public:
    explicit evenement(QWidget *parent = nullptr);
    ~evenement();

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_ajouter_2_clicked();

    void on_pb_modifier_clicked();

    void on_pushButton_chercher_clicked();

private:
    Ui::evenement *ui;
    eve tmpevenement;
};



#endif // EVENEMENT_H
