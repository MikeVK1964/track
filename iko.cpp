
#include <QtGui>
////#include <QTextCodec>
#include <QMessageBox>
#include <QMenu>

#include "iko.h"
#include "setcontrol.h"
#include "convcoor.h"
#include "mainwindowTrace.h"
#include "new_traceview.h"
#include "maketras.h"
#include "convcoor.h"
#include "si_xh.h"
#include "proppointtr.h"
#include "DocTrace.h"
////#include "rightform.h"
#include "mkapp.h"

extern MainwindowTrace* pMW;


//IKO::IKO(QWidget *parent) : QLabel(parent)
IKO::IKO(QWidget *parent) : BaseIko(parent)
{
////    setMinimumSize(550,550);

    DragMode = false;
//   setMouseTracking(true); //
}

void IKO::paintEvent(QPaintEvent* pe)
{
    BaseIko::paintEvent(pe);

    QPainter painter;
    painter.begin(this);


 if (pMW!=0) {
  New_traceView* pView = dynamic_cast<New_traceView*> (pMW->centralWidget());
  DocTras* m_pDoc=pView->GetDocument();
  QVector<Tras>::iterator it=m_pDoc->m_Trackes.begin();

////  painter.setPen(QPen(Qt::black,3)); // установка пера
  //рисование целей
  QPoint center;
  center.setX((width()-0.5)/2);
  center.setY(height()/2);
 // extern   SetControl scon; // управляющие параметры
  MKApp* pMKApp=(MKApp*)qApp;

  for (; it!=m_pDoc->m_Trackes.end();++it)
  {
   Tras tr=*it;
   QSize sz_pix;

   sz_pix.setHeight(height());
   sz_pix.setWidth(width());
   // рисование трассы на ИКО

   tr.Draw(painter,sz_pix,pMKApp->scon.dist);

   if (pMKApp->scon.status==1)  // включен режим имитации
   {

       TargetPositionNet tpn;
       if (tr.GetCoor(pView->trace_time,tpn)) {

           ShowTarget(painter,tpn);
       }
   }
  }
  if (DragMode)
  {
   int cur_sel = pView->GetCurSel();

   int num_lp= m_pDoc->m_Trackes[cur_sel-1].m_TrasPoint.size(); // номер последней точки выбранной трассы
   float fx,fy; // последняя точка выбранной трассы
   int x,y;

   DkmBToXY(m_pDoc->m_Trackes[cur_sel-1].m_TrasPoint[num_lp-1].D,m_pDoc->m_Trackes[cur_sel-1].m_TrasPoint[num_lp-1].B,
          fx,fy);
   x = fx*width()/(pMKApp->scon.dist*2)+(float)width()/2;
   y =  -fy*height()/(pMKApp->scon.dist*2) + (float)height()/2;
   painter.drawLine(x,y,dragPoint.x(),dragPoint.y());
  }
 }

 painter.end();



}

void IKO::mousePressEvent(QMouseEvent *event)
{

 if (event->button() == Qt::LeftButton) {

  New_traceView* pView = dynamic_cast<New_traceView*> (pMW->centralWidget());

  float dkm,b;


  GetDB(event->pos(),dkm,b);

  int cur_sel = pView->GetCurSel();
  if (cur_sel==0) // Новая трасса
  {

   pView->AddTras(b,dkm);
   this->update();
   pView->psi_xh->update();
  }
  else
  {
   int num_point=0;  // поиск последней точки
   int rc=pView->GetDocument()->FindTras(cur_sel-1,b,dkm,2,5,num_point);
   if (rc!=-1)  // Трасса найдена
   {
       DragMode=true;
       if (cur_sel!=rc+1)
        pView->CorNTras(rc+1);
   }
  }

 }
 if (event->button() == Qt::RightButton) {
   slotShowContextMenu(event->pos());
 }
 event->accept();

}

void IKO::mouseReleaseEvent(QMouseEvent *event)
{
 if (event->button() == Qt::LeftButton) {
  if (DragMode) {
   New_traceView* pView = dynamic_cast<New_traceView*> (pMW->centralWidget());
   int cur_sel = pView->GetCurSel();
   if (cur_sel!=0) //  трасса выбрана
   {
    float xkm,b;
    GetDB(event->pos(),xkm,b);
    DocTras* pDoc=pView->GetDocument();

    int rc= pDoc->m_Trackes[cur_sel-1].AddTP(b,xkm,pView->GetDefH(),pView->GetDefA(),pView->GetDefV());
    if (rc==0)
    {
     pView->FillList();
    }
    if (rc==1) QMessageBox::information(NULL,"V==0",QObject::tr("Ошибка"));
    if (rc==2) QMessageBox::warning(NULL,"Совпадающие точки",QObject::tr("Ошибка"));
    if (100<rc)
    {
     QString str;
     str.number(rc);
     str=tr("Ошибочный участок ")+str;
     QMessageBox::warning(NULL,QObject::tr("Ошибка"),str);
    }

   }
   DragMode = false;
   this->update();
   pView->psi_xh->update();

  }
  event->accept();
 }
}

void IKO::mouseMoveEvent(QMouseEvent *event)
{
 if (DragMode)
 {
  dragPoint=event->pos(); // Сохраняем последнюю  точку
  this->update();
 }
 BaseIko::mouseMoveEvent(event);
//    QPoint p1=event->pos();

//    float distance_km,bearing_gr;

//    GetDB(p1,distance_km,bearing_gr);

//    QString str;
//    QString str_b="D:%1";
//    str=str_b.arg(QString::number(distance_km,'g',5));

//    str=str+QString(QObject::tr(" км"));
//    emit signalDistance(str);

//    str_b="B: %1";
//    str=str_b.arg(QString::number(bearing_gr,'g',5));
//    str=str+QString(QObject::tr(" град."));
//    emit signalBearing(str);

//    float xx,yy;
//    DkmBToXY(distance_km, bearing_gr,xx, yy);

//    str_b="X: %1";
//    str=str_b.arg(QString::number(xx,'g',5));
//    str=str+QString(QObject::tr(" км"));
//    emit sigXkm(str);


//    str_b="Y: %1";
//    str=str_b.arg(QString::number(yy,'g',5));
//    str=str+QString(QObject::tr(" км"));
//    emit sigYkm(str);


//    event->accept();
}
void IKO::slotShowContextMenu(const QPoint& pos)
{
 New_traceView* pView = dynamic_cast<New_traceView*> (pMW->centralWidget());
 int cur_sel = pView->GetCurSel();
 DocTras* pDoc = pView ->GetDocument();
 float xkm,b;
 GetDB(pos,xkm,b);
 int num_point1=1;  // поиск любой точки
 int rc=pDoc->FindTras(cur_sel-1,b,
             xkm,2,5,num_point1);

 if (rc!=-1)  // Трасса найдена
 {

  pView->SetCurSel(rc+1);  // установка комбобокс  0 -- новая
  num_point=num_point1;
  QMenu Ikomnu;
  Ikomnu.addAction("Удалить трассу",this,SLOT(OnDelTr()));
  Ikomnu.addAction("Точка рубежа",this,SLOT(OnRubeg()));

  Ikomnu.addAction("Удалить точку трассы",this,SLOT(OnDelTP()));
  Ikomnu.addAction("Свойства точки",this,SLOT(OnProp()));

  Ikomnu.exec(mapToGlobal(pos));
 }

}
//************************************************************************
// слот удаления трассы
void IKO::OnDelTr()
{
 New_traceView* pView = dynamic_cast<New_traceView*> (pMW->centralWidget());
 int cur_sel = pView->GetCurSel();
 DocTras* pDoc = pView ->GetDocument();
//// pDoc->m_Trackes.remove(cur_sel-1);

if (cur_sel<1)
{
    QMessageBox::information(this,"Ошибка","трасса не выбрана");
    return;
}
pDoc->m_Trackes.erase(
     pDoc->m_Trackes.begin()+cur_sel-1);

 pView->CorNTras(0);
 this->update();
 pView->psi_xh->update();
}
void IKO::OnRubeg()
{
 New_traceView* pView = dynamic_cast<New_traceView*> (pMW->centralWidget());
 int cur_sel = pView->GetCurSel();
 DocTras* pDoc = pView ->GetDocument();
 pDoc->m_Trackes[cur_sel-1].NumTR=num_point;
 update();
 pView->psi_xh->update();

}
//**********************************
// Удаление части точек трассы
//**********************************
void IKO::OnDelTP()
{
 New_traceView* pView = dynamic_cast<New_traceView*> (pMW->centralWidget());
 int cur_sel = pView->GetCurSel();
 DocTras* pDoc = pView ->GetDocument();
 if (cur_sel==0) return;
 if (num_point==0)
 {
  QMessageBox::StandardButtons rc =   QMessageBox::information(this,"Удалить трассу",
                                                               "Единственная точка",QMessageBox::Ok | QMessageBox::No );
  if (rc== QMessageBox::Ok)
  {
   OnDelTr();
   pView->CorNTras(0);
  }
 }
 else
 {
  pDoc->m_Trackes[cur_sel-1].m_TrasPoint.erase(
    pDoc->m_Trackes[cur_sel-1].m_TrasPoint.begin()+num_point,
    pDoc->m_Trackes[cur_sel-1].m_TrasPoint.end());
  pDoc->m_Trackes[cur_sel-1].CheckTras();
  if (num_point<= pDoc->m_Trackes[cur_sel-1].NumTR)
   pDoc->m_Trackes[cur_sel-1].NumTR = 0;
  pView->CorNTras(cur_sel);

 }
 update();
 pView->psi_xh->update();

}
void IKO::OnProp()
{
 New_traceView* pView = dynamic_cast<New_traceView*> (pMW->centralWidget());
 int cur_sel = pView->GetCurSel();
 DocTras* pDoc = pView ->GetDocument();

 Tras tr(pDoc->m_Trackes[cur_sel-1]); // Cоздаем копию выбранной трассы
 PropPointTr* pdlg = new PropPointTr(tr,num_point,this);
 if (pdlg->exec() == QDialog::Accepted) {
  pDoc->m_Trackes[cur_sel-1]=tr;
  pView->CorNTras(cur_sel);
 }
 delete pdlg;
}
//Событие изменение размеров
void IKO::ResizeEvent(QResizeEvent* e)
{
 int w = e->size().width();
 int h = e->size().height();
 resize(w,h);
}
int IKO::heightForWidth(int w)
{
    return w;
}
//void IKO::ShowTarget(QPainter& painter,TargetPositionNet tpn)
//{
//  MKApp* pMKApp=(MKApp*)qApp;

//  int x = tpn.fx_km*width()/(pMKApp->scon.dist*2)+(float)width()/2;
//  int y = - tpn.fy_km*height()/(pMKApp->scon.dist*2) + (float)height()/2;

//  painter.drawRect(x-3,y-3,6,6);


//}
