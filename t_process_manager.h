#ifndef TPROCESSMANAGER_H
#define TPROCESSMANAGER_H
#include <QTimer>
#include <QObject>
#include <QProcess>


class TProcessManager :public QObject
{
    Q_OBJECT
public:

    TProcessManager();
    ~TProcessManager();

    void startMonitoring();
    void stopMonitoring();
    void checkingHardDriveInfo();
    void checkingRamInfo();
    void checkingCpuInfo();

    void checkingIpAddressInfo();
    void checkingSIMSerial();

void Reinit();
    void JsonFile();
    enum CmdCommands {
        DeviceName,
        SerialNumber,
        TerminalCode,
        DateCreated,
       SoftwareVersion,
        OS,
        CpuType,
        RamModel,
       Monitor,
        TotalRam,
        CpuUsage,
        RamUsage,
        Ping,
        SimSerial,
        IpAddress,
        MACAddress,
        HardType,
       HardCapacity,
        HardUsage,
        Power
    };
private slots:
    void checkingMonitor();


private:
    QTimer timer;
    QList<QString> commands;
    void makeList();
    void Runcmd();

};

#endif // TPROCESSMANAGER_H
