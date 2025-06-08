#include "threadscontroller.h"

ThreadsController::ThreadsController(QObject *parent)
    : QObject{parent}
{
    m_pMkClientSock= new MkClientSocket("localhost", 2323);
    thread = new QThread( parent );
 //   m_pMkClientSock->PrepareActions("localhost", 2323);
    connect(this, SIGNAL(SignalSendSecTime(double )),
                m_pMkClientSock, SLOT(SlotSendToServer(double ))
               );
//    void ShowTracks(QVector<TargetPositionNet> vnettar);
//    connect(m_pMkClientSock, SIGNAL(ShowTracks(QVector<TargetPositionNet> )),
//                this, SIGNAL(ShowTracks(QVector<TargetPositionNet> ) )
//               );
//    void ThreadsController::SlotShowTracks(QVector<TargetPositionNet> vnettar)
    connect(m_pMkClientSock, SIGNAL(ShowTracks(QVector<TargetPositionNet> )),
                this, SLOT(SlotShowTracks(QVector<TargetPositionNet> ) )
               );

    m_pMkClientSock->moveToThread(thread);
    thread->start();
//    const QString strHost;
//                       int            nPort,
//    m_pMkClientSock->PrepareActions("localhost", 2323);
}
ThreadsController::~ThreadsController()
{
//    if (m_pMkClientSock!=nullptr) delete m_pMkClientSock;
    // deleteLater - поток должен получить управление и все незавершенные
    //задачи(незавершенные сигналы) завершатся
    if (m_pMkClientSock!=nullptr) m_pMkClientSock->deleteLater();
    m_pMkClientSock=nullptr;
    thread->quit();
    thread->wait(); // на всякий случая в run ничего нет
    delete thread ;

}
void ThreadsController::SlotShowTracks(QVector<TargetPositionNet> vnettar1)
{
    this->vnettar1=vnettar1;
    emit SignalShowNetTracks1();
    qDebug() << "ThreadsController::SlotShowTracks";
}
