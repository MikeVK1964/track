#ifndef BASEIKO_H
#define BASEIKO_H

#include <QLabel>
#include <QObject>
#include "maketras.h"

//class TargetPositionNet;

class BaseIko : public QLabel
{
    Q_OBJECT
public:
    BaseIko(QWidget *parent = 0);
protected:
 virtual void paintEvent(QPaintEvent*) override;
    // Получить дальность - пеленг
  void GetDB(QPoint mp, float &distance_km, float &b);
  void ShowTarget(QPainter& painter,TargetPositionNet tpn);
  void mouseMoveEvent(QMouseEvent *event);
  void BaseConstruct();
signals:
    void signalBearing(QString strb);
    void signalDistance(QString d);
    void sigXkm(QString sxkm);
    void sigYkm(QString sykm);
public slots:
    void SlotShowTargets();
//private:
//   QVector<TargetPositionNet> vnettar1;
};

#endif // BASEIKO_H
