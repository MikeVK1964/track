#ifndef MKCLIENTSOCKET_H
#define MKCLIENTSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include "maketras.h"

class MkClientSocket :public QObject
{
    Q_OBJECT
public:
    MkClientSocket(const QString& strHost, int nPort, QWidget* pwgt = 0);
//    void PrepareActions(const QString& strHost, int nPort);
    ~MkClientSocket();
    QVector<TargetPositionNet>* getVect(){return &vnettar;}
    QMutex m_mutex;
private:
    QTcpSocket* m_pTcpSocket;
    quint16     m_nNextBlockSize=0;
    QVector<TargetPositionNet> vnettar;
//    double traces_time=0;  // время трасс для получения координат
    double start_time_tick;  // imitation time since begin
public slots:
    void SlotSendToServer(double trace_time);
    void SlotProcess();

private slots:
    void slotConnected();
    void slotReadyRead   (  );
    void slotError       (QAbstractSocket::SocketError);
signals:
    void RestartProcess(); // сигнал для перезапуска process
    void ShowTracks(QVector<TargetPositionNet> vnettar);

};

#endif // MKCLIENTSOCKET_H
