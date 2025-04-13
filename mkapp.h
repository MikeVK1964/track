#ifndef MKAPP_H
#define MKAPP_H

#include <QApplication>
#include "setcontrol.h"

class MKApp : public QApplication
{
public:
    MKApp(int &argc, char **argv);
    bool LoadSettings();
    SetControl scon; // управляющие параметры
    unsigned GetImitType() {return type_imit; }
    unsigned GetSleepingTime(){return SleepingTime;}
private:
    QString fname="trace.conf";
    unsigned type_imit; //1 - timer
    unsigned SleepingTime=0;
};

#endif // MKAPP_H
