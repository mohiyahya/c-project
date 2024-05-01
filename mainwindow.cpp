#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QString>
#include <QDebug>
#include  "QTextStream"
#include <iostream>
#include <QDir>
#include <QApplication>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnprinter_clicked()
{
    QJsonObject statusObject;
    statusObject["device"] = ui->leDevice->text().toInt();
    statusObject["lamp"] = ui->leLamp->text().toInt();
    statusObject["paper"] = ui->lePaper->text().toInt();

    QJsonObject propertyObject;
    propertyObject["printer"] = statusObject;

     QJsonDocument doc(propertyObject);

    QJsonArray jsonarray;
     QJsonObject Statusjsonarray;
    Statusjsonarray["device"]= ui->leDevice->text().toInt();
     Statusjsonarray["lamp"]  =ui->leLamp->text().toInt();
     Statusjsonarray["paper"] =ui->lePaper->text().toInt();

     jsonarray.append(Statusjsonarray);
QJsonDocument docarray(jsonarray);



  QString appDir = QCoreApplication::applicationDirPath();
    qDebug() <<"path:" <<appDir;
   //ui->textEdit->setText(appDir);
    QString relativePath = appDir + "/CashlessStatus.txt";
        QFile file(relativePath);
    ui->textEdit->setText(relativePath);
   if (!file.exists()) {
        if (file.open(QIODevice::WriteOnly)) {
           file.write(doc.toJson());
            file.write(docarray.toJson());
            // File is now created and open for writing
            // You can write data to the file here
             // Close the file when done
        }file.close();
   }else {
       QTextStream stream(&file);
      QString update = stream.readAll();
       QJsonDocument jsondocumet=QJsonDocument::fromJson(update.toUtf8());
      if (jsondocumet.isObject()) {
           QJsonObject newjobject;
          newjobject=jsondocumet.object();

      }else {
          qDebug() << "Failed to open file for reading.";
      }

   }
}

