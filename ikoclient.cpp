#include "ikoclient.h"
#include "maketras.h"
#include <QPainter>

ikoclient::ikoclient(QWidget *parent)
    :BaseIko(parent)
{

}
void ikoclient::SlotShowTargets(QVector<TargetPositionNet> vnettar)
{
    QPainter painter;
    painter.begin(this);
    QVector<TargetPositionNet>::iterator it= vnettar.begin();

    for (; it!= vnettar.end();++it)
    {
        ShowTarget(painter,*it);

    }
    painter.end();
}
