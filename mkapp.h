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

};

#endif // MKAPP_H
