#ifndef IKOCLIENT_H
#define IKOCLIENT_H

#include "baseiko.h"

class ikoclient : public BaseIko
{
public:
    ikoclient(QWidget *parent = 0);
private slots:
    void SlotShowTargets(QVector<TargetPositionNet> vnettar);
};

#endif // IKOCLIENT_H
