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

    connect(&timer,
            &QTimer::timeout,this,
            [=](){ emit MkTimeEvent(); });

   MKApp* pMKApp=(MKApp*)qApp;

    timer.start(pMKApp->GetSleepingTime());

    exec(); // запуск цикла сообщений
}
