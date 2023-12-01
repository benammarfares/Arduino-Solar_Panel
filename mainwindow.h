#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QMessageBox>
#include "employee.h"
#include "session.h"
#include "maintenance.h"
#include "main_voiture.h"
#include <QPrinter>
#include <QPrintDialog>
#include <smtp.h>
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QDialog>
#include <QFileDialog>
#include <QDialog>
#include <QDesktopWidget>
#include <QSettings>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
#include "arduino.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool validerSaisie(QString cineffacer);


private slots:
    //*****client youusef**//

    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_update_clicked();

    void on_pb_avertissement_clicked();

    void on_pb_avertissement_2_clicked();

    void on_pushButton_pdf_client_clicked();

    void on_pushButton_dec_tri_clicked();

    void on_pushButton_croiss_tri_clicked();

    void on_pushButton_search_client_clicked();

    void on_pushButton_effacertout_clie_clicked();

    void on_pushButton_stat_client_clicked();

    void on_pushButton_tester_clientclicked();



    //*****************//
    //********************SESSION raslen****************************//
    void on_pushButton_ajouter_session_clicked();


    void on_pushButton_effacer_session_clicked();


    void on_pushButton_modif_session_clicked();

    void on_pushButton_PDF_session_clicked();

    void on_pushButton_tri_session_2_clicked();

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_mode_charge_session_clicked();

    void on_pushButton_arduino_session_clicked();

    void on_pushButton_stat_session_clicked();

    void on_pushButton_effacer_tout_sess_clicked();

    void on_pushButton_chercher_session_clicked();





    //************************************************************//

    //**********************MAITENANCE ALA****************//

    void update_label();   // slot permettant la mise à jour du label état de la lampe 1,
        // ce slot est lancé à chaque réception d'un message de Arduino
    void on_pushButton_ajout_maint_clicked();
    void on_pushButton_3_maint_clicked();
    void on_pushButton_4_modifier_maint_clicked();
   // void on_lineEdit_3_textChanged(const QString &arg1);

    void on_recherche_textChanged(const QString &arg1);

    void on_comboBox_3_currentIndexChanged(const QString &arg1);

    void on_pushButton_7_maint_clicked();

    void on_pushButton_8_maint_clicked();

    void on_pushButton_9_maint_clicked();
   // void onReadyRead();

//*******************************//

//***** VOITURE FUNCTIONS ********//
    void on_pushButton_supp_voit_clicked();


    void on_pushButton_voiture_clicked();


    void on_pushButton_update_voit_clicked();


    void on_pushButton_PDF_voit_clicked();
    void on_pushButton_historique_clicked();


    void on_pushButton_TRI_voit_clicked();

    void on_lineEdit_recherche_textChanged(const QString &arg1);



    void on_pushButton_STAT_clicked();



    void on_pushButton_charge_clicked();
    void update_card();
    void readCard();



    void on_pushButton_12_clicked();



    //************************//
    //***** VOITURE EMPLOYE JASSER ********//

    void on_pushButton_supprimer_clicked();

    void on_pushButton_ajouter_clicked();


    void on_pushButton_modifier_clicked();


    void on_pushButton_modifier_2_clicked();

    void on_pushButton_tri_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_de_clicked();

    void sendMail();
    void mailSent(QString);
    void browse();
    bool pdf();


    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_clicked();
    //************************//


private:
    Ui::MainWindow *ui;
    employee semp;
    employee e;
     bool cinExists(QString cin);
      void rechercherEmployeParId(QString id);
      QStringList files;
      arduino a;

      //zeyda taa voiture Fares *********
      voiture Etmp;
      int currentBatteryLevel;
      int maxBatteryLevel;

      //** zyeda taa ala maintenance
      QList<maintenance> maintenances;
      maintenance Etmp1 ;
      void trier_par_id_maintenance();
      QByteArray data; // variable contenant les données reçues
      session Etmp2;


};
#endif // MAINWINDOW_H


