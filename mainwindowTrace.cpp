#include "mainwindowTrace.h"
#include "new_traceview.h"
#include "filenew.xpm"
#include "fileopen.xpm"
#include "filesave.xpm"
#include "setcontrol.h"
#include "iko.h"
#include "si_xh.h"
#include "maketras.h"
#include "DocTrace.h"
#include "dlgimit.h"
#include "mkapp.h"

#include <QMenu>
#include <QMessageBox>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QFileDialog>
////#include <QTextCodec>

//extern SetControl scon; // управляющие параметры

MainwindowTrace::MainwindowTrace(QWidget *parent)
    : QMainWindow(parent)
{
    New_traceView* pView = new New_traceView;

    QMenu* pmnuFile = new QMenu(tr("Файл"));
     QAction* pactNew = new QAction(tr("Новый"),0);
      pactNew->setShortcut(QKeySequence("CTRL+N"));
      pactNew->setToolTip(tr("Новый документ"));
      pactNew->setStatusTip(tr("Cоздание нового документа"));
      pactNew->setWhatsThis(tr("Cоздание нового документа"));
      pactNew->setIcon(QPixmap(filenew));
 //     connect(pactNew, &QAction::triggered, this, &MainwindowTrace::slotNew);
      connect(pactNew, SIGNAL(triggered()), this, SLOT(slotNew()));
     pmnuFile->addAction(pactNew);

     QAction* pactOpen = new QAction("Open file", 0);
      pactOpen->setText("&Открыть..."); // изменяет Open file
      pactOpen->setShortcut(QKeySequence("CTRL+O"));
      pactOpen->setToolTip("Открыть документ");
      pactOpen->setStatusTip("Открыть существующий план");
      pactOpen->setWhatsThis("Открыть существующий план");
      pactOpen->setIcon(QPixmap(fileopen));

      connect(pactOpen, SIGNAL(triggered()), this, SLOT(OnOpen()));
     pmnuFile->addAction(pactOpen);

     QAction* pactSave = new QAction("Save File", 0);
      pactSave->setText("&Save");
      pactSave->setShortcut(QKeySequence("CTRL+S"));
      pactSave->setToolTip("Save Document");
      pactSave->setStatusTip("Save the file to disk");
      pactSave->setWhatsThis("Save the file to disk");
      pactSave->setIcon(QPixmap(filesave));
      connect(pactSave, SIGNAL(triggered()), this, SLOT(slotSave()));


//     pmnuFile->addAction(pactNew);
//     connect(pmnuFile,SIGNAL(triggered(QAction*)),SLOT(slotChangeH(QAction*)));

    // pmnuFile->addAction(pactOpen,this,SLOT(slotNew()));
     pmnuFile->addAction(pactSave);
     pmnuFile->addAction("Save &As...", this, SLOT(slotSaveAs()));

     pmnuFile->addSeparator();
////     pmnuFile->addAction(tr("Выход"),qApp,SLOT(quit()),QKeySequence("CTRL+Q"));
     pmnuFile->addAction(tr("Выход"),QKeySequence("CTRL+Q"),qApp,SLOT(quit()));

///     pmnuFile->addAction(tr("Выход"),QKeySequence("CTRL+Q"),qApp,SLOT(quit()));

     QMenu* pmnuMode = new QMenu(tr("&Отображение"));
     QMenu* pmnuSubMenuShow = new QMenu(tr("Масштаб ИКО"),pmnuMode);
     pmnuMode->addMenu(pmnuSubMenuShow);
      pActScale[0] =
              pmnuSubMenuShow->addAction("500");

      pActScale[0]->setIcon(QIcon(":/rec/images/scale500.png"));

      pActScale[0]->setIconVisibleInMenu(false);

      pActScale[0]->setCheckable(true);
      pActScale[0]->setChecked(true);

      pActScale[1] = pmnuSubMenuShow->addAction("300");
      pActScale[1]->setCheckable(true);

      pActScale[1]->setIcon(QIcon(":/rec/images/scale300.png"));

      pActScale[1]->setIconVisibleInMenu(false);


      pActScale[2] = pmnuSubMenuShow->addAction("150");
      pActScale[2]->setCheckable(true);

      pActScale[2]->setIcon(QIcon(":/rec/images/scale150.png"));

      pActScale[2]->setIconVisibleInMenu(false);

      pActScale[3] = pmnuSubMenuShow->addAction("75");
      pActScale[3]->setCheckable(true);

      pActScale[3]->setIcon(QIcon(":/rec/images/scale75.png"));

      pActScale[3]->setIconVisibleInMenu(false);

      pActScale[4] = pmnuSubMenuShow->addAction("32");
      pActScale[4]->setCheckable(true);
      pActScale[4]->setIcon(QIcon(":/rec/images/scale32.png"));

      pActScale[4]->setIconVisibleInMenu(false);

      connect(pmnuSubMenuShow,SIGNAL(triggered(QAction*)),SLOT(slotChangeScale(QAction*)));


      QMenu* pmnuSubMenuHeight = new QMenu(tr("Высота СИ X-H"),pmnuMode);
      pmnuMode->addMenu(pmnuSubMenuHeight);
      pActHeight[0] = pmnuSubMenuHeight->addAction(tr("40 км"));
////      pActHeight40->actionGroup();
      pActHeight[0]->setCheckable(true);
      pActHeight[0]->setChecked(true);

      pActHeight[0]->setIcon(QIcon(":/rec/images/H40.png"));

      pActHeight[0]->setIconVisibleInMenu(false);


      pActHeight[1] = pmnuSubMenuHeight->addAction(tr("20 км"));
      pActHeight[1]->setCheckable(true);

      pActHeight[1]->setIcon(QIcon(":/rec/images/H20.png"));

      pActHeight[1]->setIconVisibleInMenu(false);

      pActHeight[2] = pmnuSubMenuHeight->addAction(tr("10 км"));
      pActHeight[2]->setCheckable(true);
      pActHeight[2]->setIcon(QIcon(":/rec/images/H10.png"));

      pActHeight[2]->setIconVisibleInMenu(false);
      connect(pmnuSubMenuHeight,SIGNAL(triggered(QAction*)),SLOT(slotChangeH(QAction*)));

//      QMenu* pmnuSubMenuImit = new QMenu(tr("Имитация"),pmnuMode);
//     pmnuMode->addMenu(pmnuSubMenuImit);


     QAction* pactOnImit = new QAction("Start Imit", 0);
      pactOnImit->setText("&Имитация..."); // изменяет Open file
      pactOnImit->setShortcut(QKeySequence("CTRL+I"));
      pactOnImit->setToolTip("Запустить имитацию");
      pactOnImit->setStatusTip("Запустить имитацию");
      pactOnImit->setWhatsThis("Запустить имитацию");
////      pactOpen->setIcon(QPixmap(fileopen));

      connect(pactOnImit, SIGNAL(triggered()), this, SLOT(OnImit()));
     pmnuMode->addAction(pactOnImit);



    QMenu* pmnuHelp = new QMenu(tr("&Помощь"));


    menuBar()->addMenu(pmnuFile);
    menuBar()->addMenu(pmnuMode);
    menuBar()->addMenu(pmnuHelp);
 ////   pmnuHelp->addAction(tr("О программе"),this,SLOT(slotAbout()),Qt::Key_F1);
    pmnuHelp->addAction(tr("О программе"),Qt::Key_F1,this,SLOT(slotAbout()));


    QToolBar* ptbFile = new QToolBar("File Operations");
    ptbFile->addAction(pactNew);
    ptbFile->addAction(pactOpen);
    ptbFile->addAction(pactSave);

    for (int i=0;i<5;i++)
        ptbFile->addAction(pActScale[i]);

    for (int i=0;i<3;i++)
        ptbFile->addAction(pActHeight[i]);



    addToolBar(Qt::RightToolBarArea, ptbFile);


 ////   statusBar()->addWidget(new QLabel(this));
    setCentralWidget(pView);
    setWindowTitle(TITLE_NO_NAME);

    tmr = new QTimer();

    connect(tmr, SIGNAL(timeout()),this, SLOT(OnTime()));
//    tmr->start(500);  // таймер срабатывает 2 раза в секунду
    connect(&imit_tread, SIGNAL(MkTimeEvent()),this, SLOT(OnTime()));

}

MainwindowTrace::~MainwindowTrace()
{
    
}
void MainwindowTrace::slotAbout()
{
    QMessageBox::about(this,tr("Писалка трасс"),tr("Версия 1.0"));
}
void MainwindowTrace::slotChangeScale(QAction* prAc)
{
 QString str = prAc->text();
 MKApp* pMKApp=(MKApp*)qApp;

 if (pMKApp->scon.dist==str.toInt())
     return;
 for (int i=0;i<5;i++)
    pActScale[i]->setChecked(false);

 switch(str.toInt()) {
  case 500:
     pActScale[0]->setChecked(true);
     pMKApp->scon.dist=str.toInt();
  break;
  case 300:
     pActScale[1]->setChecked(true);
     pMKApp->scon.dist=str.toInt();

  break;
  case 150:
     pActScale[2]->setChecked(true);
     pMKApp->scon.dist=str.toInt();

  break;
  case 75:
     pActScale[3]->setChecked(true);
     pMKApp->scon.dist=str.toInt();

  break;
  case 32:
     pActScale[4]->setChecked(true);
     pMKApp->scon.dist=str.toInt();

  break;

 }
 New_traceView* pView = dynamic_cast<New_traceView*> (centralWidget());
 pView->pIKO->update();

}
void MainwindowTrace::slotChangeH(QAction* pHAc)
{
 MKApp* pMKApp=(MKApp*)qApp;
 QString str = pHAc->text();
 str=str.mid(0,2);

 for (int i=0;i<3;i++)
    pActHeight[i]->setChecked(false);

 switch(str.toInt()) {
  case 40:
     pActHeight[0]->setChecked(true);
     pMKApp->scon.h=40;

  break;
  case 20:
     pActHeight[1]->setChecked(true);
//     scon.h=str.toInt();
      pMKApp->scon.h=str.toInt();

  break;
  case 10:
     pActHeight[2]->setChecked(true);
     pMKApp->scon.h=str.toInt();

  break;

 }
 New_traceView* pView = dynamic_cast<New_traceView*> (centralWidget());
 pView->psi_xh->update();

}
void MainwindowTrace::slotNew()
{
 New_traceView* pView = dynamic_cast<New_traceView*> (centralWidget());

 pView->GetDocument()->DeleteAllTras();
 pView->pIKO->update();
 pView->psi_xh->update();

 pView->SetCurSel(0);
 pView->CorNTras(0);
 pView->FillList();
}
// Слот Сохранить как
void MainwindowTrace::slotSaveAs()
{
    New_traceView* pView = dynamic_cast<New_traceView*> (centralWidget());
    DocTras* pdoc= pView->GetDocument();

    if (pdoc->m_Trackes.size()==0)
    {
     QMessageBox msg;
    msg.setWindowTitle(tr("Замечание"));
     msg.setText(tr("Нет трасс"));
     msg.setStandardButtons(QMessageBox::Cancel);
     msg.exec();
     return;
    }

    QString str=QFileDialog::getSaveFileName(this,"Выбор файла","","*.trc ");
    if (str.size()==0)
        return;
     setWindowTitle("trace-"+str);
     setWindowFilePath(str);
     CommonSave();
}

void MainwindowTrace::slotSave()
{
 if (windowTitle()==TITLE_NO_NAME)
 {
  QString str=QFileDialog::getSaveFileName(this,"Выбор файла","","*.trc ");
  if (str.size()==0)
      return;
   setWindowTitle("trace-"+str);
   setWindowFilePath(str);

 }
#if 0
 QString fname= windowFilePath();

 New_traceView* pView = dynamic_cast<New_traceView*> (centralWidget());
 DocTras* pdoc= pView->GetDocument();
 pdoc->Save(fname);
#endif
 CommonSave();
}
//**********************************************************
//
void MainwindowTrace::OnOpen()
{
 QString str=QFileDialog::getOpenFileName(this,"Открыть файл","","*.trc");//После закрытия диалогового окна мы проверяем
 if (str.isEmpty())  return;
 setWindowTitle("Имя файла - "+str);

 New_traceView* pView = dynamic_cast<New_traceView*> (centralWidget());
 DocTras* pdoc= pView->GetDocument();
 pdoc->Load(str);
 pView->CorNTras(0);

}
void MainwindowTrace::CommonSave()
{

    QString fname= windowFilePath();

    New_traceView* pView = dynamic_cast<New_traceView*> (centralWidget());
    DocTras* pdoc= pView->GetDocument();
    pdoc->Save(fname);

}
// Вызов диалога запуска имитации
void MainwindowTrace::OnImit()
{
  MKApp* pMKApp=(MKApp*)qApp;

  DlgImit plg(this);

  if ( plg.exec()==QDialog::Accepted)
  {
      New_traceView* pView = dynamic_cast<New_traceView*> (centralWidget());
      DocTras* pdoc= pView->GetDocument();

      if (pdoc->m_Trackes.size()==0)
      {
          //MessageBox("Идиот! Введи трассы .","Нечему летать",MB_OK);
          QMessageBox::information(nullptr,"Идиот! Введи трассы .","Нечему летать");
          pMKApp->scon.status=0;  // нет полетов
          return;  // нет трасс
      }
      pMKApp->scon.status=1; // запуск полетов
      pView->beg_tick = GetTickCount();  //GetTickCount64();
      pView->trace_time=0;  // время движения при имитации
      pdoc->SetStartTime();  // установка задержек, для обработки точек рубежа

      if (pMKApp->GetImitType()==1)
       tmr->start(pMKApp->GetSleepingTime());
      if (pMKApp->GetImitType()==2)
         imit_tread.start();
      return;
  }
  if (pMKApp->GetImitType()==1)
   tmr->stop(); // остановка таймера
//  if (qApp->GetImitType()==2)
//    imit_tread.finished();
  //imit_tread.fi
  pMKApp->scon.status=0;  // нет полетов

 // delete plg ;

}
// Продвижение и отображение трасс -- public слот
void MainwindowTrace::OnTime()
{
    MKApp* pMKApp=(MKApp*)qApp;

    if (pMKApp->scon.status!=1)
          return;

    New_traceView* pView = dynamic_cast<New_traceView*> (centralWidget());
///    DocTras* pdoc= pView->GetDocument();

     pView->trace_time = pView->trace_time+ ((GetTickCount()-(double)pView->beg_tick)*(pMKApp->scon.v_imi+1))/CLOCKS_PER_SEC;  //1000;
     pView->beg_tick =  GetTickCount();
     // вызов функции рисования трасс в

    pView->pIKO->update();
    pView->psi_xh->update();

}
