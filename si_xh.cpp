#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>

#include "si_xh.h"
#include "setcontrol.h"
#include "mainwindowTrace.h"
#include "new_traceview.h"
#include "maketras.h"
#include "DocTrace.h"
#include "mkapp.h"

//extern SetControl scon; // управляющие параметры
extern MainwindowTrace* pMW;


SI_XH::SI_XH(QWidget *parent) :
    QWidget(parent)
{
  setMouseTracking(true); //

}

void SI_XH::paintEvent(QPaintEvent* /*paint*/)
{
 MKApp* pMKApp=(MKApp*)qApp;
 QPainter painter;
 if (pMW!=0) {
  New_traceView* pView = dynamic_cast<New_traceView*> (pMW->centralWidget());
  DocTras* m_pDoc=pView->GetDocument();
  QVector<Tras>::iterator it=m_pDoc->m_Trackes.begin();

  painter.begin(this);
  QSize sz_pix;
  sz_pix.setHeight(height());
  sz_pix.setWidth(width());

  // цикл по всем трассам
   for (; it!=m_pDoc->m_Trackes.end();++it)
   {

    it->DrawH(painter,sz_pix,pMKApp->scon.dist,pMKApp->scon.h ) ;
    if (pMKApp->scon.status==1)  // включен режим имитации
    {
        TargetPositionNet tpn;
        if (it->GetCoor(pView->trace_time,tpn)) {
            ShowTarget(painter, tpn);
//            int x = tpn.fx_km*width()/(pMKApp->scon.dist*2)+(float)width()/2;
//            int y = - tpn.ih_m*height()/(pMKApp->scon.h*1000) + (float)height();
//            painter.drawRect(x-3,y-5,6,6);

        }
    }

   }
//
  painter.end();
 }
}
void SI_XH::mouseMoveEvent(QMouseEvent *event)
{
 MKApp* pMKApp=(MKApp*)qApp;

 QPoint point=event->pos();
 float ftmp;
 ftmp =
         ((height() -point.y()-1.0)*(float)pMKApp->scon.h)
     /height();
 QString str;


 str.setNum(ftmp,'g',5);
 str="H: "+str+QString(tr(" км"));

 emit signalH(str);
 event->accept();

}
void SI_XH::ShowTarget(QPainter& painter,TargetPositionNet tpn)
{
    MKApp* pMKApp=(MKApp*)qApp;

    int x = tpn.fx_km*width()/(pMKApp->scon.dist*2)+(float)width()/2;
    int y = - tpn.ih_m*height()/(pMKApp->scon.h*1000) + (float)height();
    painter.drawRect(x-3,y-5,6,6);

}
