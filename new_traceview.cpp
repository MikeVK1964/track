#include <QLabel>
#include <QObject>

#include "new_traceview.h"
#include "iko.h"
#include "rightform.h"
#include "ui_rightform.h"
#include "si_xh.h"
#include "maketras.h"
#include "convcoor.h"
#include "DocTrace.h"
#include "setcontrol.h"
#include "mkapp.h"
#include "ikoclient.h"

//************************************************************
// Главный winget MainwindowTrace
//     setCentralWidget(pView);
//     агрегатирована с классом    DocTras* m_pDocument;
//**************************************************
New_traceView::New_traceView(QWidget* parent)
    :BaseView(parent)
{
 MKApp* pMKApp=(MKApp*)qApp;
 if (pMKApp->IsClientNet())
 {
     pIKO=new ikoclient; //(BaseIko;
 }
 else {
     pIKO=new IKO;
 }
 psi_xh = new SI_XH;

 BaseView::BaseConstruct();
 if (pMKApp->IsClientNet())
 {
     pThreadsController = new ThreadsController();
//     connect(pThreadsController, SIGNAL(ShowTracks(QVector<TargetPositionNet> )),
//                    (ikoclient *)  pIKO, SLOT(SlotShowTargets(QVector<TargetPositionNet> )) );
     connect(pThreadsController, SIGNAL(SignalShowNetTracks1()),
                     pIKO, SLOT(SlotShowTargets()) );

     //SlotShowTargets(

 }
 else {
     m_pmkServer = new MKNetServer(2323,m_pDocument,parent);
 }

}

New_traceView::~New_traceView()
{
 delete m_pDocument;
 if (modelTrPoints)
  delete modelTrPoints;
}
