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
    bool IsClientNet() {return mknet_client==1 ; }
    unsigned GetSleepingTime(){return SleepingTime;}
private:
    QString fname="trace.conf";
    unsigned mknet_client=0; //1 -  клиент сети
    unsigned SleepingTime=0;
};

#endif // MKAPP_H
