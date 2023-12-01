#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employee.h"
#include "voiture.h"
#include "employee.h"
#include "client.h"
#include "mainwindow_voiture.h"
#include <QtWidgets>
#include <QTableWidget>
#include <QRegExp>
#include <QDebug>
#include <QtSql>
#include <QSqlQuery>
#include "login.h"
#include <QSound>
#include <QString>
#include <QRegExpValidator>
#include <QSqlRecord>
#include <QSortFilterProxyModel>
#include <QSqlQueryModel>
#include <QtCharts/QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QGraphicsScene>
#include <QtCharts/QChart>
#include <QPdfWriter>
#include <QPainter>
#include <QRectF>
#include <QList>


namespace Ui {
class voiture;
}


MainWindow::MainWindow(QWidget *parent)

    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);


    //***zyeda taa client***//
        client c;
        QObject::connect(a.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
        ui->tableView_client->setModel(c.afficher());

        //controle de saisie
       ui->lineEdit_id->setValidator(new QIntValidator(1, 99999999, this));
       ui->lineEdit_telephone->setValidator(new QIntValidator(1, 99999999, this));
       ui->lineEdit_cin->setValidator(new QIntValidator(1, 99999999, this));
       ui->lineEdit_supp_id->setValidator(new QIntValidator(1, 99999999, this));
       ui->lineEdit_nom->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]+"), this));
       ui->lineEdit_prenom->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]+"), this));
       ui->lineEdit_adresse->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]+"), this));
       ui->lineEdit_email->setValidator(new QRegExpValidator(QRegExp("[A-Za-z._%+-]+@[A-Za-z.-]+(?=\\.[A-Za-z]{2,})(\\.?[A-Za-z])*"),  this));


    //for email tab
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));
    QObject::connect(a.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
    //le slot update_label suite à la reception du signal readyRead (reception des données).

      //*****FOR SESSION //


    ui->tableView_6->setModel(Etmp2.afficher_session());
    // Find the QTableWidget using its object name
       QTableWidget *tableWidget_4 = findChild<QTableWidget*>("tableWidget_4");

       // Use the QTableWidget object as needed
       int row4 = tableWidget_4->rowCount();


       //control de saisir
       ui->ID_SESSION->setValidator(new QIntValidator(1, 99999999, this));
       //ui->MODEE->setValidator(new QIntValidator(0, 1, this));
       ui->NIV_BATTERIE->setValidator(new QIntValidator(0, 100, this));
       ui->VITESSE->setValidator(new QIntValidator(0, 10, this));
       ui->PRIX->setValidator(new QIntValidator(1, 99999999, this));


    //****************//


    //**************************************FOR MAINT ALA*****
 ui->tableView_5->setModel(Etmp1.afficher_maintenance());
 // Find the QTableWidget using its object name
    QTableWidget *tableWidget_3 = findChild<QTableWidget*>("tableWidget_3");
    // Use the QTableWidget object as needed
     int row2 = tableWidget_3->rowCount();
     ui->lineEdit_idmaintenance->setValidator(new QIntValidator(1,999, this));
     ui->combobox_type->setValidator(new QRegExpValidator(QRegExp("^[a-zA-Z]+(?:\\s+[a-zA-Z]+)*$"),  this));
     ui->lineEdit_Cout->setValidator(new QRegExpValidator(QRegExp("^[\\d]+(\\.[\\d]{1,2})?$"),  this));
     ui->lineEdit_Dure->setValidator(new QRegExpValidator(QRegExp("^([01]?[0-9]|2[0-3]):[0-5][0-9]$"),  this));

    // Find the QTableWidget using its object name

    ui->tableView->setModel(semp.afficher());
       ui->lineEdit_cin->setValidator(new QRegExpValidator(QRegExp("\\d{8}"), this));
       ui->lineEdit->setValidator(new QRegExpValidator(QRegExp("\\d{8}"), this));
       ui->lineEdit_rech->setValidator(new QRegExpValidator(QRegExp("\\d{8}"), this));
       ui->lineEdit_pdf->setValidator(new QRegExpValidator(QRegExp("\\d{8}"), this));
       int ret=a.connect_arduino(); // lancer la connexion à arduino
               switch(ret){
               case(0):qDebug()<< "arduino is available and connected to : "<< a.getarduino_port_name();
                   break;
               case(1):qDebug() << "arduino is available but not connected to :" <<a.getarduino_port_name();
                  break;
               case(-1):qDebug() << "arduino is not available";
               }



               //**************zyeda taa voiture   Fares ******************************
               ui->progressBar_charging->setRange(0, maxBatteryLevel);
               ui->progressBar_charging->setValue(currentBatteryLevel);
               QSqlQuery query;




             ui->tableView_3->setModel(Etmp.afficher_voiture());
            ui->tableView_2->setModel(Etmp.afficher_voiture());

             // Find the QTableWidget using its object name
                QTableWidget *tableWidget = findChild<QTableWidget*>("tableWidget");

                // Use the QTableWidget object as needed
                int row = tableWidget->rowCount();


                //control de saisir
                ui->lineEdit_idvoiture->setValidator(new QIntValidator(1, 99999999, this));
                ui->lineEdit_bat_lvl->setValidator(new QIntValidator(1, 99999999, this));
                ui->lineEdit_batt_cap->setValidator(new QIntValidator(1, 99999999, this));
                ui->lineEdit_quantite->setValidator(new QIntValidator(1, 99999999, this));
                 ui->lineEdit_model->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]+"), this));


 connect(ui->pushButton_TRI_voit, &QPushButton::clicked, this, &MainWindow::on_pushButton_TRI_voit_clicked);


}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::validerSaisie(QString cineffacer)
{
    if(cineffacer.isEmpty()) {
        QMessageBox::warning(nullptr, QObject::tr("Warning"),
                                     QObject::tr("Le champ est vide.\n"
                                                 "Veuillez saisir un CIN."), QMessageBox::Cancel);
        return false;
    }

    if(cineffacer.length() != 8) {
        QMessageBox::warning(nullptr, QObject::tr("Warning"),
                                     QObject::tr("Le CIN doit contenir 8 chiffres."), QMessageBox::Cancel);
        return false;
    }

    bool ok;
    cineffacer.toInt(&ok);
    if(!ok) {
        QMessageBox::warning(nullptr, QObject::tr("Warning"),
                                     QObject::tr("Le CIN doit être un nombre."), QMessageBox::Cancel);
        return false;
    }

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM employe WHERE id_employe = :id_employe");
    query.bindValue(":id_employe", cineffacer);
    query.exec();
    query.next();
    bool cinExists = query.value(0).toInt() > 0;

    if(!cinExists) {
        QMessageBox::warning(nullptr, QObject::tr("Warning"),
                                     QObject::tr("CIN non trouvé dans la base de données."), QMessageBox::Cancel);
        return false;
    }

    return true;
}


void MainWindow::on_pushButton_supprimer_clicked()
{
    QString cineffacer = ui->lineEdit->text();

        if(validerSaisie(cineffacer)) {
            bool test = semp.supprimer(cineffacer);

            if (test) {
                ui->tableView->setModel(semp.afficher());

                QMessageBox::information(nullptr, QObject::tr("OK"),
                                            QObject::tr("Suppression effectuée.\n"
                                                        "Click Cancel to exit."), QMessageBox::Cancel);

            } else {
                QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                            QObject::tr("Suppression non effectuée.\n"
                                                        "Click Cancel to exit."), QMessageBox::Cancel);
            }
        }
}


bool MainWindow::cinExists(QString cinInput)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM employe WHERE id_employe = :id_employe");
    query.bindValue(":id_employe", cinInput);
    query.exec();
    query.next();
    return query.value(0).toInt() > 0;
}


void MainWindow::on_pushButton_ajouter_clicked()
{
    // Get input values from UI elements

    QString cinInput = ui->lineEdit_cin->text();
    QString nom = ui->lineEdit_nom->text();
    QString prenom = ui->lineEdit_prenom->text();
    QString email = ui->lineEdit_email->text();
    QString mdp = ui->lineEdit_mdp->text();
    QString role = ui->comboBox->currentText();
    float salaire = ui->lineEdit_salaire->text().toFloat();
    QDate datedInscription = ui->dateEdit->date();
    QString genre = ui->comboBox_2->currentText();

    // Check if CIN input is valid
    QRegExp cinRegex("[0-9]{8}");
    bool cinIsValid = cinRegex.exactMatch(cinInput);
    QRegExp emailRegex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$");
      bool emailIsValid = emailRegex.exactMatch(email);

    // Check if nom input is valid
    QRegExp nomRegex("[a-zA-Z ]+");
    bool nomIsValid = nomRegex.exactMatch(nom);
    // chek the prenom
    QRegExp prenomRegex("[a-zA-Z ]+");
    bool prenomIsValid = nomRegex.exactMatch(prenom);
    //check email
    // Check if CIN input is already in database
   bool cinIsUnique = !cinExists(cinInput);


    // Add input to database if it is valid and unique
    if (!cinInput.isEmpty() && !nom.isEmpty() && !prenom.isEmpty() && !email.isEmpty() && !mdp.isEmpty() && !role.isEmpty() && salaire != 0 && !genre.isEmpty()) {
        if (cinIsValid && cinIsUnique && nomIsValid  && prenomIsValid && emailIsValid && mdp.contains(QRegExp("^(?=.*[a-z])(?=.*[A-Z]).+$")) && salaire >= 1000 && salaire <= 5000) {
            employee e(cinInput, nom, prenom, email, mdp, role, salaire, datedInscription, genre);
            bool test = e.ajouter();
            if (test) {
                ui->tableView->setModel(semp.afficher());
                // Input added successfully, display success message
                QMessageBox::information(this, "Success", "Input added successfully.");
            } else {
                // Error executing query, display error message
                QMessageBox::warning(this, "Error", "Failed to add input to database.");
            }
        } else {
            // Invalid input or duplicate CIN or invalid nom, display error message
            if (!cinIsUnique) {
                QMessageBox::warning(this, "Error", "CIN is already in use.");
            } else if (!cinIsValid) {
                QMessageBox::warning(this, "Error", "CIN must be a 8-digit number.");
            } else if (!nomIsValid){
                QMessageBox::warning(this, "Error", "Nom can only contain letters and spaces.");
            } else if (!prenomIsValid){
                QMessageBox::warning(this, "Error", "Prenom can only contain letters and spaces.");

            } else if (!emailIsValid){
                QMessageBox::warning(this, "Error", "e-mail invalide.");
            } else if (!mdp.contains(QRegExp("^(?=.*[a-z])(?=.*[A-Z]).+$"))) {
                QMessageBox::warning(this, "Error", "Mot de passe doit contenir au moins un caractere et une lettre majuscule.");
            } else if (salaire < 1000 || salaire > 5000) {
                QMessageBox::warning(this, "Error", "Salaire doit être entre 1000 et 5000.");
            }
        }
    } else {
        // Empty fields, display error message
        QMessageBox::warning(this, "Error", "All fields are required.");
    }
}



void MainWindow::on_pushButton_modifier_clicked()
{
        QString cinInput = ui->lineEdit->text();
        QString nom = ui->lineEdit_nom->text();
        QString prenom = ui->lineEdit_prenom->text();
        QString email = ui->lineEdit_email->text();
        QString mdp = ui->lineEdit_mdp->text();
        QString role = ui->comboBox->currentText();
        float salaire = ui->lineEdit_salaire->text().toFloat();
        QDate datedInscription = ui->dateEdit->date();
        QString genre = ui->comboBox_2->currentText();

        // Check if CIN input is valid
        QRegExp cinRegex("[0-9]{8}");
        bool cinIsValid = cinRegex.exactMatch(cinInput);

        // Check if nom input is valid
        QRegExp nomRegex("[a-zA-Z ]+");
        bool nomIsValid = nomRegex.exactMatch(nom);
        // chek the prenom
        QRegExp prenomRegex("[a-zA-Z ]+");
        bool prenomIsValid = nomRegex.exactMatch(prenom);
        //check email
        QRegExp emailRegex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$");
          bool emailIsValid = emailRegex.exactMatch(email);




        // Add input to database if it is valid and unique
               if (!cinInput.isEmpty() && !nom.isEmpty() && !prenom.isEmpty() && !email.isEmpty() && !mdp.isEmpty() && !role.isEmpty() && salaire != 0 && !genre.isEmpty()) {
                    if (cinIsValid  && nomIsValid && prenomIsValid && mdp.contains(QRegExp("^(?=.*[a-z])(?=.*[A-Z]).+$")) && emailIsValid && salaire >= 1000 && salaire <= 5000) {
                        employee e(cinInput, nom, prenom, email, mdp, role, salaire, datedInscription, genre);
                        bool test = e.modifier();
                        if (test) {
                            ui->tableView->setModel(semp.afficher());
                            // Input added successfully, display success message
                            QMessageBox::information(this, "Success", "Update added successfully.");
                        } else {
                            // Error executing query, display error message
                            QMessageBox::warning(this, "Error", "Failed to update to database.");
                        }
                    } else {
                        // Invalid input or duplicate CIN or invalid nom, display error message
                        if (!cinIsValid) {
                            QMessageBox::warning(this, "Error", "CIN must be a 8-digit number.");
                        } else if (!nomIsValid){
                            QMessageBox::warning(this, "Error", "Nom can only contain letters and spaces.");
                        } else if (!prenomIsValid){
                            QMessageBox::warning(this, "Error", "Prenom can only contain letters and spaces.");

                        } else if (!prenomIsValid){
                            QMessageBox::warning(this, "Error", "prenom invalide.");
                        } else if (!mdp.contains(QRegExp("^(?=.*[a-z])(?=.*[A-Z]).+$"))) {
                            QMessageBox::warning(this, "Error", "Mot de passe doit contenir au moins un caractere et une lettre majuscule.");
                        } else if (!emailIsValid) {
                            QMessageBox::warning(this, "Error", "Email invalide.");
                } else if (salaire < 1000 || salaire > 5000) {
                    QMessageBox::warning(this, "Error", "Salaire doit être entre 1000 et 5000.");
                }
            }
        } else {
            // Empty fields, display error message
            QMessageBox::warning(this, "Error", "All fields are required.");
        }
}
void MainWindow::rechercherEmployeParId(QString id)
{
    QSqlQuery qry;
    qry.prepare("SELECT * FROM employe WHERE id_employe= :id_employe");
    qry.bindValue(":id_employe",id);
    if (qry.exec())
    {
        while(qry.next())
        {
            ui->lineEdit_cin->setText(qry.value(0).toString());
            ui->lineEdit_nom->setText(qry.value(1).toString());
            ui->lineEdit_prenom->setText(qry.value(2).toString());
            ui->lineEdit_email->setText(qry.value(3).toString());
            ui->lineEdit_mdp->setText(qry.value(4).toString());
            ui->comboBox->setEditText(qry.value(5).toString());
            ui->lineEdit_salaire->setText(qry.value(6).toString());
            ui->dateEdit->setWhatsThis(qry.value(7).toString());
            ui->comboBox_2->setEditText(qry.value(8).toString());
        }
    }
    else
    {
        QMessageBox::warning(this,"Error","No information found for this ID");
    }
}
void MainWindow::on_pushButton_modifier_2_clicked()
{
    QString id_employe= ui->lineEdit->text();
       rechercherEmployeParId(id_employe);
}

void MainWindow::on_pushButton_tri_clicked()
{

    QString tri = ui->comboBox_tri->currentText(); // récupérer le choix de l'utilisateur dans le comboBox_tri
    QSqlQueryModel* model;
    if(tri == "De A..Z") // trier par nom dans l'ordre croissant
    {
        employee emp;
        model = emp.afficherTriNom();
    }
    else if(tri == "CIN") // trier par CIN dans l'ordre croissant
    {
        employee emp;
        model = emp.afficherTriCin();
    }

    else if(tri == "De Z..A") // trier par CIN dans l'ordre croissant
    {
        employee emp;
        model = emp.afficherTriNomd();
    }
    else if(tri == "Salaire elevée") // trier par CIN dans l'ordre croissant
    {
        employee emp;
        model = emp.afficherTrisalaire();
    }
    else if(tri == "Salaire bas") // trier par CIN dans l'ordre croissant
    {
        employee emp;
        model = emp.afficherTrisalaired();
    }
    else // si le choix n'est ni "De A..Z" ni "CIN", ne rien faire
    {
        return;
    }
    ui->tableView->setModel(model); // afficher le modèle trié dans le tableView
}



void MainWindow::on_pushButton_5_clicked()
{
    QString id_employe = ui->lineEdit_rech->text();
    employee emp;

    if (emp.recherche(id_employe)) {
        QSqlQuery query;
        query.prepare("SELECT * FROM employe WHERE id_employe=:id_employe");
        query.bindValue(":id_employe", id_employe);
        query.exec();
        if (query.next()) {

            QString info = "<html><head/><body><p><span style=\"font-size:14pt;\"><b>CIN:</b> " + query.value(0).toString() + "</span></p>"
                           "<p><span style=\"font-size:14pt;\"><b>Nom:</b> " + query.value(1).toString() + "</span></p>"
                           "<p><span style=\"font-size:14pt;\"><b>Prénom:</b> " + query.value(2).toString() + "</span></p>"
                           "<p><span style=\"font-size:14pt;\"><b>E-mail:</b> " + query.value(3).toString() + "</span></p>"
                           "<p><span style=\"font-size:14pt;\"><b>Mot de passe:</b> " + query.value(4).toString() + "</span></p>"
                           "<p><span style=\"font-size:14pt;\"><b>Rôle:</b> " + query.value(7).toString() + "</span></p>"
                           "<p><span style=\"font-size:14pt;\"><b>Salaire:</b> " + query.value(6).toString() + "</span></p>"
                           "<p><span style=\"font-size:14pt;\"><b>Genre:</b> " + query.value(8).toString() + "</span></p>"
                           "<p><span style=\"font-size:14pt;\"><b>Date d'inscription:</b> " + query.value(5).toDate().toString("d MMMM yyyy") + "</span></p>"
                           "</body></html>";

            QMessageBox msgBox;
            msgBox.setStyleSheet("QMessageBox{"
                                  "background-color: #5F585F;"
                                  "border: 2px solid #dbdbdb;"
                                  "}"
                                  "QLabel{"
                                  "min-width: 500px;"
                                  "}"
                                  "QPushButton{"
                                  "background-color: black;"
                                  "color: white;"
                                  "border: none;"
                                  "padding: 5px 10px;"
                                  "}");

            msgBox.setText("Informations de l'employé");
            msgBox.setInformativeText(info);
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.exec();
        } else {
            QMessageBox::warning(this, "Avertissement", "L'employé n'existe pas.");
        }
    } else {
        QMessageBox::warning(this, "Avertissement", "L'employé n'existe pas.");
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    QString id_employe = ui->lineEdit_pdf->text();
       employee emp;

       if (emp.recherche(id_employe)) {
           QSqlQuery query;
           query.prepare("SELECT * FROM employe WHERE id_employe=:id_employe");
           query.bindValue(":id_employe", id_employe);
           query.exec();
           if (query.next()) {
               QString nom = query.value(1).toString();
               QString prenom = query.value(2).toString();
               QString email = query.value(3).toString();
               QString role = query.value(7).toString();
               double salaire = query.value(6).toDouble();
               QString genre = query.value(8).toString();
               QDate date = query.value(5).toDate();
               QString html = "<html><head><style>h1{color:#00bfff; font-size:50px;} p{color:#404040; font-size:250px;} strong{color:#FF0000;}</style></head><body>";
               html += "<img src='file:///C:/Users/21692/Downloads/kisspng-computer-icons-physician-login-medicine-user-avatar-5ac45a4d44fe99.2456489015228176132826.jpg' alt='Texte alternatif de l&#39;image' style='position: absolute; top: 0; left: 100;'>";
               html += "<p>Chez CHARGI, nous nous engageons à fournir à nos employés un environnement </p><br>";
               html += "<p>de travail sûr et équitable. </p><br>";
               html += "<p style='font-size:300px'>Nous sommes heureux d'accueillir : <strong style='color:#0000FF'>" + QString(nom.at(0)).toUpper() + nom.mid(1) + " " + QString(prenom.at(0)).toUpper() + prenom.mid(1) + "</strong></p><br>";
               html += "<p><strong>CIN :</strong> " + query.value(0).toString() + "</p><br>";
               html += "<p>-------------------------------------------------------------------------------------------------------------</p><br>";
               html += "<p><strong>E-mail :</strong> " + email + "</p><br>";
               html += "<p>--------------------------------------------------------------------------------------------------------------</p><br>";
               html += "<p><strong>Mot de passe :</strong> " + query.value(4).toString() + "</p><br>";
               html += "<p>--------------------------------------------------------------------------------------------------------------</p><br>";
               html += "<p><strong>Role :</strong> " + role + "</p><br>";
               html += "<p>--------------------------------------------------------------------------------------------------------------</p><br>";
               html += "<p><strong>Salaire :</strong> " + QString::number(salaire) + " DT</p><br>";
               html += "<p>--------------------------------------------------------------------------------------------------------------</p><br>";
               html += "<p><strong>Genre :</strong> " + genre + "</p><br>";
               html += "<p>--------------------------------------------------------------------------------------------------------------</p><br>";
               html += "<p><strong>Date d'inscription :</strong> " + date.toString("d MMMM yyyy") + "</p><br>";
               html += "<p>--------------------------------------------------------------------------------------------------------------</p><br>";

               html += "<p>Chez CHARGI, nous valorisons la diversité et l'inclusion et nous nous efforçons  </p><br>";
               html += "<p>de créer un environnement de travail accueillant pour tous. </p><br>";
               html += "<p>--------------------------------------------------------------------------------------------------------------</p><br>";
               html += "<p>--------------------------------------------------------------------------------------------------------------</p><br>";
               html += "<p>----------------------------------------------TCHARGI----------------------------------------------------</p><br>";





               html += "</body></html>";

               QString filename = nom + "_" + prenom + "_" + QDateTime::currentDateTime().toString("yyyyMMddhhmmss") + ".pdf";
               QPdfWriter writer(filename);
               writer.setPageSize(QPageSize(QPageSize::A4));
               writer.setPageMargins(QMarginsF(20, 20, 20, 20));

               QPainter painter(&writer);
               painter.setPen(Qt::black);
               painter.setFont(QFont("Arial", 100));
               QTextDocument document;
               document.setHtml(html);
               document.drawContents(&painter);

               painter.end();

               QDesktopServices::openUrl(QUrl::fromLocalFile(filename));
           } else {
               QMessageBox::warning(this, "Avertissement", "Aucun employé trouvé avec ce CIN.\n\nATTENTION : Votre Cin doit comporter 8 chiffres");
           }
       } else {
           QMessageBox::warning(this, "Avertissement", "Aucun employé trouvé avec ce CIN.\n\nATTENTION : Votre Cin doit comporter 8 chiffres");
       }

}


void MainWindow::on_pushButton_de_clicked()
{
    // Fermer la fenêtre principale (MainWindow)
        this->close();

        // Afficher la fenêtre de connexion (login)
        login *loginWindow = new login();
        loginWindow->show();
    }
void  MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );

}
void   MainWindow::sendMail()
{
    Smtp* smtp = new Smtp("mohamedjasser.yahmadi@esprit.tn",ui->mail_pass->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("mohamedjasser.yahmadi@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail("mohamedjasser.yahmadi@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}
void   MainWindow::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->rcpt->clear();
    ui->subject->clear();
    ui->file->clear();
    ui->msg->clear();
    ui->mail_pass->clear();
}


void MainWindow::on_pushButton_8_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}
bool employee::pdf()
       {
    QPdfWriter pdf("C:/Users/MSI/Documents/Listes.pdf");
           QPainter painter(&pdf);
          int i = 1800;


               painter.setPen(Qt::darkMagenta);
               painter.setFont(QFont("euphemia", 20));
               painter.drawText(550,650,"                        Liste des employées");
               painter.setPen(Qt::black);
               painter.setFont(QFont("calibri", 10));
               painter.drawRect(100,100,9500,800);
               painter.drawRect(0,1000,9600,500);
               painter.setFont(QFont("consolas", 6));
               painter.drawText(200,1250,"CIN");
               painter.drawText(1300,1250,"Nom");
               painter.drawText(2400,1250,"Prenom");
               painter.drawText(3500,1250,"E-mail");
               painter.drawText(4600,1250,"Mot de passe");
                 painter.drawText(5700,1250,"Date");
                 painter.drawText(6800,1250,"Salaire");
                 painter.drawText(7900,1250,"Rôle");
                 painter.drawText(9000,1250,"Genre");



               QSqlQuery query;
               query.prepare("select * from employe");
               query.exec();
               while (query.next())
               {
                   painter.drawText(200,i,query.value(0).toString());
                   painter.drawText(1300,i,query.value(1).toString());
                   painter.drawText(2400,i,query.value(2).toString());
                   painter.drawText(3500,i,query.value(3).toString());
                   painter.drawText(4600,i,query.value(4).toString());
                   painter.drawText(5700,i,query.value(5).toString());
                   painter.drawText(6800,i,query.value(6).toString());
                   painter.drawText(7900,i,query.value(7).toString());
                   painter.drawText(9000,i,query.value(8).toString());





                  i = i + 600;


               }



               return query.exec();

      }
void MainWindow::on_pushButton_9_clicked()

{
    employee emp;
    emp.pdf();
}

void MainWindow::on_pushButton_clicked()
{   int id = ui->lineEdit_Arduino->text().toInt();
    QString idString = QString::number(id);
    QSqlQuery query;
    query.prepare("select (modee) from sesion where id_session = :id");
    query.bindValue(":id",id);
    bool test = query.exec();
    if (test && query.next()){
        QString alerte = (" Session "+idString+"   Mode " +query.value(0).toString());
        QByteArray x=alerte.toUtf8();
        qDebug() << x ;
        a.write_to_arduino(x);
    }
    else {
        QString alerte = (" Session  "+idString+"   Introuvbable  ");
        QByteArray x=alerte.toUtf8();
        qDebug() << x ;
        a.write_to_arduino(x);
    }


}



//**** voiture Fares******************************************************************//

void MainWindow::readCard()
{

    QByteArray arduinoMsg = a.read_from_arduino();

    qDebug() << "messs messs:" << arduinoMsg;

       int tagPos = arduinoMsg.indexOf(": ");
             if (tagPos < 0) {
                 qDebug() << "Second line:" << tagPos;

                 return;

             }
             QString uidString = arduinoMsg.mid(tagPos + 2, 1);
                      qDebug() << "Second line:" << uidString;
                      bool ok;
                      int uidInt = uidString.toInt(&ok, 16);

                      if (ok) {
                                   qDebug() << "your id is" <<uidInt;
                               }
                      bool idFound = false;

                      while (!idFound) {
                          QSqlQuery query2;
                          query2.prepare("SELECT MATRICULE FROM VOITURE WHERE ID_VOITURE=:id");
                          query2.bindValue(":id", uidInt);
                          if (query2.exec()) {
                              if (query2.next()) {
                                  qDebug() << "SUCCEDED" << uidInt;
                                  idFound = true;
                              }
                          }

}}

void MainWindow::on_pushButton_12_clicked()
{



    QByteArray arduinoMsg = a.read_from_arduino();


       int tagPos = arduinoMsg.indexOf("tag :");
             if (tagPos < 0) {
                 qDebug() << "messs:" << tagPos;

                 return;
             }
             QString uidString = arduinoMsg.mid(tagPos + 6, 1);
                      qDebug() << "Second line:" << uidString;
                      bool ok;
                      int uidInt = uidString.toInt(&ok, 16);

                      if (ok) {
                                   qDebug() << "your id is" <<uidInt;
                               }
                      QSqlQuery query2;
                          query2.prepare("SELECT MATRICULE FROM VOITURE WHERE ID_VOITURE=:id");
                          query2.bindValue(":id", uidInt);
                          if (query2.exec()) {
                              if (query2.next()) {

                                  qDebug() << "SUCCEDED" <<uidInt;

                              }}

    int PRICE;
    int id1 = ui->lineEdit_ID_CAR->text().toInt();

    QSqlQuery query1;
    query1.prepare("SELECT PRIX FROM SESION JOIN VOITURE ON VOITURE.ID_SESSION=SESION.ID_SESSION WHERE VOITURE.ID_VOITURE = :id_voiture");
    query1.bindValue(":id_voiture", id1);

     query1.exec();
    while (query1.next()) {
   PRICE=query1.value("PRIX").toInt();
  qDebug() << "TEST PRIX!" <<PRICE ;
     }
     if (!query1.exec()) {
         qDebug() << "Failed to execute query1!";
         return;
     }


     QByteArray priceData = QByteArray::number(PRICE);
  // create an instance of the arduino object
    a.write_to_arduino(priceData);

}


void MainWindow::on_pushButton_voiture_clicked()
{


    //fuction true meloul taa tous les fonctions
    bool isValid = true;


    // Get the input values
   QString id = ui->lineEdit_idvoiture->text();
   QString model = ui->lineEdit_model->text();
   QString license = ui->lineEdit_license->text();
   QString bat_lvl = ui->lineEdit_bat_lvl->text();
   QString batt_cap = ui->lineEdit_batt_cap->text();
   QString etat = ui->comboBox_etat->currentText();
   QString quantite = ui->lineEdit_quantite->text();

//consructeur voiture parametré
   voiture v(id,model,license,bat_lvl,batt_cap,etat,quantite);


    //get the id2 for the checkid fucntion
    int id2 = ui->lineEdit_idvoiture->text().toInt();


//check for the id_voiture if exist and number or not
    if (v.idExists(id2)) {
        QMessageBox::warning(this, "ID EXISTE", "ID already exists, please enter another ID.");
        isValid = false;
    }


   //check if empty or not

   if ((id.isEmpty()) || (model.isEmpty()) || (license.isEmpty()) ||  (bat_lvl.isEmpty()) ||  (batt_cap.isEmpty()) ||  (etat.isEmpty()) ||  (quantite.isEmpty())) {
       QMessageBox::warning(this, "Invalid Inputs", "Vous devez saisir tous les champs pour ajouter ");
       isValid = false;

   }

      //*****************
  QRegExp etatRegex("[a-zA-Z]+");
  QRegExp licenseRegex("[a-zA-Z]{2}\\d{3}[a-zA-Z]{2}");

    //CONVERTING the lvl_batterie and capacité and quantité to entierr

  int batt_cap_int = ui->lineEdit_batt_cap->text().toInt();
  int bat_lvl_int = ui->lineEdit_bat_lvl->text().toInt();
  int quantite_int = ui->lineEdit_quantite->text().toInt();



          //control saisir sur la quantité a charger

            if (quantite_int > batt_cap_int -bat_lvl_int ) {
                QMessageBox::warning(this, "Invalid Input", "la qunatité que vous voullez charger depasse les limites.");

                isValid = false;

            }


          //control saisir sur la matricule


        if ((!licenseRegex.exactMatch(license))  && (!license.isEmpty())) {
            QMessageBox::warning(this, "Invalid Input", "Matricule format is XX999XX.");
            isValid = false;
        }

        //*****************

    if (isValid) {
        v.setId(id);
        v.setLicensePlate(ui->lineEdit_license->text());
        v.setBatteryLvl(ui->lineEdit_bat_lvl->text());
        v.setBatterCap(ui->lineEdit_batt_cap->text());
        v.setModel(ui->lineEdit_model->text());
        v.setEtat(ui->comboBox_etat->currentText());
        v.setQuantite(ui->lineEdit_quantite->text());


        if (v.insert()) {
            //refresh to afficher
            ui->tableView->setModel(Etmp.afficher_voiture());
            ui->tableView_2->setModel(Etmp.afficher_voiture());

            qDebug() << "Voiture inserted successfully";
            QMessageBox::information(nullptr, QObject::tr("OK"),
                          QObject::tr("Ajout effectué\n"
                                      "Click Cancel to exit ."), QMessageBox::Cancel);


            // Add a new row to the QTableWidget and set the item for each column
            QTableWidget *tableWidget = findChild<QTableWidget*>("tableWidget");
            int row = tableWidget->rowCount();
            tableWidget->insertRow(row);
            // Get the current date/time
            QDateTime currentDateTime = QDateTime::currentDateTime();
            tableWidget->setItem(row, 0, new QTableWidgetItem(v.get_model()));
            tableWidget->setItem(row, 1,new QTableWidgetItem(v.get_Etat()));
            tableWidget->setItem(row, 2, new QTableWidgetItem(v.get_licensePlate()));
            tableWidget->setItem(row, 3, new QTableWidgetItem(v.get_Quantite()));
            tableWidget->setItem(row, 4, new QTableWidgetItem(currentDateTime.toString(Qt::ISODate)));

        } else {
            qDebug() << "Failed to insert voiture into database";
        }
    }
}






void MainWindow::on_pushButton_supp_voit_clicked()
{
    int id1 =ui->lineEdit_2->text().toUInt();

    //QString license = ui->lineEdit->text();
     voiture v; // declare and initialize Etmp

     bool test=Etmp.delete_voiture(id1);

     //get the id2 for the checkid fucntion
     int id2 = ui->lineEdit_idvoiture->text().toInt();


 //check for the id_voiture if exist and number or not


     //get the id2 for the checkid fucntion
     if (!v.idExists(id2)) {


     if (test) {
         ui->tableView_3->setModel(Etmp.afficher_voiture());
         ui->tableView_2->setModel(Etmp.afficher_voiture());

         QMessageBox::information(nullptr, QObject::tr("OK"),
                           QObject::tr("Suppression effectue.\n"
                                       "Cancel to exit."), QMessageBox::Cancel);

     }

     }else {
QMessageBox::warning(this, "ID N EXISTE pas", "ID doesn't exists, please enter another ID.");


}

}








void MainWindow::on_pushButton_update_voit_clicked()
{
    QString id = ui->lineEdit_idvoiture->text();
    QString license = ui->lineEdit_license->text();
    QString bat_lvl = ui->lineEdit_bat_lvl->text();
    QString batt_cap = ui->lineEdit_batt_cap->text();
    QString model = ui->lineEdit_model->text();
    QString etat = ui->comboBox_etat->currentText();
    QString quantite = ui->lineEdit_quantite->text();

    voiture v(id,model,license,bat_lvl,batt_cap,etat,quantite);

    //get the id2 for the checkid fucntion
    int id2 = ui->lineEdit_idvoiture->text().toInt();
    if (v.idExists(id2)) {

     if (v.update(v.get_id())) {
          // Refresh the table view to show the updated data
          ui->tableView->setModel(Etmp.afficher_voiture());
          QMessageBox::information(this, "Update voiture", "Voiture updated successfully.");
      } else {
          QMessageBox::warning(this, "Update voiture", "Failed to update voiture.");
      }}else {

        QMessageBox::warning(this, "ID EXISTE", "ID already exists, please enter another ID.");

    }
  }




void MainWindow::on_pushButton_PDF_voit_clicked()
{
    // Prepare SQL query
    QSqlQuery query;
    query.prepare("SELECT * FROM VOITURE");

    // Execute query
    if (!query.exec()) {
        qDebug() << "Failed to execute query!";
        return;
    }

    // Create PDF document
    QPdfWriter writer("C:/PDF/output.pdf");
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setPageMargins(QMarginsF(20, 20, 20, 20));

    // Create PDF painter
    QPainter painter(&writer);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    painter.setFont(QFont("Arial", 5));



    // Define table cell dimensions
    int cellWidth = 150;
    int cellHeight = 40;

    // Set table position
    int tableX = 20;
    int tableY = 20;

    // Draw table header
    painter.drawText(tableX + cellWidth , tableY, "ID_VOITURE");
    painter.drawText(tableX + cellWidth * 6, tableY , "ID_CLIENT");
    painter.drawText(tableX + cellWidth * 11, tableY , "ID_MAINTENANCE");
    painter.drawText(tableX + cellWidth * 18, tableY, "MATRICULE");
    painter.drawText(tableX + cellWidth * 24, tableY, "BATTERIE_LVL");
    painter.drawText(tableX + cellWidth * 30, tableY, "BATTERIE_CAP");
    painter.drawText(tableX + cellWidth * 36, tableY, "MODEL");
    painter.drawText(tableX + cellWidth * 40, tableY, "ETAT");
    painter.drawText(tableX + cellWidth * 45, tableY, "QUANTITE");
    painter.drawText(tableX + cellWidth * 50, tableY, "ID_SESSION");

    tableY += cellHeight;

    // Loop through query results and draw table cells
    int row = 5;
    while (query.next()) {
        // Draw ID_VOITURE value
        painter.drawText(tableX + cellWidth , tableY + row * cellHeight, query.value(0).toString());
        // Draw ID_CLIENT value
        painter.drawText(tableX + cellWidth * 6, tableY + row * cellHeight, query.value(1).toString());
        // Draw ID_MAINTENANCE value
        painter.drawText(tableX + cellWidth * 11, tableY + row * cellHeight, query.value(2).toString());
        // Draw MATRICULE value
        painter.drawText(tableX + cellWidth * 18, tableY + row * cellHeight, query.value(3).toString());
        // Draw BATTERIE_LVL value
        painter.drawText(tableX + cellWidth * 24, tableY + row * cellHeight, query.value(4).toString());
        // Draw BATTERIE_CAP value
        painter.drawText(tableX + cellWidth * 30, tableY + row * cellHeight, query.value(5).toString());
        // Draw MODEL value
        painter.drawText(tableX + cellWidth * 36, tableY + row * cellHeight, query.value(6).toString());
        // Draw ETAT value
        painter.drawText(tableX + cellWidth * 40, tableY + row * cellHeight, query.value(7).toString());
        // Draw QUANTITE value
        painter.drawText(tableX + cellWidth * 45, tableY + row * cellHeight, query.value(8).toString());
        // Draw ID_SESSION value
        painter.drawText(tableX + cellWidth * 50, tableY + row * cellHeight, query.value(9).toString());

        row++;
        row++;
        row++;
        row++;
    }

    // Clean up
    painter.end();

    qDebug() << "PDF generated!";
}


void MainWindow::on_pushButton_TRI_voit_clicked()
{
    // khdhit el table View mel ui
      QAbstractItemModel *model = ui->tableView_2->model();

      // Create a QSortFilterProxyModel  lel tri
      QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
      proxyModel->setSourceModel(model);

      // Sort by id
      proxyModel->setSortRole(Qt::EditRole);
      proxyModel->sort(0, Qt::AscendingOrder);

      //update lel table view
      ui->tableView_2->setModel(proxyModel);
}




void MainWindow::on_lineEdit_recherche_textChanged(const QString &searchString)
{

    QSqlQueryModel *model = new QSqlQueryModel(this);
       model->setQuery(QString("SELECT * FROM VOITURE WHERE MODEL LIKE '%%1%'").arg(searchString));
       model->setHeaderData(0, Qt::Horizontal, "ID_VOITURE");
       model->setHeaderData(1, Qt::Horizontal, "ID_CLIENT");
       model->setHeaderData(2, Qt::Horizontal, "ID_MAINTENANCE");
       model->setHeaderData(3, Qt::Horizontal, "MATRICULE");
       model->setHeaderData(4, Qt::Horizontal, "BATTERIE_LVL");
       model->setHeaderData(5, Qt::Horizontal, "BATTERIE_CAP");
       model->setHeaderData(6, Qt::Horizontal, "MODEL");
       model->setHeaderData(7, Qt::Horizontal, "ETAT");
       model->setHeaderData(8, Qt::Horizontal, "QUANTITE");
       model->setHeaderData(9, Qt::Horizontal, "ID_SESSION");
       ui->tableView_3->setModel(model);
       ui->tableView_3->show();
}







void MainWindow::on_pushButton_STAT_clicked()
{
    QSqlQuery query;
    QGraphicsScene *scene = new QGraphicsScene(this);

    QPieSeries *series = new QPieSeries();




    if (!query.exec("SELECT COUNT(*) FROM VOITURE")) {
        // Handle the error if the query fails to execute
        qDebug() << "Failed to execute query: " << query.lastError().text();
        return;
    }

    // Fetch the result of the query
    if (query.next()) {
        // Get the total count of cars from the first column of the result
        int totalCount = query.value(0).toInt();
        qDebug() << "Total count of cars: " << totalCount;

        //
        QSqlQuery query("SELECT COUNT(*) FROM VOITURE WHERE ETAT='Maintenance '");
        query.next();
        int maintenanceCount = query.value(0).toInt();
        qDebug() << "Total count of cars: " << maintenanceCount;
        //
        QSqlQuery query2("SELECT COUNT(*) FROM VOITURE WHERE ETAT='Non Maintenance'");
        query2.next();
        int nonMaintenanceCount = query2.value(0).toInt();
        qDebug() << "Total count of cars: " << nonMaintenanceCount;

        // Calculate the percentage of cars in maintenance and non-maintenance status
        double maintenancePercent = 100.0 * maintenanceCount / totalCount;
        double nonMaintenancePercent = 100.0 * nonMaintenanceCount / totalCount;

        qDebug() << "PERCENTAGE: " << maintenancePercent;
        qDebug() << "PERCENTAGE: " << nonMaintenancePercent;

        // Add the data to the series
        QPieSlice *maintenanceSlice = new QPieSlice();
        series->setPieSize(80);
        maintenanceSlice->setLabel(QString("Maintenance\n%1%\n(%2)").arg(maintenancePercent, 0, 'f', 2).arg(maintenanceCount));
        maintenanceSlice->setValue(maintenancePercent);
       maintenanceSlice->setBrush(QColor(50, 205, 50)); // green
       QFont font;
       font.setPointSize(8); //
       maintenanceSlice->setLabelFont(font);
       series->append(maintenanceSlice);



        QPieSlice *nonMaintenanceSlice = new QPieSlice();
        nonMaintenanceSlice->setLabel(QString("Non-Maintenance\n%1%\n(%2)").arg(nonMaintenancePercent, 0, 'f', 2).arg(nonMaintenanceCount));
        nonMaintenanceSlice->setValue(nonMaintenancePercent);
       nonMaintenanceSlice->setBrush(QColor(255, 0, 0)); // red
      nonMaintenanceSlice->setLabelFont(font);
        series->append(nonMaintenanceSlice);




        // format to show the percentage and the value
        series->setLabelsVisible();
        series->setLabelsPosition(QPieSlice::LabelInsideHorizontal);

        // legend
        QChart *chart = new QChart();
        chart->setGeometry(QRectF(0, 0, 600, 400));

        chart->addSeries(series);
        chart->setTitle("Etat Voiture");
        QFont titleFont;
        titleFont.setPointSize(30);
        chart->setTitleFont(titleFont);
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignRight);

        // Set the chart theme and other properties
        chart->setTheme(QChart::ChartThemeLight);
        chart->setAnimationOptions(QChart::AllAnimations);

        // Create a new QChartView widget and set the chart as its chart
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        // Add the QChartView widget to the QGraphicsScene
        QGraphicsProxyWidget *proxy = scene->addWidget(chartView);
        proxy->setPos(0, 0);

        // Set the QGraphicsScene as the scene of the QGraphicsView widget
        ui->graphicsView->setScene(scene);
               ui->graphicsView->fitInView(proxy, Qt::KeepAspectRatio);
    }

}




void MainWindow::on_pushButton_historique_clicked()
{

    //******************* SELECTING MEL VOITURE ******************//

    QSqlQuery query;
    query.prepare("SELECT ID_VOITURE, ID_CLIENT, MATRICULE, MODEL, ID_SESSION, DATE_VOITURE  FROM VOITURE");

    // Execute query
    if (!query.exec()) {
        qDebug() << "Failed to execute query!";
        return;
    }


    //******************* SELECTING MEL SESSION ******************//


    int PRICE;
    QSqlQuery query1;
    query1.prepare("SELECT PRIX FROM SESION JOIN VOITURE ON VOITURE.ID_SESSION=SESION.ID_SESSION");
     query1.exec();
    while (query1.next()) {
   PRICE=query1.value("PRIX").toInt();
  qDebug() << "TEST PRIX!" <<PRICE ;
     }
     if (!query1.exec()) {
         qDebug() << "Failed to execute query1!";
         return;
     }


     //******************* SELECTING MEL CLIENT ******************//


     int prenom;
     int telephone;
     QSqlQuery query2;
     query2.prepare("SELECT PRENOM, TELEPHONE FROM CLIENT JOIN VOITURE ON VOITURE.ID_CLIENT=CLIENT.ID_CLIENT");

      query2.exec();
     while (query2.next()) {

    prenom=query2.value("PRENOM").toInt();
    telephone=query2.value("TELEPHONE").toInt();

   qDebug() << "TEST PRENOM!" <<prenom ;
   qDebug() << "TEST TELEPHONE!" <<telephone ;

      }
     if (!query2.exec()) {
         qDebug() << "Failed to execute query2!";
         return;
     }


     //************************** PDF *************************//

    QPdfWriter writer("C:/PDF/historique.pdf");
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setPageMargins(QMarginsF(20, 20, 20, 20));
    // Create PDF painter
    QPainter painter(&writer);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    painter.setFont(QFont("Arial", 5));

    // Define table cell dimensions
    int cellWidth = 150;
    int cellHeight = 40;

    // Set table position
    int tableX = 20;
    int tableY = 20;

    // Draw table header
    painter.drawText(tableX + cellWidth , tableY, "ID_VOITURE");
    painter.drawText(tableX + cellWidth * 6, tableY , "MATRICULE");
    painter.drawText(tableX + cellWidth * 11, tableY , "MODEL");
    painter.drawText(tableX + cellWidth * 18, tableY, "SESSION");
   painter.drawText(tableX + cellWidth * 24, tableY, "PRIX");
   painter.drawText(tableX + cellWidth * 30, tableY, "CLIENT");
   painter.drawText(tableX + cellWidth * 38, tableY, "TELEPHONE_CLIENT");
   painter.drawText(tableX + cellWidth * 47, tableY, "TIME");



    tableY += cellHeight;

    // Loop through query results and draw table cells
    int row = 5;
    while (query.next() && query2.next() && query1.next()) {
        painter.drawText(tableX + cellWidth , tableY + row * cellHeight, query.value(0).toString());
        painter.drawText(tableX + cellWidth * 6, tableY + row * cellHeight, query.value(2).toString());
       painter.drawText(tableX + cellWidth * 11, tableY + row * cellHeight, query.value(3).toString());
       painter.drawText(tableX + cellWidth * 18, tableY + row * cellHeight, query.value(4).toString());
       painter.drawText(tableX + cellWidth * 24, tableY + row * cellHeight, query1.value(0).toString());
        painter.drawText(tableX + cellWidth * 30, tableY + row * cellHeight, query2.value(0).toString());
       painter.drawText(tableX + cellWidth * 38, tableY + row * cellHeight, query2.value(1).toString());
        painter.drawText(tableX + cellWidth * 18, tableY + row * cellHeight, query.value(5).toString());

        row++;
        row++;
        row++;
        row++;
    }

    // Clean up
    painter.end();

    qDebug() << "historique generated!";

}




void MainWindow::on_pushButton_charge_clicked()
{


    if (ui->pushButton_charge->isEnabled()) {



        int PRICE;
        int id1 = ui->lineEdit_ID_CAR->text().toInt();

        QSqlQuery query1;
        query1.prepare("SELECT PRIX FROM SESION JOIN VOITURE ON VOITURE.ID_SESSION=SESION.ID_SESSION WHERE VOITURE.ID_VOITURE = :id_voiture");
        query1.bindValue(":id_voiture", id1);

         query1.exec();
        while (query1.next()) {
       PRICE=query1.value("PRIX").toInt();
      qDebug() << "TEST PRIX!" <<PRICE ;
         }
         if (!query1.exec()) {
             qDebug() << "Failed to execute query1!";
             return;
         }


         QByteArray priceData = QByteArray::number(PRICE);
      // create an instance of the arduino object
        a.write_to_arduino(priceData);




       int VITESSE;
       QSqlQuery query2;
       query2.prepare("SELECT VITESSE FROM SESION JOIN VOITURE ON VOITURE.ID_SESSION=SESION.ID_SESSION WHERE VOITURE.ID_VOITURE=:idv");
       query2.bindValue(":idv", id1);

        query2.exec();
       while (query2.next()) {

      VITESSE=query2.value("VITESSE").toInt();

     qDebug() << "TEST VITESSE!" <<VITESSE ;


        }
       if (!query2.exec()) {
           qDebug() << "Failed to execute query2!";
           return;
       }



       int QUANT;
       QSqlQuery query3;
       query3.prepare("SELECT QUANTITE FROM VOITURE WHERE ID_VOITURE=:idv");
       query3.bindValue(":idv", id1);

        query3.exec();
       while (query3.next()) {

      QUANT=query3.value("QUANTITE").toInt();

     qDebug() << "TEST QUANTITE!" <<QUANT ;}


int duree;
  if (VITESSE >= 20) {
  double temp = VITESSE * QUANT  / 60;
  duree = static_cast<int>(temp);
       }
  else if (VITESSE<20) {
    double temp = VITESSE * QUANT / 30;
    temp=temp+15;
    duree = static_cast<int>(temp);

  }




  QLCDNumber *lcdNumber = ui->lcdNumber_2;
  lcdNumber->display(duree);



          // Get battery level and max battery level from database using car ID
          QSqlQuery query;
          query.prepare("SELECT BATTERIE_LVL, BATTERIE_CAP ,QUANTITE FROM VOITURE WHERE ID_VOITURE = :id");
         query.bindValue(":id", id1);
          if (!query.exec()) {
              qDebug() << "Failed to retrieve car data from database: " << query.lastError().text();


              return;
          }

          // If car ID not found in database
          if (!query.next()) {
              qDebug() << "Car not found in database.";
              return;
          }

          // Get battery level and max battery level
          int batteryLevel = query.value(0).toInt();
          int batteryCap = query.value(1).toInt();
          int chargeQuantity = query.value(2).toInt();

          currentBatteryLevel = batteryLevel;
          maxBatteryLevel = batteryCap;

          qDebug() << "Battery level before charging: " << currentBatteryLevel;


          // Update progress bar
          ui->progressBar_charging->setRange(0, maxBatteryLevel);
          ui->progressBar_charging->setValue(currentBatteryLevel);


          ui->lcdNumber->setDigitCount(2);
          ui->lcdNumber->display("0");
          int count = 1;
          for (int i = 0; i < chargeQuantity; i++) {
              QThread::sleep(1); // sleep for 1 second
              currentBatteryLevel++;
              ui->progressBar_charging->setValue(currentBatteryLevel);
              ui->lcdNumber->display(QString("%1").arg(count, 2, 10, QChar('0')));
              if (count == duree) { // stop the loop when count reaches duree
                  break;
              }
              count++;
          }

          for (int i = 0; i < chargeQuantity - duree; i++) {
              // Set the range and initial value of the QLabel

                  currentBatteryLevel++;
                  ui->progressBar_charging->setValue(currentBatteryLevel);
              }

          // Update car's battery level in database
          QSqlQuery updateQuery;
          updateQuery.prepare("UPDATE VOITURE SET BATTERIE_LVL= :batteryLevel WHERE ID_VOITURE = :id3");
          updateQuery.bindValue(":batteryLevel", currentBatteryLevel);
          updateQuery.bindValue(":id3", id1);
          if (!updateQuery.exec()) {
              qDebug() << "Failed to update car's battery level in database: " << updateQuery.lastError().text();
              return;
          }
          ui->tableView->setModel(Etmp.afficher_voiture());
          ui->tableView_2->setModel(Etmp.afficher_voiture());


             qDebug() << "Battery level after charging: " << currentBatteryLevel;




}

    else {
            // show an error message
            QMessageBox::warning(this, "Error", "Swipe your Card .");

}}




void MainWindow::update_card()
{




    QByteArray arduinoMsg = a.read_from_arduino();

   qDebug() << "messs messs:" << arduinoMsg;


             if (arduinoMsg.contains("ca")) {
                 QMessageBox::information(nullptr, "Car Detected", "A car has been detected!");
             }

      int tagPos = arduinoMsg.indexOf(": ");


            if (tagPos < 0) {
                 qDebug() << "Second line:" << tagPos;

                return;

           }
            QString uidString = arduinoMsg.mid(tagPos + 2, 1);

                     qDebug() << "Second line:" << uidString;
                     bool ok;
                     int uidInt = uidString.toInt(&ok, 16);
                     bool idFound = false;


                     QString mode;

                     QSqlQuery query5;
                     query5.prepare("SELECT MODEE FROM SESION JOIN VOITURE ON VOITURE.ID_SESSION=SESION.ID_SESSION WHERE VOITURE.ID_VOITURE = :id_voiture");
                     query5.bindValue(":id_voiture", uidInt);

                      query5.exec();
                     if (query5.next()) {
                    mode=query5.value("MODEE").toString();
                   qDebug() << "MODEEE!" <<mode ;
                      }
                      if (!query5.exec()) {
                          qDebug() << "Failed to execute query1!";
                          return;
                      }

if (mode=="repos"){
    QMessageBox::warning(this, "repos", "wait until session is charged");

    QByteArray myByteArray = mode.toUtf8();

                     a.write_to_arduino(myByteArray);
                     ok=false;
}




                     if (ok){
                                 qDebug() << "your id is" <<uidInt;


                    if (!idFound) {
                        QSqlQuery query2;
                        query2.prepare("SELECT MATRICULE FROM VOITURE WHERE ID_VOITURE=:id");
                        query2.bindValue(":id", uidInt);
                        if (query2.exec()) {
                            if (query2.next()){
if(uidInt==8){
    QMessageBox::information(this, "admin is connected", "droit d'acces permi");

    ui->pushButton_charge->setEnabled(true);
}
if(uidInt!=8){

                                qDebug() << "SUCCEDED" << uidInt;

                                QMessageBox::information(this, "Login", "Charge your car now!");

                                int PRICE;

                                QSqlQuery query1;
                                query1.prepare("SELECT PRIX FROM SESION JOIN VOITURE ON VOITURE.ID_SESSION=SESION.ID_SESSION WHERE VOITURE.ID_VOITURE = :id_voiture");
                                query1.bindValue(":id_voiture", uidInt);

                                 query1.exec();
                                if (query1.next()) {
                               PRICE=query1.value("PRIX").toInt();
                              qDebug() << "TEST PRIX!" <<PRICE ;
                                 }
                                 if (!query1.exec()) {
                                     qDebug() << "Failed to execute query1!";
                                     return;
                                 }


                                 QByteArray priceData = QByteArray::number(PRICE);
                              // create an instance of the arduino object
                                a.write_to_arduino(priceData);




                               int VITESSE;
                               QSqlQuery query4;
                               query4.prepare("SELECT VITESSE FROM SESION JOIN VOITURE ON VOITURE.ID_SESSION=SESION.ID_SESSION WHERE VOITURE.ID_VOITURE=:idv");
                               query4.bindValue(":idv", uidInt);

                                query4.exec();
                               if (query4.next()) {

                              VITESSE=query4.value("VITESSE").toInt();

                             qDebug() << "TEST VITESSE!" <<VITESSE ;


                                }
                               if (!query4.exec()) {
                                   qDebug() << "Failed to execute query2!";
                                   return;
                               }



                               int QUANT;
                               QSqlQuery query3;
                               query3.prepare("SELECT QUANTITE FROM VOITURE WHERE ID_VOITURE=:idv");
                               query3.bindValue(":idv", uidInt);

                                query3.exec();
                               if (query3.next()) {

                              QUANT=query3.value("QUANTITE").toInt();

                             qDebug() << "TEST QUANTITE!" <<QUANT ;}


                        int duree;
                          if (VITESSE >= 20) {
                          double temp = VITESSE * QUANT  / 60;
                          duree = static_cast<int>(temp);
                               }
                          else if (VITESSE<20) {
                            double temp = VITESSE * QUANT / 30;
                            temp=temp+15;
                            duree = static_cast<int>(temp);

                          }




                          QLCDNumber *lcdNumber = ui->lcdNumber_2;
                          lcdNumber->display(duree);



                                  // Get battery level and max battery level from database using car ID
                                  QSqlQuery query;
                                  query.prepare("SELECT BATTERIE_LVL, BATTERIE_CAP ,QUANTITE FROM VOITURE WHERE ID_VOITURE = :id");
                                 query.bindValue(":id", uidInt);
                                  if (!query.exec()) {
                                      qDebug() << "Failed to retrieve car data from database: " << query.lastError().text();


                                      return;
                                  }

                                  if (!query.next()) {
                                      qDebug() << "Car not found in database.";
                                      return;
                                  }

                                  int batteryLevel = query.value(0).toInt();
                                  int batteryCap = query.value(1).toInt();
                                  int chargeQuantity = query.value(2).toInt();

                                  currentBatteryLevel = batteryLevel;
                                  maxBatteryLevel = batteryCap;

                                  qDebug() << "Battery level before charging: " << currentBatteryLevel;


                                  // Update progress bar
                                  ui->progressBar_charging->setRange(0, maxBatteryLevel);
                                  ui->progressBar_charging->setValue(currentBatteryLevel);


                                  ui->lcdNumber->setDigitCount(2);
                                  ui->lcdNumber->display("0");
                                  int count = 1;
                                  for (int i = 0; i < chargeQuantity; i++) {
                                      QThread::sleep(1); // sleep for 1 second
                                      currentBatteryLevel++;
                                      ui->progressBar_charging->setValue(currentBatteryLevel);
                                      ui->lcdNumber->display(QString("%1").arg(count, 2, 10, QChar('0')));
                                      if (count == duree) { // stop the loop when count reaches duree
                                          break;
                                      }
                                      count++;
                                  }

                                  for (int i = 0; i < chargeQuantity - duree; i++) {
                                      // Set the range and initial value of the QLabel

                                          currentBatteryLevel++;
                                          ui->progressBar_charging->setValue(currentBatteryLevel);
                                      }

                                  // Update car's battery level in database
                                  QSqlQuery updateQuery;
                                  updateQuery.prepare("UPDATE VOITURE SET BATTERIE_LVL= :batteryLevel WHERE ID_VOITURE = :id3");
                                  updateQuery.bindValue(":batteryLevel", currentBatteryLevel);
                                  updateQuery.bindValue(":id3", uidInt);
                                  if (!updateQuery.exec()) {
                                      qDebug() << "Failed to update car's battery level in database: " << updateQuery.lastError().text();
                                      return;
                                  }
                                  ui->tableView->setModel(Etmp.afficher_voiture());
                                  ui->tableView_2->setModel(Etmp.afficher_voiture());


                                     qDebug() << "Battery level after charging: " << currentBatteryLevel;

 idFound = true;


                        }


                         }  else {

                                QMessageBox::warning(this, "Error", "Your car is no longer registered.");

                            } }}
                         }



}





                                      //***********MAINTENANCE ALA *********//



void MainWindow::update_label()
{
   // qDebug() << "update_label() called";
    // Read the data from the serial port




    //qDebug() << "Data received from Arduino:" << data;

    // Handle the data as needed
    // Convert the data to a string and parse the RFID UID
   // QString uidString = QString(data).trimmed(); // Trim whitespace from the data
   /* if (uidString.length() == 0) {
        // No UID was read
        return;
    }*/
   // qDebug() << "RFID UID:" << uidString;

    // Update the UI with the RFID UID
   // ui->rfidLabel->setText(uidString);
}

/*void MainWindow::onReadyRead()
{
    // Read the data from the serial port
    QByteArray data = A.read_from_arduino();
    qDebug() << "Data received from Arduino:" << data;

    // Handle the data as needed
    // Convert the data to a string and parse the RFID UID
    QString uidString = QString(data).trimmed(); // Trim whitespace from the data
    if (uidString.length() == 0) {
        // No UID was read
        return;
    }
    qDebug() << "RFID UID:" << uidString;

    // Update the UI with the RFID UID
    ui->rfidLabel->setText(uidString);
}
*/


void MainWindow::on_pushButton_ajout_maint_clicked()
{
    maintenance m;



    //function true
    bool isValid = true ;
//id number or not
QString  id = ui->lineEdit_idmaintenance->text();

int  id2 = ui->lineEdit_idmaintenance->text().toInt();

if (m.id_exist(id2)) {
    QMessageBox::warning(this, "ID EXISTE", "id existe deja !! .");
isValid=false;
}

QString id_maintenance = ui->lineEdit_idmaintenance->text();
QString type = ui->combobox_type->currentText();
QString description = ui->plainTextEdit->toPlainText();
QString cout = ui->lineEdit_Cout->text();
QString duree = ui->lineEdit_Dure->text();
QString date_hr = ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss");
QDateTime dateTime = QDateTime::fromString(date_hr, "yyyy-MM-dd hh:mm:ss");
if (id_maintenance.isEmpty() || type.isEmpty() || description.isEmpty() || cout.isEmpty() || duree.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill all fields.");
      isValid=false;
    }
QRegExp dateRegex("^\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2}$");
QRegExp typeRegex("^[a-zA-Z]+(?:\\s+[a-zA-Z]+)*$");
QRegExp descriptionRegex("^[a-zA-Z0-9 ]{0,100}$");
QRegExp coutRegex("^[\\d]+(\\.[\\d]{1,2})?$");
QRegExp dureeRegex("^([0-9]|[01][0-9]|2[0-3]):[0-5][0-9]$");
if (!dateRegex.exactMatch(date_hr)){
    QMessageBox::warning(this, "Invalid Input", "Date must be in the format YYYY-MM-DD HH:MM:SS.");
    isValid = false;
}
if (!dureeRegex.exactMatch(duree)) {
    QMessageBox::warning(this, "Invalid Input", "Duration must be in the format HH:MM.");
    isValid = false;
}

if (!descriptionRegex.exactMatch(description)) {
    QMessageBox::warning(this, "Invalid Input", "Description reached 100 caracters .");
    isValid = false;
}
 if (isValid) {





    m.setid(ui->lineEdit_idmaintenance->text());
   m.settype(ui->combobox_type->currentText());
    m.setdate(ui->dateTimeEdit->dateTime());
    m.setdescription(ui->plainTextEdit->toPlainText());
    m.setcout(ui->lineEdit_Cout->text());
    m.setduree(ui->lineEdit_Dure->text());

/*
    QDateTime selectedDateTime = ui->dateTimeEdit->dateTime();
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString durationText = ui->lineEdit_Dure->text();
    QRegExp durationRegex("^([0-9]|[01][0-9]|2[0-3]):([0-5][0-9])$");
    if (durationRegex.indexIn(durationText) == -1) {
        QMessageBox::warning(nullptr, "Invalid Duration", "Please enter a valid duration in the format \"hh:mm\"");
        return;
    }
    int durationHours = durationRegex.cap(1).toInt();
    int durationMinutes = durationRegex.cap(2).toInt();
    int durationSeconds = durationHours * 3600 + durationMinutes * 60;
   QDateTime previousDateTime;
    if (!m.isValidDT( previousDateTime, selectedDateTime, durationSeconds)) {
        QMessageBox::warning(nullptr, "Invalid Date and Time", "Please select a date and time that is after the previous maintenance record and before the ready time");
        return ;
    }
*/

if (m.insert(m)){
    m.setid(ui->lineEdit_idmaintenance->text());
   m.settype(ui->combobox_type->currentText());
    m.setdate(ui->dateTimeEdit->dateTime());
    m.setdescription(ui->plainTextEdit->toPlainText());
    m.setcout(ui->lineEdit_Cout->text());
    m.setduree(ui->lineEdit_Dure->text());


    QDateTime selectedDateTime = ui->dateTimeEdit->dateTime();
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString durationText = ui->lineEdit_Dure->text();
    QRegExp durationRegex("^([0-9]|[01][0-9]|2[0-3]):([0-5][0-9])$");
    if (durationRegex.indexIn(durationText) == -1) {
        QMessageBox::warning(nullptr, "Invalid Duration", "Please enter a valid duration in the format \"hh:mm\"");
        return;
    }
    int durationHours = durationRegex.cap(1).toInt();
    int durationMinutes = durationRegex.cap(2).toInt();
    int durationSeconds = durationHours * 3600 + durationMinutes * 60;
   QDateTime previousDateTime;
    //if (!m.isValidDT( previousDateTime, selectedDateTime, durationSeconds)) {
        //QMessageBox::warning(nullptr, "Invalid Date and Time", "Please select a date and time that is after the previous maintenance record and before the ready time");
//        return ;
   // }


    ui->tableView_5->setModel(Etmp1.afficher_maintenance());
            qDebug() << "maintenance inserted successfully";
            QMessageBox::information(nullptr, QObject::tr("OK"),
                          QObject::tr("Ajout effectué🙂\n"
                                      "Click Cancel to exit ."), QMessageBox::Cancel);
           // QSound::play("C:/Users/bouch/qt-things/notif.wav");
      QTableWidget *tableWidget_3 = findChild<QTableWidget*>("tableWidget_3");
      int row = tableWidget_3->rowCount();
      tableWidget_3->insertRow(row);
      tableWidget_3->setItem(row, 0, new QTableWidgetItem(m.get_type()));
      tableWidget_3->setItem(row, 1, new QTableWidgetItem(m.get_date().toString("yyyy-MM-dd hh:mm:ss")));
      tableWidget_3->setItem(row, 2, new QTableWidgetItem(m.get_description()));
      tableWidget_3->setItem(row, 3, new QTableWidgetItem(m.get_cout()));
      tableWidget_3->setItem(row, 4, new QTableWidgetItem(m.get_duree()));
      qDebug() << "bouton: 'Ajouter Maintenance'  appuyé";
}
      else {
           qDebug() << "Failed to insert Maintenance !  into database";
      }

 }

 QDateTime now = QDateTime::currentDateTime();
 // Get the selected date and time from the dateTimeEdit widget
 QDateTime selectedDateTime = ui->dateTimeEdit->dateTime();
 // Parse the duration text input into hours and minutes
 QString durationText = ui->lineEdit_Dure->text();
 QRegExp durationRegex("^([0-9]|[01][0-9]|2[0-3]):([0-5][0-9])$");
 if (durationRegex.indexIn(durationText) == -1) {
     QMessageBox::warning(nullptr, "Invalid Duration", "Please enter a valid duration in the format \"hh:mm\"");
     return;
 }
 int durationHours = durationRegex.cap(1).toInt();
 int durationMinutes = durationRegex.cap(2).toInt();
 // Calculate the duration in seconds
 int durationSeconds = durationHours * 3600 + durationMinutes * 60;
 // Calculate the ready time
 QDateTime readyDateTime = selectedDateTime.addSecs(durationSeconds);
 // Format the ready time as "hh:mm"
 QString readyTimeString = readyDateTime.toString("hh:mm");
 int remainingSeconds = durationSeconds;
 QMessageBox remainingTimeMsgBox;
 remainingTimeMsgBox.setWindowTitle("Remaining Time");
 // Create a progress bar to show the remaining time
 QProgressBar *progressBar = new QProgressBar(&remainingTimeMsgBox);
 progressBar->setRange(0, remainingSeconds);
 progressBar->setValue(remainingSeconds);
 remainingTimeMsgBox.layout()->addWidget(progressBar);
 // Create a timer to update the remaining time
 QTimer timer;
 QObject::connect(&timer, &QTimer::timeout, [&]() {
     // Decrement the remaining time by 1 second
     remainingSeconds--;
     progressBar->setValue(remainingSeconds);
     remainingTimeMsgBox.setText("Remaining time: " + QString::number(remainingSeconds) + " seconds");
     // If the remaining time is 0, stop the timer and play a sound
     if (remainingSeconds == 0) {
         QMessageBox messageBox;
         QSound::play("C:/Users/bouch/qt-things/notif.wav"); // replace with path to your sound file
         messageBox.setWindowTitle("Car Ready");
         messageBox.setText("Car ready boi🙂!!");
         messageBox.setIconPixmap(QPixmap("C:/Users/bouch/qt-things/notification-2.png"));
         messageBox.exec();
         timer.stop();
     }
 });
 // Start the timer with a 1-second interval
 timer.start(1000);
 // Show the remaining time message box
 remainingTimeMsgBox.setText("Remaining time: " + QString::number(remainingSeconds) + " seconds");
 remainingTimeMsgBox.exec();


}

void MainWindow::on_pushButton_3_maint_clicked()
{
    int id1 =ui->lineEdit_6->text().toUInt();
     maintenance m ;// declare and initialize Etmp
     bool test=Etmp1.delete_maintenance(id1);
     if (test) {
         ui->tableView_5->setModel(Etmp1.afficher_maintenance());
         QMessageBox::information(nullptr, QObject::tr("OK"),
                           QObject::tr("Suppression effectue🙂.\n"
                                       "Cancel to exit."), QMessageBox::Cancel);
     }
     else
     {
         QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                           QObject::tr("Suppression NON effectue(L'ID n'existe pas dans la base de données!)\n"
                                       "Cancel to exit."), QMessageBox::Cancel);

     }
}
void MainWindow::on_pushButton_9_maint_clicked()
{
     maintenance m ;// declare and initialize Etmp
     bool test=Etmp1.delete_allmaintenance();
     if (test) {
         ui->tableView_5->setModel(Etmp1.afficher_maintenance());
         QMessageBox::information(nullptr, QObject::tr("OK"),
                           QObject::tr("Suppression effectue🙂.\n"
                                       "Cancel to exit."), QMessageBox::Cancel);
     }
}

void MainWindow::on_pushButton_4_modifier_maint_clicked()
{
    QString id = ui->lineEdit_idmaintenance->text();
    QString type = ui->combobox_type->currentText();
    QString description = ui->plainTextEdit->toPlainText();
    QString cout = ui->lineEdit_Cout->text();
    QString duree = ui->lineEdit_Dure->text();
    QString date_hr = ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss");
    QDateTime dateTime = QDateTime::fromString(date_hr, "yyyy-MM-dd hh:mm:ss");
    maintenance m;
    int  id2 = ui->lineEdit_idmaintenance->text().toInt();
    m.setid(id);
    m.settype(type);
    m.setdescription(description);
    m.setcout(cout);
    m.setduree(duree);
    m.setdate(dateTime);
    if (m.id_exist(id2))
    {
    if (m.update_maintenance(m, ui->tableWidget)) {
        // Refresh the table view to show the updated data
        ui->tableView_5->setModel(m.afficher_maintenance());
        QMessageBox::information(this, "Update Maintenance", "Maintenance updated successfully🙂.");
    } else {
        QMessageBox::warning(this, "Update Maintenance", "Failed to update Maintenance.");
    }}else{
        QMessageBox::warning(this, "!", " please enter an ID.");

    }
}
void MainWindow::on_recherche_textChanged(const QString &arg1)
{
    ui->tableView_5->setModel(Etmp1.afficher_search_result(ui->recherche->text() ));
}

void MainWindow::on_comboBox_3_currentIndexChanged(const QString &arg1)
{
    if(ui->comboBox_3->currentText()=="id ↓"){
        qDebug() << "aaaaaaaaaaaaaaaaaaa";

        ui->tableView_5->setModel(Etmp1.afficher_id_decroissant());}
        if(ui->comboBox_3->currentText()=="id ↑"){ ui->tableView_5->setModel(Etmp1.afficher_id_croissant());}
}

void MainWindow::on_pushButton_7_maint_clicked()
{
maintenance m ;
m.telechargerPDF();
{QMessageBox::information(nullptr, QObject::tr("database is open"),
QObject::tr("PDF exported successfully🙂!\n"
"Click Cancel to exit."), QMessageBox::Cancel);}
}

void MainWindow::on_pushButton_8_maint_clicked()
{
    maintenance m ;
    QSqlQuery q1,q2,q3;
   /* QByteArray data = A.getserial()->readAll();
               // qDebug() << "Received data from Arduino:" << data;

                           QString strData(data);
                         //  qDebug() << "Received data:" << strData;
                           int startIndex = strData.indexOf("Card UID:");
                              if (startIndex != -1) {
                                  QString uid = strData.mid(startIndex + 10, 11);
                                  qDebug() << "Card UID:" << uid;
                                  uid.remove(" ");
                                  bool ok;
                                      int decimalValue = uid.toInt(&ok, 16);
                                      qDebug() <<decimalValue ;
                                      QSqlQuery query;
                                        maintenance m;
                                      if (m.test_maintenance(decimalValue)==true)
                                      {
                                          qDebug() << "Id valide";
                                          query.prepare("SELECT * FROM MAINTENANCE  WHERE DATE >= NOW() AND DATE <= DATE_ADD(NOW(), INTERVAL 30 MINUTE)");
                                                                                   query.bindValue(":id", decimalValue);
                                                                                  query.exec();
                                                                               //    if (query.next())
                                                                               //    {
                                                                                       qDebug() << "Resa valide";
                                                                                       QDateTime currentDateTime = QDateTime::currentDateTime();
                                                                                       QString dateTimeStr = currentDateTime.toString("yyyy-MM-dd hh:mm");
                                                                                       qDebug() << dateTimeStr;
                                                                                       //test type panne
                                                                                       int recl;
                                                                                       query.prepare("SELECT* FROM MAINTENANCE WHERE ID_MAINTENANCE=:id");
                                                                                       query.bindValue(":id", decimalValue);
                                                                                       query.exec();
                                                                                       while (query.next()) {
                                                                                            QString tp=query.value("TYPE").toString();
                                                                                            qDebug()<<"Type"<<tp;
                                                                                            if (tp=="Panne")
                                                                                            {
                                                                                                A.write_to_arduino("1");
                                                                                                query.prepare("UPDATE MAINTENANCE SET COUT=:prix WHERE ID_MAINTENANCE=:id");
                                                                                                query.bindValue(":prix", 0);
                                                                                                query.bindValue(":id", decimalValue);
                                                                                                query.exec();

                                                                                              //  A.write_to_arduino(data);
                                                                                            }
                                                                                            else if (tp=="Lavage")
                                                                                            {
                                                                                                A.write_to_arduino("2");
                                                                                                query.prepare("UPDATE MAINTENANCE SET COUT=:prix WHERE ID_MAINTENANCE=:id");
                                                                                                query.bindValue(":prix", 0);
                                                                                                query.bindValue(":id", decimalValue);
                                                                                                query.exec();
                                                                                            }
                                                                                            //qDebug()<<"hello"<<recl;
                                                                                       }

                                                                              /*     }
                                                                                   else
                                                                                   {
                                                      qDebug() << "Resa invalide";
                               }*/
                                    //  }
                           //   else {
                                 /* query.prepare("SELECT* FROM MAINTENANCE WHERE ID_MAINTENANCE=:id");
                                  query.bindValue(":id", decimalValue);
                                  query.exec();
                                  while (query.next()) {*/
                                    //   QDateTime date=query.value("DATE_HR");
                                     //  qDebug()<<"hello"<<date;
                                  //    qDebug() << "Resservation invalide";
                                 // }

                                //  A.write_to_arduino("3");
                           //   }
                            //  }
       // data = A.read_from_arduino();
           qreal tot=0,c1=0,c2=0;
           q1.prepare("SELECT ID_MAINTENANCE FROM MAINTENANCE");
           q1.exec();
           q2.prepare("SELECT ID_MAINTENANCE FROM MAINTENANCE WHERE type='Lavage'");
           q2.exec();
           q3.prepare("SELECT ID_MAINTENANCE FROM MAINTENANCE WHERE type='Panne'");
           q3.exec();
           while (q1.next()){tot++;}
           while (q2.next()){c1++;}
           while (q3.next()){c2++;}
           c1=(c1 * 100)/tot;
           c2=(c2 * 100)/tot;
           QString c3= QString::number(c1) ;
           c3="="+c3+"%";
        QString c4= QString::number(c2) ;
        c4="="+c4+"%";
         QString etat1="L" ;
         etat1=etat1+c3 ;
         QString etat2="P" ;
         etat2=etat2+c4 ;
           //Création des pie series
         QPieSeries *series = new QPieSeries();
         series->append(etat1,c1);
         series->append(etat2,c2);
         //Creation d'un charte
         QChart *chart  =new QChart();
         chart->setTitle("Les résultats:");
         chart->addSeries(series);
         chart->legend()->show();
          chart->setBackgroundBrush(QColor(252, 236, 218, 0));
         QChartView *chartView;
         chartView = new QChartView(chart,ui->graphicsView_4);
         chartView->setRenderHint(QPainter::Antialiasing);
         chartView->setMinimumSize(280,200);
         chartView->show();

}



                             //************************ SESSION RASLEN*******************//


void MainWindow::on_pushButton_ajouter_session_clicked()
{


    //fuction true meloul taa tous les fonctions
    bool isValid = true;


    // Get the input values
   QString ID_SESSION = ui->ID_SESSION->text();
   QString MODEE = ui->MODEE->currentText();
   QString NIV_BATTERIE = ui->NIV_BATTERIE->text();
   QString VITESSE = ui->VITESSE->text();
   QString HAPPY_HOUR = ui->HAPPY_HOUR->currentText();
   QString PRIX = ui->PRIX->text();

//consructeur voiture parametré
session s(ID_SESSION,MODEE,NIV_BATTERIE,VITESSE,HAPPY_HOUR,PRIX );


    //get the id2 for the checkid fucntion
    int id2 = ui->ID_SESSION->text().toInt();


//check for the id_voiture if exist and number or not
    if (s.idExists(id2)) {
        QMessageBox::warning(this, "ID EXISTE", "ID already exists, please enter another ID.");
        isValid = false;
    }


   //check if empty or not

   if ((ID_SESSION.isEmpty()) || (MODEE.isEmpty()) || (NIV_BATTERIE.isEmpty()) ||  (VITESSE.isEmpty()) ||  (HAPPY_HOUR.isEmpty()) ||  (PRIX.isEmpty()))
   {
       QMessageBox::warning(this, "Invalid Inputs", "Vous devez saisir tous les champs pour ajouter ");
       isValid = false;

   }

        //*****************

    if (isValid) {
        s.setID_SESION(ui->ID_SESSION->text());
        s.setMODEE(ui->MODEE->currentText());
        s.setNIV_BATTERIE(ui->NIV_BATTERIE->text());
        s.setVITESSE(ui->VITESSE->text());
        s.setHAPPY_HOUR(ui->HAPPY_HOUR->currentText());
        s.setPRIX(ui->PRIX->text());


        if (s.insert()) {
            //refresh to afficher
            ui->tableView_6->setModel(Etmp2.afficher_session());
            qDebug() << "session inserted successfully";
            QMessageBox::information(nullptr, QObject::tr("OK"),
                          QObject::tr("Ajout effectué\n"
                                      "Click Cancel to exit ."), QMessageBox::Cancel);

            // Add a new row to the QTableWidget and set the item for each column
            QTableWidget *tableWidget_4 = findChild<QTableWidget*>("tableWidget_4");
            int row = tableWidget_4->rowCount();
            tableWidget_4->insertRow(row);
            tableWidget_4->setItem(row, 0, new QTableWidgetItem(s.get_MODEE()));
            tableWidget_4->setItem(row, 1,new QTableWidgetItem(s.get_NIV_BATTERIE()));
            tableWidget_4->setItem(row, 2, new QTableWidgetItem(s.get_VITESSE()));
            tableWidget_4->setItem(row, 3, new QTableWidgetItem(s.get_HAPPY_HOUR()));
            tableWidget_4->setItem(row, 4, new QTableWidgetItem(s.get_PRIX()));
        } else {
            qDebug() << "Failed to insert session into database";
        }
    }

}
void MainWindow::on_pushButton_effacer_session_clicked(){

    int id1 =ui->lineEdit_test_session->text().toUInt();

    //QString license = ui->lineEdit->text();
     session s; // declare and initialize Etmp

     bool test=Etmp2.delete_session(id1);

     if (test) {
         ui->tableView_6->setModel(Etmp2.afficher_session());

         QMessageBox::information(nullptr, QObject::tr("OK"),
                           QObject::tr("Suppression effectue.\n"
                                       "Cancel to exit."), QMessageBox::Cancel);

     }
     else
         QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                           QObject::tr("Suppression NON effectue.\n"
                                       "Cancel to exit."), QMessageBox::Cancel);
}









void MainWindow::on_pushButton_modif_session_clicked()
{
    QString ID_SESSION = ui->ID_SESSION->text();
    QString MODEE = ui->MODEE->currentText();
    QString NIV_BATTERIE = ui->NIV_BATTERIE->text();
    QString VITESSE = ui->VITESSE->text();
    QString HAPPY_HOUR = ui->HAPPY_HOUR->currentText();
    QString PRIX = ui->PRIX->text();


    session s(ID_SESSION,MODEE,NIV_BATTERIE,VITESSE,HAPPY_HOUR,PRIX);

    //get the id2 for the checkid fucntion
    int id2 = ui->ID_SESSION->text().toInt();
    s.update(s.get_ID_SESION());
    ui->tableView_6->setModel(Etmp2.afficher_session());
   /* if (s.idExists(id2)) {

     if (s.update(s.get_ID_SESSION())) {
          // Refresh the table view to show the updated data
          ui->tableView->setModel(Etmp.afficher_session());
          QMessageBox::information(this, "Update session", "session updated successfully.");
      } else {
          QMessageBox::warning(this, "Update session", "Failed to update session.");
      }}else {

        QMessageBox::warning(this, "ID EXISTE", "ID already exists, please enter another ID.");

    }*/
  }





void MainWindow::on_pushButton_PDF_session_clicked()
{
    // Prepare SQL query
        QSqlQuery query;
        query.prepare("SELECT * FROM SESION");

        // Execute query
        if (!query.exec()) {
            qDebug() << "Failed to execute query!";
            return;
        }

        // Create PDF document
        QPdfWriter writer("C:/PDF/output.pdf");
        writer.setPageSize(QPageSize(QPageSize::A4));
        writer.setPageMargins(QMarginsF(20, 20, 20, 20));

        // Create PDF painter
        QPainter painter(&writer);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
        painter.setFont(QFont("Arial", 5));



        // Define table cell dimensions
        int cellWidth = 150;
        int cellHeight = 40;

        // Set table position
        int tableX = 20;
        int tableY = 20;

        // Draw table header
        painter.drawText(tableX + cellWidth , tableY, "ID_SESSION");
        painter.drawText(tableX + cellWidth * 6, tableY , "MODEE");
        painter.drawText(tableX + cellWidth * 11, tableY , "NIV_BATTERIE");
        painter.drawText(tableX + cellWidth * 18, tableY, "VITESSE");
        painter.drawText(tableX + cellWidth * 24, tableY, "HAPPY_HOUR");
        painter.drawText(tableX + cellWidth * 30, tableY, "PRIX");


        tableY += cellHeight;

        // Loop through query results and draw table cells
        int row = 5;
        while (query.next()) {
            // Draw ID_VOITURE value
            painter.drawText(tableX + cellWidth , tableY + row * cellHeight, query.value(0).toString());
            // Draw ID_CLIENT value
            painter.drawText(tableX + cellWidth * 6, tableY + row * cellHeight, query.value(1).toString());
            // Draw ID_MAINTENANCE value
            painter.drawText(tableX + cellWidth * 11, tableY + row * cellHeight, query.value(2).toString());
            // Draw MATRICULE value
            painter.drawText(tableX + cellWidth * 18, tableY + row * cellHeight, query.value(3).toString());
            // Draw BATTERIE_LVL value
            painter.drawText(tableX + cellWidth * 24, tableY + row * cellHeight, query.value(4).toString());
            // Draw BATTERIE_CAP value
            painter.drawText(tableX + cellWidth * 30, tableY + row * cellHeight, query.value(5).toString());


            row++;
            row++;
            row++;
            row++;
        }

        // Clean up
        painter.end();

        qDebug() << "PDF generated!";
    }

void MainWindow::on_pushButton_tri_session_2_clicked()
{
    // khdhit el table View mel ui
          QAbstractItemModel *model = ui->tableView_6->model();

          // Create a QSortFilterProxyModel  lel tri
          QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
          proxyModel->setSourceModel(model);

          // Sort by id
          proxyModel->setSortRole(Qt::EditRole);
          proxyModel->sort(0, Qt::AscendingOrder);

          //update lel table view
          ui->tableView_6->setModel(proxyModel);
}

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{

    QSqlQueryModel *model = new QSqlQueryModel(this);
       model->setQuery(QString("SELECT * FROM SESION WHERE MODEL LIKE '%%1%'").arg(arg1));
       model->setHeaderData(0, Qt::Horizontal, "ID_SESSION");
       model->setHeaderData(1, Qt::Horizontal, "MODEE");
       model->setHeaderData(2, Qt::Horizontal, "NIV_BATTERIE");
       model->setHeaderData(3, Qt::Horizontal, "VITESSE");
       model->setHeaderData(4, Qt::Horizontal, "BATTERIE_LVL");
       model->setHeaderData(5, Qt::Horizontal, "HAPPY_HOUR");
       model->setHeaderData(6, Qt::Horizontal, "PRIX");
       ui->tableView_7->setModel(model);
       ui->tableView_7->show();
}




void MainWindow::on_mode_charge_session_clicked()
{

    int quantity;
    int niv;
    int niv_batt;

        int v=ui->lineEdit_8->text().toInt();
        int id_s=ui->lineEdit_9->text().toInt();
        QSqlQuery query;
        query.prepare("SELECT QUNATITE FROM VOITURE WHERE ID_VOITURE=:idVoi");
        query.bindValue(":idVoi",v );
        if (query.exec() && query.next()) {
             quantity = query.value(0).toInt(); // Get the quantity from Voiture table
            qDebug() << "Quantity: " << quantity;
        } else {
            qDebug() << "Failed to get quantity from Voiture table!";
        }


        query.prepare("SELECT NIV_BATTERIE FROM SESION WHERE ID_SESSION=:id");
        query.bindValue(":id",id_s );
        if (query.exec() && query.next()) {
             niv = query.value(0).toInt(); // Get the NIV_BATTERIE from SESION table
            qDebug() << "NIVEAU: " << niv;
        } else {
            qDebug() << "Failed to get NIV_BATTERIE from SESION table!";
        }



        double niv_quantity = quantity*100/1000;
        int new_niv = static_cast<int>(niv - niv_quantity);

if(query.exec() && query.next()){

        if (new_niv <= 20) {
            QSqlQuery query3;

            query3.prepare("UPDATE SESION SET MODEE = 'repos' WHERE ID_SESSION = :id");
            query3.bindValue(":id", id_s);
            if (query3.exec()) {
                QMessageBox::warning(this, "REPOS MODE", "la session est en mode repos");
            } else {
                qDebug() << "Failed to update MODEE column in SESSION tableeeeeeeeeeeeeeeeeeeee!";
            }
 }
else {



QSqlQuery query2;
query2.prepare("UPDATE SESION SET NIV_BATTERIE=:new_niv WHERE ID_SESSION=:id");
query2.bindValue(":id", id_s);
query2.bindValue(":new_niv", new_niv);
if (query2.exec()) {
    qDebug() << "Updated NIV_BATTERIE in SESION table";
    QMessageBox::warning(this, "Charging", "Mise a jour de la session complete");
}
else {
    qDebug() << "Failed to update NIV_BATTERIE in SESION table!";
    return;
}

        }}




}

void MainWindow::on_pushButton_arduino_session_clicked()
{

    int PRICE;
    int id=ui->lineEdit_10->text().toInt();

                                   QSqlQuery query1;
                                   query1.prepare("SELECT PRIX FROM SESION JOIN VOITURE ON VOITURE.ID_SESSION=SESION.ID_SESSION WHERE VOITURE.ID_VOITURE = :id_voiture");
                                   query1.bindValue(":id_voiture", id);

                                    query1.exec();
                                   if (query1.next()) {
                                  PRICE=query1.value("PRIX").toInt();
                                 qDebug() << "TEST PRIX!" <<PRICE ;
                                    }
                                    if (!query1.exec()) {
                                        qDebug() << "Failed to execute query1!";
                                        return;
                                    }


                                    QByteArray priceData = QByteArray::number(PRICE);
                                 // create an instance of the arduino object
                                   a.write_to_arduino(priceData);
}
void MainWindow::on_pushButton_stat_session_clicked()
{
    session s  ;
        QSqlQuery q1,q2,q3;
               qreal tot=0,c1=0,c2=0;
               q1.prepare("SELECT ID_SESSION FROM SESION");
               q1.exec();
               q2.prepare("SELECT ID_SESSION FROM SESION WHERE MODEE='repos'");
               q2.exec();
               q3.prepare("SELECT ID_SESSION FROM SESION WHERE MODEE='actif'");
               q3.exec();
               while (q1.next()){tot++;}
               while (q2.next()){c1++;}
               while (q3.next()){c2++;}
               c1=(c1 * 100)/tot;
               c2=(c2 * 100)/tot;
               QString c3= QString::number(c1) ;
               c3="="+c3+"%";
            QString c4= QString::number(c2) ;
            c4="="+c4+"%";
             QString etat1="L" ;
             etat1=etat1+c3 ;
             QString etat2="P" ;
             etat2=etat2+c4 ;
               //Création des pie series
               QPieSeries *series = new QPieSeries();
               series->append(etat1,c1);
               series->append(etat2,c2);
               //Creation d'un charte
               QChart *chart  =new QChart();
               chart->setTitle("Les résultats:");
               chart->addSeries(series);
               chart->legend()->show();
                chart->setBackgroundBrush(QColor(252, 236, 218, 0));
               QChartView *chartView;
               chartView = new QChartView(chart,ui->graphicsView_statistic);
               chartView->setRenderHint(QPainter::Antialiasing);
               chartView->setMinimumSize(280,200);
               chartView->show();
}

void MainWindow::on_pushButton_effacer_tout_sess_clicked()
{
    session s;
        s.delete_all();
        ui->tableView_6->setModel(s.afficher_session());
}




void MainWindow::on_pushButton_chercher_session_clicked()
{
    session s;
        ui->tableView_7->setModel(s.afficher_search(ui->lineEdit_7->text()));
}



//***************************CLIENT YOUSSEF**********************************//


void MainWindow::on_pb_ajouter_clicked()
{
    int id=ui->lineEdit_id->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    int cin=ui->lineEdit_cin->text().toInt();
    QString adresse=ui->lineEdit_adresse->text();
    int telephone=ui->lineEdit_telephone->text().toInt();
    QString email=ui->lineEdit_email->text();
    int bonus=0;
    int reclamation=0;
    client c(id,nom,prenom,cin,adresse,telephone,email,bonus,reclamation);
    // Add a new row to the QTableWidget and set the item for each column
   // c.ajouter_client();
    if ((ui->lineEdit_id->text().isEmpty()) || (ui->lineEdit_nom->text().isEmpty()) || (ui->lineEdit_prenom->text().isEmpty()) || (ui->lineEdit_cin->text().isEmpty()) || (ui->lineEdit_adresse->text().isEmpty()) || (ui->lineEdit_telephone->text().isEmpty()) || (ui->lineEdit_email->text().isEmpty()))
    {
        QMessageBox::warning(this,"Invalide input    ","Saisie invalide!");
    }
    if ((c.ajouter_client()==false) && (!ui->lineEdit_id->text().isEmpty() )) {
            QMessageBox::warning(this,"Invalide input    ","Id existe deja!");
            }
        ui->tableView_client->setModel(c.afficher());


     // QTableWidget *tableWidget = findChild<QTableWidget*>("tableWidget");
    //  int row = tableWidget->rowCount();
     // tableWidget->insertRow(row);
    /*  tableWidget->setItem(row, 0, new QTableWidgetItem(c.get_nom()));
      tableWidget->setItem(row, 1, new QTableWidgetItem(c.get_prenom()));
      tableWidget->setItem(row, 2, new QTableWidgetItem(c.get_cin()));
      tableWidget->setItem(row, 3, new QTableWidgetItem(c.get_adresse()));
      tableWidget->setItem(row, 4, new QTableWidgetItem(c.get_telephone()));
      tableWidget->setItem(row, 5, new QTableWidgetItem(c.get_email()));
      tableWidget->setItem(row, 6, new QTableWidgetItem(c.get_bonus()));
      tableWidget->setItem(row, 7, new QTableWidgetItem(c.get_reclamation()));*/
}





void MainWindow::on_pb_supprimer_clicked()
{
    client c;
    c.setID(ui->lineEdit_supp_id->text().toInt());
    bool test=c.supprimer_client(c.get_id());
    ui->tableView_client->setModel(c.afficher());
    /*QMessageBox msgbox;
    if (test)
            msgbox.setText("Supprission avec succées!");
    else
            msgbox.setText("Echec de supprission!");
            msgbox.exec();*/
}

void MainWindow::on_pb_update_clicked()
{
    int id=ui->lineEdit_id->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    int cin=ui->lineEdit_cin->text().toInt();
    QString adresse=ui->lineEdit_adresse->text();
    int telephone=ui->lineEdit_telephone->text().toInt();
    QString email=ui->lineEdit_email->text();
    client c(id,nom,prenom,cin,adresse,telephone,email,0,0);
    c.modifier_client(c.get_id());
    ui->tableView_client->setModel(c.afficher());
}

void MainWindow::on_pb_avertissement_clicked()
{
    int id=ui->lineEdit_id2->text().toInt();
    int recl=ui->spinBox_averti->text().toInt();
    client c;
    c.ajouter_averti(id,recl);
    c.reduction_averti(id,recl);
    ui->tableView_client->setModel(c.afficher());
}

void MainWindow::on_pb_avertissement_2_clicked()
{
    int id=ui->lineEdit_id2->text().toInt();
    //int recl=ui->spinBox_averti->text().toInt();
    client c;
    c.update_bonus(id);
    ui->tableView_client->setModel(c.afficher());
    if (c.happy_hour(id)==false)
    {
        QMessageBox::warning(this,"Invalide!    ","Happy Hour n'est pas valide pour ce client !     ");
    }
}


void MainWindow::on_pushButton_pdf_client_clicked()
{
    client c;
    c.pdf();
    {QMessageBox::information(nullptr, QObject::tr("database is open"),
    QObject::tr("PDF exported successfully!\n"
    "Click Cancel to exit."), QMessageBox::Cancel);}
}

void MainWindow::on_pushButton_dec_tri_clicked()
{
    client c;
    ui->tableView_client->setModel(c.afficher_d());
}

void MainWindow::on_pushButton_croiss_tri_clicked()
{
    client c;
    ui->tableView_client->setModel(c.afficher_c());
}

void MainWindow::on_pushButton_search_client_clicked()
{
    client c;
    ui->tableView_client->setModel(c.afficher_search(ui->lineEdit_search->text()));
}

void MainWindow::on_pushButton_effacertout_clie_clicked()
{
    client c;
    c.delete_all();
    ui->tableView_client->setModel(c.afficher_c());
}

void MainWindow::on_pushButton_stat_client_clicked()
{

    QSqlQuery q1,q2,q3;
               qreal tot=0,c1=0,c2=0;
               q1.prepare("SELECT ID_CLIENT FROM CLIENT");
               q1.exec();
               q2.prepare("SELECT ID_CLIENT FROM CLIENT WHERE BONUS > 200");
               q2.exec();
               q3.prepare("SELECT ID_CLIENT FROM CLIENT WHERE BONUS < 200");
               q3.exec();
               while (q1.next()){tot++;}
               while (q2.next()){c1++;}
               while (q3.next()){c2++;}
               c1=(c1 * 100)/tot;
               c2=(c2 * 100)/tot;
               QString c3= QString::number(c1) ;
               c3="="+c3+"%";
            QString c4= QString::number(c2) ;
            c4="="+c4+"%";
             QString etat1="Fidele" ;
             etat1=etat1+c3 ;
             QString etat2="Non Fidele" ;
             etat2=etat2+c4 ;
               //Création des pie series
               QPieSeries *series = new QPieSeries();
               series->append(etat1,c1);
               series->append(etat2,c2);
               //Creation d'un charte
               QChart *chart  =new QChart();
               chart->setTitle("Les résultats des cartes fidelitées:");
               chart->addSeries(series);
               chart->legend()->show();
               chart->setBackgroundBrush(QColor(31, 86, 62, 1));
               QChartView *chartView;
               chartView = new QChartView(chart,ui->graphicsView_client);
               chartView->setRenderHint(QPainter::Antialiasing);
               chartView->setMinimumSize(280,200);
               chartView->show();
}

void MainWindow::on_pushButton_tester_clientclicked()
{
    QByteArray data = a.getserial()->readAll();
               // qDebug() << "Received data from Arduino:" << data;
                           QString strData(data);
                         //  qDebug() << "Received data:" << strData;
                           int startIndex = strData.indexOf("Card UID:");
                              if (startIndex != -1) {
                                  QString uid = strData.mid(startIndex + 10, 11);
                                  qDebug() << "Card UID:" << uid;
                                  uid.remove(" ");
                                  bool ok;
                                      int decimalValue = uid.toInt(&ok, 16);
                                      qDebug() <<decimalValue ;
                                      QSqlQuery query;
                                        client cc;
                                      if (cc.test_maintenance(decimalValue)==true)
                                      {
                                          qDebug() << "Id valide";
                                          query.prepare("SELECT * FROM MAINTENANCE  WHERE DATE >= NOW() AND DATE <= DATE_ADD(NOW(), INTERVAL 5 MINUTE)");
                                                                                   query.bindValue(":id", decimalValue);
                                                                                   query.exec();
                                                                               //    if (query.next())
                                                                               //    {
                                                                                       qDebug() << "Resa valide";
                                                                                       QDateTime currentDateTime = QDateTime::currentDateTime();
                                                                                       QString dateTimeStr = currentDateTime.toString("yyyy-MM-dd hh:mm");
                                                                                       qDebug() << dateTimeStr;
                                                                                       //test type panne
                                                                                       query.prepare("SELECT* FROM MAINTENANCE WHERE ID_MAINTENANCE=:id");
                                                                                       query.bindValue(":id", decimalValue);
                                                                                       query.exec();
                                                                                       while (query.next()) {
                                                                                            QString tp=query.value("TYPEE").toString();
                                                                                            qDebug()<<"Type"<<tp;
                                                                                            if (tp=="Panne")
                                                                                            {
                                                                                                a.write_to_arduino("1");
                                                                                                query.prepare("UPDATE MAINTENANCE SET COUT=:prix WHERE ID_MAINTENANCE=:id");
                                                                                                query.bindValue(":prix", 0);
                                                                                                query.bindValue(":id", decimalValue);
                                                                                                query.exec();

                                                                                              //  A.write_to_arduino(data);
                                                                                            }
                                                                                            else if (tp=="Lavage")
                                                                                            {
                                                                                                a.write_to_arduino("2");
                                                                                                query.prepare("UPDATE MAINTENANCE SET COUT=:prix WHERE ID_MAINTENANCE=:id");
                                                                                                query.bindValue(":prix", 0);
                                                                                                query.bindValue(":id", decimalValue);
                                                                                                query.exec();
                                                                                            }
                                                                                            //qDebug()<<"hello"<<recl;
                                                                                       }


                                                                              /*     }
                                                                                   else
                                                                                   {
                                                                                       qDebug() << "Resa invalide";
                                                                                   }*/

                                      }
                              else {
                                /*  query.prepare("SELECT* FROM MAINTENANCE WHERE ID_MAINTENANCE=:id");
                                  query.bindValue(":id", decimalValue);
                                  query.exec();
                                  while (query.next()) {*/
                                    //   QDateTime date=query.value("DATE_HR");
                                     //  qDebug()<<"hello"<<date;
                                      qDebug() << "Resa invalide";
                                  //}
                                  a.write_to_arduino("3");
                              }
                              }

        data = a.read_from_arduino();
  //  qDebug() << "Received data from Arduino:" << data;
}


