#include <QCoreApplication>
#include <t_process_manager.h>
#include <QDebug>
#include <iostream>
#include <QSharedPointer>
#include <QRandomGenerator>
#include <QMap>
#include "general.h"
#include <QDir>
#include <QApplication>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TProcessManager myProcessManager;
    myProcessManager.Reinit();
    //TProcessManager pm;
    //pm.startMonitoring();
    // pm.checkingHardDriveInfo();
    // pm.checkingRamInfo();
    // pm.checkingCpuInfo();
     //myProcessManager.checkingIpAddressInfo();






// QString s="LoadPercentage  Name 2 Intel(R) Core(TM) i5-4440 CPU @ 3.10GHz";
//     QStringList s1=s.split(" ",Qt::SkipEmptyParts);
// QString name=s1.at(0);
//     QString name2=s1.at(2);
// qDebug() << name <<" : "<<name2;


    return a.exec();
}
