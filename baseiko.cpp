#include <QtGui>

#include "baseiko.h"
#include "mkapp.h"
#include "convcoor.h"
#include "maketras.h"
#include "mainwindowTrace.h"
#include "new_traceview.h"

BaseIko::BaseIko(QWidget *parent): QLabel(parent)
{

    setMinimumSize(550,550);
    setMouseTracking(true); //

}
void BaseIko::paintEvent(QPaintEvent*)
{
    QPainter painter;
    painter.begin(this);
///    painter.setPen(QPen(QColor(100,100,0),4));
    QImage imp_salut(":/rec/images/salut.png");

     painter.drawImage(0,0,imp_salut);
     painter.drawEllipse(QRectF(0.5,0,width()-1,height()-0.5));
     painter.drawEllipse(QRectF(width()/4,height()/4,width()/2,height()/2));
     painter.drawLine(QPointF(width()/2,0),QPointF(width()/2,height()-0.5));
     // ось Х

     painter.drawLine(QPointF(0,height()/2),QPointF(width(),height()/2));

     extern MainwindowTrace* pMW;

     New_traceView* pView = dynamic_cast<New_traceView*> (pMW->centralWidget());

     ThreadsController* pThreadsController= pView->GetpThreadContr();
     if (pThreadsController!=nullptr)
     {

    //  QVector<TargetPositionNet>::iterator it= vnettar1.begin();
      QVector<TargetPositionNet>::iterator it= pThreadsController->vnettar1.begin();

      for (; it!= pThreadsController->vnettar1.end();++it)
      {
        ShowTarget(painter,*it);

      }
      qDebug() << "paintEvent" << pThreadsController->vnettar1.count() ;

     }

    painter.end();

}
// Получить дальность - пеленг
void BaseIko::GetDB(QPoint mp, float &distance_km, float &b)
{
    MKApp* pMKApp=(MKApp*)qApp;

    QPoint center;
    center.setX((width()-0.5)/2.0);
    center.setY(height()/2.0);

    double ksq1=4*pMKApp->scon.dist*pMKApp->scon.dist;
    double sq1=ksq1*(center.x()-mp.x())*(center.x()-mp.x());
    sq1=sq1/(width()*width());

    double sq2=ksq1*(center.y()-mp.y())*(center.y()-mp.y())
            /(height()*height());
    double sq3=sq1+sq2;
    distance_km =sqrt(sq3);

    int x,y;
    x=mp.x()-center.x();
    y=center.y()-mp.y();

    if ((x==0)&&(y==0))
    {
     b=-1;distance_km=0;
    }
    else
    {
        double x_km=x*pMKApp->scon.dist/width();
        double y_km=y*pMKApp->scon.dist/height();
        double b_grad,sq;
        GetBG( x_km,y_km,b_grad,sq); // получить пеленг в град и даль хY
        b=(float)b_grad;
    }

}
void BaseIko::ShowTarget(QPainter& painter,TargetPositionNet tpn)
{
  MKApp* pMKApp=(MKApp*)qApp;

  int x = tpn.fx_km*width()/(pMKApp->scon.dist*2)+(float)width()/2;
  int y = - tpn.fy_km*height()/(pMKApp->scon.dist*2) + (float)height()/2;

  painter.drawRect(x-3,y-3,6,6);

}
void BaseIko::mouseMoveEvent(QMouseEvent *event)
{
    QPoint p1=event->pos();

    float distance_km,bearing_gr;

    GetDB(p1,distance_km,bearing_gr);

    QString str;
    QString str_b="D:%1";
    str=str_b.arg(QString::number(distance_km,'g',5));

    str=str+QString(QObject::tr(" км"));
    emit signalDistance(str);

    str_b="B: %1";
    str=str_b.arg(QString::number(bearing_gr,'g',5));
    str=str+QString(QObject::tr(" град."));
    emit signalBearing(str);

    float xx,yy;
    DkmBToXY(distance_km, bearing_gr,xx, yy);

    str_b="X: %1";
    str=str_b.arg(QString::number(xx,'g',5));
    str=str+QString(QObject::tr(" км"));
    emit sigXkm(str);


    str_b="Y: %1";
    str=str_b.arg(QString::number(yy,'g',5));
    str=str+QString(QObject::tr(" км"));
    emit sigYkm(str);


    event->accept();

}
void BaseIko::SlotShowTargets()
{
//    QPainter painter;
//    painter.begin(this);
//     QVector<TargetPositionNet>::iterator it= vnettar.begin();

//     for (; it!= vnettar.end();++it)
//     {
//        ShowTarget(painter,*it);

//     }
//    painter.end();
//   vnettar1=vnettar;
   qDebug() << "BaseIko::SlotShowTargets"  ;

   update();

}
