#ifndef MKIMITTHREAD_H
#define MKIMITTHREAD_H

#include <QThread>
#include <QObject>

class MkImitThread : public QThread
{
Q_OBJECT
public:
    explicit MkImitThread(QObject *parent = nullptr);
      void run();
signals:
      void MkTimeEvent();
public slots:
};

#endif // MKIMITTHREAD_H
