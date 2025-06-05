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

//************************************************************
// Главный winget MainwindowTrace
//     setCentralWidget(pView);
//     агрегатирована с классом    DocTras* m_pDocument;
//**************************************************
New_traceView::New_traceView(QWidget* parent)
    :QSplitter(Qt::Horizontal,parent)
{
 QSplitter* pleft;
 pright1 = new RightForm;

 pleft = new QSplitter(Qt::Vertical);

 pIKO=new IKO;
//// pleft->addWidget(new IKO);
 pleft->addWidget(pIKO);
 psi_xh = new SI_XH;

 pleft->addWidget(psi_xh);

 addWidget(pleft);

 addWidget(pright1);

 m_pDocument = new DocTras;

// connect(pIKO,SIGNAL(signalAddTras(float b,float dxykm)),
///         this,SLOT(slotAddTrass(float,float)));

// connect((BaseIko*)pIKO,SIGNAL(signalDistance(QString)),pright1->ui->label_Distance,
//         SLOT(setText(QString)));


 connect(pIKO,SIGNAL(signalDistance(QString)),pright1->ui->label_Distance,
         SLOT(setText(QString)));
 connect(pIKO,SIGNAL(signalBearing(QString)),pright1->ui->labelB,
                     SLOT(setText(QString)));

 connect(pIKO,SIGNAL(sigXkm(QString)),pright1->ui->label_Xkm,
                     SLOT(setText(QString)));

 connect(pIKO,SIGNAL(sigYkm(QString)),pright1->ui->label_Ykm,
                     SLOT(setText(QString)));


 connect(psi_xh,SIGNAL(signalH(QString)),pright1->ui->label_H,
                     SLOT(setText(QString)));

 m_ntr_val=0; // нет выбранных трасс
 modelTrPoints = new QStandardItemModel; // модель точек трассы
 m_pmkServer = new MKNetServer(2323,m_pDocument,parent);

}

New_traceView::~New_traceView()
{
 delete m_pDocument;
 if (modelTrPoints)
  delete modelTrPoints;
}
//****************************************
//  Изменение combo - N трасс
// заполнение таблицы точек выбранной трассы
void New_traceView::CorNTras(int num_pos)
{
 DocTras* m_pDoc=GetDocument();

 int num_tr =m_pDoc->m_Trackes.size(); // число трасс
 pright1->ui->cBNTRASS->clear();

 QString s;
 s=tr("новая");
 pright1->ui->cBNTRASS->addItem(s);
 for (int j=0;j<num_tr;j++)
 {
 ///  s.asprintf("%d",j+1);
   s=QString::number(j+1,10);
   pright1->ui->cBNTRASS->addItem(s);

 }
 pright1->ui->cBNTRASS->setCurrentIndex(num_pos);
/// pright1->ui->cBNTRASS->setCurrentIndex(num_tr);


/// FillList();  -- вызывается в SetCurSel
}
// Заполнение таблицы точек выбранной трассы
void New_traceView::FillList()
{
 modelTrPoints->clear();

 if (m_ntr_val==0) // номер трассы, выбранной в комбо
     return;
 QStringList horizontalHeader;

 horizontalHeader <<  QString(QObject::tr("B,град.")) << QString(QObject::tr("D,км"))<< QString(QObject::tr("X,км"))
  << QString(QObject::tr("Y,км")) << QString(QObject::tr("H,м"))<< QString(QObject::tr("Гос.оп.")) << QString(QObject::tr("V,м/с"))
  << QString(QObject::tr("A, м/(ceк*ceк)"));
 modelTrPoints->setHorizontalHeaderLabels(horizontalHeader);
 Tras tr=GetDocument()->m_Trackes[m_ntr_val-1];

 for (int i=0;i<tr.m_TrasPoint.size();i++)
 {
   FillElList(i);
 }
 pright1->ui->tableViewTrass->setModel(modelTrPoints);

}
// i - порядковый номер точки
// выводит строку в таблицу
void New_traceView::FillElList(int i)
{
 QString str;

 str.setNum(GetDocument()->m_Trackes[m_ntr_val-1].m_TrasPoint[i].B);
 modelTrPoints->setItem(i,0,new QStandardItem(str));

 str.setNum(GetDocument()->m_Trackes[m_ntr_val-1].m_TrasPoint[i].D);
 modelTrPoints->setItem(i,1,new QStandardItem(str));
 float xx,yy;

 DkmBToXY(GetDocument()->m_Trackes[m_ntr_val-1].m_TrasPoint[i].D,
     GetDocument()->m_Trackes[m_ntr_val-1].m_TrasPoint[i].B,xx, yy);
 //str.asprintf("%5.3f",xx);
 str.setNum(xx);
 modelTrPoints->setItem(i,2,new QStandardItem(str));

 //str.asprintf("%5.3f",yy);
 str.setNum(yy);

 modelTrPoints->setItem(i,3,new QStandardItem(str));

// str.asprintf("%d",GetDocument()->m_Trackes[m_ntr_val-1].m_TrasPoint[i].H);
 str.setNum(GetDocument()->m_Trackes[m_ntr_val-1].m_TrasPoint[i].H);
 modelTrPoints->setItem(i,4,new QStandardItem(str));
 kmb_trace::TargetType type_tar
       =GetDocument()->m_Trackes[m_ntr_val-1].type_tar;
 switch(type_tar) {
  case kmb_trace::Unknown:
     str=QObject::tr("неопр.");
     modelTrPoints->setItem(i,5,new QStandardItem(str));
  break;
 case kmb_trace::Foe:
    str=QObject::tr("чужой");
    modelTrPoints->setItem(i,5,new QStandardItem(str));
 break;
 case kmb_trace::Friend:
    str=QObject::tr("свой");
    QStandardItem* psi;
    psi =  new QStandardItem(str);
    psi->setForeground(Qt::red);
    modelTrPoints->setItem(i,5,psi);
 break;
 case kmb_trace::Our_Hel:
    str=QObject::tr("СКВ");
    modelTrPoints->setItem(i,5,new QStandardItem(str));
 break;

 }
 if (0<i) // для первой точки скорость и ускорение не важно
 {

//  str.asprintf("%d",GetDocument()->m_Trackes[m_ntr_val-1].m_TrasPoint[i].V)  ;
  str.setNum(GetDocument()->m_Trackes[m_ntr_val-1].m_TrasPoint[i].V);
  modelTrPoints->setItem(i,6,new QStandardItem(str));
  //str.asprintf("%d",GetDocument()->m_Trackes[m_ntr_val-1].m_TrasPoint[i].A)  ;
  str.setNum(GetDocument()->m_Trackes[m_ntr_val-1].m_TrasPoint[i].A);
  modelTrPoints->setItem(i,7,new QStandardItem(str));

 }
}
void New_traceView::AddTras(float B, float D)
{
 DocTras* m_pDoc;
 m_pDoc=GetDocument();

 ///int H=pright1->ui->lEH->text().toInt();
 int H = pright1->ui->sB_H->value();

 int ival;

 ival=pright1->ui->cBIFF->currentIndex();
 switch(ival) {
  case 0:
     m_pDoc->AddTras(B,D,H,kmb_trace::Unknown);
  break;
 case 1:
    m_pDoc->AddTras(B,D,H,kmb_trace::Friend);
 break;
 case 2:
    m_pDoc->AddTras(B,D,H,kmb_trace::Foe);
 break;
 case 3:
    m_pDoc->AddTras(B,D,H,kmb_trace::Our_Hel);
 break;

 }


 CorNTras(m_pDoc->m_Trackes.size());

}

void New_traceView::SetCurSel(int cur_sel)
{
 m_ntr_val=cur_sel;  // номер трассы, выбранной
 FillList();

}
// h - по умолчанию
int New_traceView::GetDefH()
{
 return pright1->ui->sB_H->value();
}
unsigned int New_traceView::GetDefA()
{
 return pright1->ui->lE_A->text().toUInt();
}
unsigned int New_traceView::GetDefV()
{
 return pright1->ui->lE_V->text().toUInt();
}
