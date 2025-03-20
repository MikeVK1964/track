#include "proppointtr.h"
#include "ui_proppointtr.h"
#include "maketras.h"
#include "convcoor.h"
#include <QMessageBox>

PropPointTr::PropPointTr(Tras& tr,int num_point1,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PropPointTr)
{
 ui->setupUi(this);
 setWindowFlags(windowFlags() & (~Qt::WindowContextHelpButtonHint)); // Убрать кнопку ?

 setFixedSize(size()); // Зафиксировать размер диалога
 QString str;
 str.asprintf("свойства точки  N %d",num_point1+1);
 setWindowTitle(str);

 num_point= num_point1;
 ptr=&tr;
 ui->dSBox_B->setValue(tr.m_TrasPoint[num_point].B);
 ui->dSBox_D->setValue(tr.m_TrasPoint[num_point].D);
 float fx,fy;
 DkmBToXY(ptr->m_TrasPoint[num_point].D,ptr->m_TrasPoint[num_point].B, fx, fy);
 ui->doubleSpinBox_X->setValue(fx);
 ui->doubleSpinBox_Y->setValue(fy);
 ui->spinBox_H->setValue(tr.m_TrasPoint[num_point].H);
 ui->spinBox_V->setValue(tr.m_TrasPoint[num_point].V);
 ui->spinBox_A->setValue(tr.m_TrasPoint[num_point].A);

// Установка свой-чужой
 ui->comboBox_IFF->addItem("неопр.");
 ui->comboBox_IFF->addItem("свой");
 ui->comboBox_IFF->addItem("чужой");
 ui->comboBox_IFF->addItem("СКВ");
 ui->comboBox_IFF->setCurrentIndex(tr.type_tar);
}
void PropPointTr::accept()
{
 float fx,fy;
 if (ui->checkBox_flagXY->checkState()==Qt::Checked)
 {
  fx=ui->doubleSpinBox_X->value();
  fy=ui->doubleSpinBox_Y->value();
  if (500<sqrt(fx*fx+fy*fy))
  {
   QMessageBox::information(this,"Ошибка","Дальность больше 500 км");
   return;
  }
  GetBG(fx,fy,ptr->m_TrasPoint[num_point].B,
   ptr->m_TrasPoint[num_point].D);

 }
 else
 {
  ptr->m_TrasPoint[num_point].B=ui->dSBox_B->value();
  ptr->m_TrasPoint[num_point].D=ui->dSBox_D->value();
 }
 ptr->type_tar=static_cast<kmb_trace::TargetType>(ui->comboBox_IFF->currentIndex());
 ptr->m_TrasPoint[num_point].H=ui->spinBox_H->value();
 ptr->m_TrasPoint[num_point].V=ui->spinBox_V->value();
 ptr->m_TrasPoint[num_point].A=ui->spinBox_A->value();
 int rc=ptr->CheckTras();
 if (rc!=0)
 {
  QMessageBox::warning(this,"","");
  return;
 }
///return; // запрет закрытия диалога
 QDialog::accept();
}

PropPointTr::~PropPointTr()
{
    delete ui;
}
