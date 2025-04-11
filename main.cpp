#include <QApplication>
#include <QSettings>
#include "mainwindowTrace.h"
#include "mkapp.h"

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
    MKApp a(argc, argv);

    extern  MainwindowTrace* pMW;
    QString fname="trace.conf";
    QFile checkConfig(fname);
    if(checkConfig.exists())
    {
        QSettings m_settings( fname, QSettings::IniFormat );


        unsigned typ = m_settings.value("/Settings/type_app").toUInt();
        qDebug() << typ;

    }
    else {

    }
    MKApp* pMKApp=(MKApp*)qApp;
    if (!pMKApp->LoadSettings())
     return 1;
    pMW = new  MainwindowTrace;
    pMW->show();
    return a.exec();
}
