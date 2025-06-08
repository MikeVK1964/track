#ifndef THREADSCONTROLLER_H
#define THREADSCONTROLLER_H

#include <QObject>
#include "mkclientsocket.h"


class ThreadsController : public QObject
{
    Q_OBJECT
public:
    explicit ThreadsController(QObject *parent = nullptr);
    ~ThreadsController();
    MkClientSocket* GetMkClSock(){return m_pMkClientSock; }
    QVector<TargetPositionNet> vnettar1;

private:
    QThread* thread; //поток

    MkClientSocket* m_pMkClientSock=nullptr;

signals:
    void SignalSendSecTime(double );
    void SignalShowNetTracks1();
//    void ShowTracks(QVector<TargetPositionNet> vnettar);
public slots:
    void SlotShowTracks(QVector<TargetPositionNet> vnettar);


};

#endif // THREADSCONTROLLER_H
