#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <time.h>
//#include "QMainWindowTrace"
#define TITLE_NO_NAME "trace-Без названия"

class MainwindowTrace : public QMainWindow
{
    Q_OBJECT
    
public:
    MainwindowTrace(QWidget *parent = 0);
    ~MainwindowTrace();
public slots:
    void slotAbout();
    void slotSaveAs();
private slots:
 void slotChangeScale(QAction* prAc);
 void slotChangeH(QAction* pHAc);
 void slotNew();
 void slotSave();
 void OnOpen();
 void OnImit();
 void OnTime();

private:
    QAction* pActScale[5];
    QAction* pActHeight[3];
    void CommonSave();
    QTimer *tmr; //Адресная переменная таймера


};

#endif // MAINWINDOW_H
