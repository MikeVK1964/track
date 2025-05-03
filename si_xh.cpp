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
        int z_m=0;
        float x_km=0;
        if (it->GetCurrentCoor_SI(z_m,x_km,pView->trace_time))  {
            int x = x_km*sz_pix.width()/(pMKApp->scon.dist*2)+(float)sz_pix.width()/2;
            int y = - z_m*sz_pix.height()/(pMKApp->scon.h*1000) + (float)sz_pix.height();
            painter.drawRect(x-3,y-5,6,6);

        }
//        it->ShowTrPosSI(painter,sz_pix,pMKApp->scon.dist,pMKApp->scon.h,pView->trace_time);
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


// str.asprintf("H%8.3f",ftmp);
  str.setNum(ftmp,'g',5);
/// QMessageBox::critical(NULL,"error",str);
 str="H: "+str+QString(tr(" км"));

 emit signalH(str);
 event->accept();

}
