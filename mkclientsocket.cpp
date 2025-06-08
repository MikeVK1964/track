#include <QMessageBox>
#include "mkclientsocket.h"
//#include "maketras.h"
//https://github.com/manfredipist/QTcpSocket/tree/master
MkClientSocket::MkClientSocket(const QString& strHost, int nPort, QWidget* pwgt )
    : QObject{}
{
    m_pTcpSocket = new QTcpSocket(this);
//    m_pTcpSocket->connectToHost(strHost, nPort);
    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    //    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
    //            this,         SLOT(slotError(QAbstractSocket::SocketError))
    //           );
       // так начиная с QT5
    connect(m_pTcpSocket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)),
                this,         SLOT(slotError(QAbstractSocket::SocketError))
               );

    connect(this, SIGNAL(RestartProcess()),
                this,         SLOT(SlotProcess())
               );

    start_time_tick = clock();
    m_pTcpSocket->connectToHost(strHost, nPort);
 //   m_pTcpSocket->waitForConnected(); // ждем 30 секунд
    if (!m_pTcpSocket->waitForConnected(10000000))  //ждем 1000000 сек
    {
      QMessageBox::critical(nullptr,
       "QTCPClient", QString("The following error occurred: %1.").arg(m_pTcpSocket->errorString()));
      return;
    }
}
MkClientSocket::~MkClientSocket()
{
    if(m_pTcpSocket->isOpen())
        m_pTcpSocket->close();

}

void MkClientSocket::slotConnected()
{
    qDebug() << "Connected123";
    SlotProcess();
}
// ----------------------------------------------------------------------
// вызывается при получении данных от сервера
void MkClientSocket::slotReadyRead()
{
    qDebug() << "slotReadyRead()";
    QDataStream in(m_pTcpSocket);
    in.setVersion(QDataStream::Qt_5_10);
    for (;;) {
        if (!m_nNextBlockSize) {   // число байт в блоке
// static_cast -- проверяет возможность преобразования во время компиляции

//            if (m_pTcpSocket->bytesAvailable() < sizeof(quint16)) {
            if (static_cast<long long unsigned int>(m_pTcpSocket->bytesAvailable()) < sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize;  // считывваем
        }

       if (m_pTcpSocket->bytesAvailable() < m_nNextBlockSize) {
            break;   // не весь блок считан
        }
        m_mutex.lock();

         qsizetype trace_count;

         in >> trace_count;
         vnettar.clear();  //

         for (int i=0;i<trace_count;i++ )
         {
            TargetPositionNet tracePos;
            in >> tracePos;
            vnettar.push_back(tracePos); // запись в вектор
            qDebug() << "tracePos.fx_km " << tracePos.fx_km;
         }
         m_nNextBlockSize = 0;
         emit ShowTracks(vnettar);
        m_mutex.unlock();

        QThread::msleep(5000);
        SlotProcess();

    }
//    SlotProcess();
}
// trace_time -
void MkClientSocket::SlotSendToServer(double trace_time)
{
    qDebug() << "SlotSendToServer ";
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);
//    double trace_time=3; // время движения с начала имитации в секундах
//    out <<  QTime::currentTime() << m_ptxtInput->text();
    out << trace_time;
    m_pTcpSocket->write(arrBlock);
    m_pTcpSocket->flush(); // посылаем немедленно без буффера
}
void MkClientSocket::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
        "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                     "The host was not found." :
                     err == QAbstractSocket::RemoteHostClosedError ?
                     "The remote host is closed." :
                     err == QAbstractSocket::ConnectionRefusedError ?
                     "The connection was refused." :
                     QString(m_pTcpSocket->errorString())
                    );
  //  m_ptxtInfo->append(strError);
    qDebug() << strError;
}
void MkClientSocket::SlotProcess()
{
    double duration;  // разница в секундах
    // проверка во время компиляции
    duration = ( clock() - start_time_tick ) / static_cast<double>(CLOCKS_PER_SEC);
 //   SlotSendToServer(duration);
    SlotSendToServer(duration);
 //   QThread::usleep(200);
 //   QThread::msleep(4000);

//    emit RestartProcess();

}
