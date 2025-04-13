#include <QApplication>
#include <QSettings>
#include <qfile.h>
#include <QDir>
#include "mkapp.h"

MKApp::MKApp(int &argc, char **argv)
    :QApplication(argc, argv)
{

}
//return true --- success
bool MKApp::LoadSettings()
{
    QFile checkConfig(QDir::currentPath()+"/"+fname);
    if(checkConfig.exists())
    {
        QSettings m_settings( QDir::currentPath()+"/"+fname, QSettings::IniFormat );


         type_imit = m_settings.value("Imit/type_app").toUInt();
         SleepingTime=m_settings.value("Imit/SleepingTime").toUInt();
         qDebug() << type_imit  << SleepingTime;

    }
    else       return false;


    return true;
}
