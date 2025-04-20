#include <QApplication>
#include <QSettings>
#include "mainwindowTrace.h"
#include "mkapp.h"

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
    MKApp a(argc, argv);

    extern  MainwindowTrace* pMW;
    MKApp* pMKApp=(MKApp*)qApp;
    if (!pMKApp->LoadSettings())
     return 1;
    pMW = new  MainwindowTrace;
    pMW->show();
    return a.exec();     // запуск цикла обработки сообщений
}
