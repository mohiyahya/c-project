#include "t_process_manager.h"
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
#include <QJsonValue>
TProcessManager::TProcessManager()
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(checkingMonitor()));

}



TProcessManager::~TProcessManager()
{
    disconnect(&timer, SIGNAL(timeout()), this, SLOT(checkingMonitor()));
}


void TProcessManager::startMonitoring()
{
    timer.setInterval(5000);
    timer.start();
}

void TProcessManager::stopMonitoring()
{
    timer.stop();
}


void TProcessManager::checkingMonitor()
{

    QProcess process;
    // process.start(/*"cmd.exe", QStringList() << "/c" <<*/ "wmic desktopmonitor get Name,MonitorType,MonitorManufacturer,Status");
    QStringList list;
    list.append("desktopmonitor");
    list.append("get");
    list.append("Status");
    process.start("wmic", list );
    // qDebug() << process.readAll();
    process.waitForFinished();
    QString output = process.readAllStandardOutput();
    // if (process.exitCode() == 0) {
    //     qDebug() << "Command executed successfully. Output:";
    //     qDebug() << output;
    // } else {
    //     qDebug() << "Error executing the command. Exit code:" << process.exitCode();
    // }
    QStringList items = output.split('\n', Qt::SkipEmptyParts);
    for (const QString& item : items) {
        QString trimmedItem = item.trimmed(); // Trim any leading/trailing spaces
        if (!trimmedItem.isEmpty()) {
            qDebug() << trimmedItem;
        }
    }



    // qDebug() << output;
}

void TProcessManager::makeList()
{
    commands.append("wmic memorychip get capacity");
    commands.append("wmic memorychip get MemoryType");
    commands.append("wmic cpu get loadpercentage");
    commands.append("wmic cpu get name");
    commands.append("wmic nicconfig get ipaddress");
    commands.append("wmic desktopmonitor get status");
    // commands.append("systeminfo | find \"Available Physical Memory");
    // commands.append("systeminfo | findstr /B /C:\"OS Name\"");
    // commands.append("systeminfo | find \"Total Physical Memory\"");
    //commands.append("power");



}

void TProcessManager::Runcmd()
{
    for (const QString& cmd : commands) {
        QProcess process;
        process.start("cmd", QStringList() << "/c" << cmd);
        process.waitForFinished();
        QString output = process.readAll().trimmed();
        QStringList items = output.split('\n', Qt::SkipEmptyParts);
        if (items.count() != 0 )
        {
            if (items.at(0).trimmed()=="IPAddress") {
                for (int i = 1; i < items.count(); i++) {
                    QString trimmedItem = items.at(i).trimmed(); // Trim any leading/trailing spaces
                    if(trimmedItem.contains(",")){
                    QStringList Newitems = trimmedItem.split(",");
                        for (int j = 0; j < Newitems.count(); ++j) {

                            qDebug() << Newitems.at(j);
                        }

                    }
                }
            }
            else{
                for (int i = 0; i < items.count(); i++)
                {
                    QString trimmedItem = items.at(i).trimmed(); // Trim any leading/trailing spaces
                    if (!trimmedItem.isEmpty()) {
                        qDebug() << trimmedItem;
                    }


                }
            }
        }

    }

}

void TProcessManager::Reinit()
{
    //makeList();
   // Runcmd();
    JsonFile();
    //checkingRamInfo();
}

void TProcessManager::JsonFile()
{
    QString serialno="c:\\pathsrc\cashlessfiles\sconfig";
    if (serialno.at(0)=="SerialNumber") {
        for (int i = 1; i < serialno.count(); i++) {
            QString trimmedItem = serialno.at(i).trimmed(); // Trim any leading/trailing spaces
            if(trimmedItem.contains(",")){
                QStringList Newitems = trimmedItem.split("=");
                for (int j = 0; j < Newitems.count(); ++j) {

                    qDebug() << Newitems.at(j);
                }

            }
        }
    }

    QJsonObject myJsonObj;
    myJsonObj["DeviceName"] = "wk300";
    myJsonObj["SerialNumber"] = serialno;

     myJsonObj["TerminalCode"] =;
     myJsonObj["DateCreated"] = "";
    myJsonObj["SoftwareVersion"] = "";
     myJsonObj["OS"] = "";
    myJsonObj["CpuType"] = "";
    myJsonObj["RamModel"] = "";
    myJsonObj["Monitor"] = "";
    myJsonObj["TotalRam"] = "";
    myJsonObj["CpuUsage"] = "";
    myJsonObj["RamUsage"] = "";
    myJsonObj["Ping"] = "";
    myJsonObj["SimSerial"] = "";
    myJsonObj["IpAddress"] = "";
    myJsonObj["MACAddress"] = "";
    myJsonObj["HardType"] = "";
    myJsonObj["HardCapacity"] = "";
    myJsonObj["HardUsage"] = "";
    myJsonObj["Power"] = "";

    QJsonDocument doc(myJsonObj);
    qDebug()<<""<< myJsonObj;

    QFile file("my_device_info.json");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // Write the JSON data to the file
        file.write(doc.toJson(QJsonDocument::Indented));
        file.close();
    } else {
        // Handle file open error
        qDebug() << "Error opening file for writing.";
    }



}

void TProcessManager::checkingHardDriveInfo()
{
    QProcess process;
    QStringList list;
    list.append("MEMORYCHIP");
    list.append("get");
    list.append("MemoryType,");
    list.append("Capacity");
    process.start("wmic",list);
    process.waitForFinished();
    QString output = process.readAllStandardOutput();
    qDebug() << "Hard Drive Information:";
    QStringList items = output.split('\n', Qt::SkipEmptyParts);
    for (const QString& item : items) {
        QString trimmedItem = item.trimmed(); // Trim any leading/trailing spaces
        if (!trimmedItem.isEmpty()) {
            qDebug() << trimmedItem;
        }
    }


}

void TProcessManager::checkingRamInfo()
{
    QProcess process;
    process.start("cmd", QStringList() << "/c" << "systeminfo");
    process.waitForFinished();

    QString output = process.readAllStandardOutput();
    qDebug() << "RAM Information:" ;

    QStringList items = output.split('\n');
    // for (const QString& item : items) {
    //     QString trimmedItem = item.trimmed(); // Trim any leading/trailing spaces
    //     if (!trimmedItem.isEmpty()) {
    //         qDebug() << trimmedItem;
    //     }
    // }
    /*for(int i=0; i < items.count(); i++)
    {
        }*/
    //items.at(i) = items.at(i).trimmed();
    if(items.at(2).trimmed().contains("OS Name")){
        QStringList Newitems = items.at(2).split("OS Name:");
        QString osname=Newitems.at(1).trimmed();
        qDebug() <<" Os Name: " <<osname ;
    }
    if (items.at(25).trimmed().contains("Available Physical Memory:")) {
        QStringList Newitems = items.at(25).split("Available Physical Memory:");
        QString osname=Newitems.at(1).trimmed();
        qDebug() <<" Available Physical Memory: " <<osname ;
    }

    if (items.at(24).trimmed().contains("Total Physical Memory:")) {
        QStringList Newitems = items.at(24).split("Total Physical Memory:");
        QString osname=Newitems.at(1).trimmed();
        qDebug() <<" Total Physical Memory: " <<osname ;

    }


}

void TProcessManager::checkingCpuInfo()
{
    QProcess process;
    //process.start("cmd", QStringList() << "/c" << "wmic cpu get name, caption, maxclockspeed, numberofcores");
    QStringList list;
    list.append("cpu");
    list.append("get");
    list.append("loadpercentage,");
    list.append("name");
    process.start("wmic",list);
    process.waitForFinished();
    QString output = process.readAllStandardOutput();
    qDebug() << "Cpu Information:" ;
    QString trimmedItem;
    QStringList items = output.split('\n', Qt::SkipEmptyParts);
    for (const QString& item : items) {
        trimmedItem = item.trimmed(); // Trim any leading/trailing spaces
        if (!trimmedItem.isEmpty()) {
            qDebug() << trimmedItem;
        }
        /*for(int i=0; i < items.count(); i++)
    {
        }*/
        //items.at(i) = items.at(i).trimmed();
        // QStringList spaces=trimmedItem.split("");
        // if(spaces.at(1).trimmed().contains("LoadPercentage  Name")){
        //     QStringList Newitems = spaces.at(1).split("LoadPercentage:");
        //     QString osname=Newitems.at(1).trimmed();
        //     qDebug() <<" LoadPercentage : " <<osname ;
        // }
    }

}



void TProcessManager::checkingIpAddressInfo()
{
    QProcess process;
    // process.start("cmd", QStringList() << "/c" << "ipconfig |  findstr ");
    QStringList list;
    list.append("nicconfig");
    list.append("get");
    list.append("ipaddress");
    process.start("wmic",list);
    process.waitForFinished();
    QString output = process.readAllStandardOutput();

    QStringList items = output.split('\n', Qt::SkipEmptyParts);
    // QStringList newitem=items.split(',');
    for (const QString& item : items) {
        QString trimmedItem = item.trimmed();
        // QStringList newitems = item.split(',', QString(::SkipEmptyParts);
        // Trim any leading/trailing spaces
        if (!trimmedItem.isEmpty()) {
            qDebug()<< "ip Information:"<< trimmedItem;
        }





    }
}

void TProcessManager::checkingSIMSerial()
{
    // QProcess process;
    // process.start("wmic", QStringList() << "path" << "win32_pnpentity" << "where" << "DeviceID like '%SIM%'" << "get" << "Caption,PNPDeviceID");
    // process.waitForStarted();
    // process.waitForFinished();
    // QString output = process.readAllStandardOutput();

    // // Parse the output to extract the ICC ID
    // // (ICC ID is usually part of the PNPDeviceID)
    // // ...

    // qDebug() << "SIM ICC ID:\n" << output;
}


