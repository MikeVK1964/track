#include "dlgimit.h"
#include "ui_dlgimit.h"
//#include "setcontrol.h"
#include "mkapp.h"

DlgImit::DlgImit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgImit)
{
    ui->setupUi(this);
}

DlgImit::~DlgImit()
{
    delete ui;
}

void DlgImit::on_pushButton_clicked()
{
    this->accept();
}


void DlgImit::on_comboBoxValSpeed_activated(int index)
{
//    extern SetControl scon; // управляющие параметры
    MKApp* pMKApp=(MKApp*)qApp;

    pMKApp->scon.v_imi = index;
}

