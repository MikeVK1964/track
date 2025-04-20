#include "mkimitthread.h"
#include "mkapp.h"

#include <QTimer>
MkImitThread::MkImitThread(QObject *parent)
    : QThread{parent}
{

}
// Переписываем метод
void MkImitThread::run()
{
    QTimer timer;
    connect(&timer, SIGNAL(timeout()), SLOT(slotOnTime()));

    MKApp* pMKApp=(MKApp*)qApp;
//    tmr->start(pMKApp->GetSleepingTime());

    timer.start(pMKApp->GetSleepingTime());

    exec(); // запуск цикла сообщений
}
void MkImitThread::slotOnTime()
{
   emit MkTimeEvent();
}
