#ifndef MOHADESEH_H
#define MOHADESEH_H

#include <QFile>
#include <QString>
#include <QObject>
class Mohadeseh :public QObject
{
    Q_OBJECT
public:
    Mohadeseh();
    QFile doMoghayerat();               // every day i do moghayerat and then take you a file
    void projectCode();                // every day solve and find solution
    QFile doResearch(QString topic);  // take a topic to me and then i make you a report




    bool getStatus();
    QString whatAreYouDoing();

private:
    bool nagging;
    QString Name;
    QString LastName;
    int age;
    int melicode;
    QString hometown;
    QString gender(QStringList genders); //chose gender from this list that you choose male or female
    int phonenumber;
    QString degree;
    QString address;
    bool doSport;
    bool healthy;
        int weight;
    int lenght;
    bool alive;
    QStringList skincolor(QString skin); //chose skin color from this list that you thing appropriate for me
   bool responsibility;
   bool riskyperson;
  bool naughty;



    void wakeup();
    void washdface();
    void brashteeth();
    void makeup();
    void gotowork();




};

#endif // MOHADESEH_H
