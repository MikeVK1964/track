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
    qDebug() << QDir::currentPath();
    if(checkConfig.exists())
    {
        QSettings m_settings( QDir::currentPath()+"/"+fname, QSettings::IniFormat );


        unsigned typ = m_settings.value("Setting/type_app").toUInt();
        qDebug() << typ;

    }
    else       return false;


    return true;
}
