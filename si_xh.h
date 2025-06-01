#ifndef SI_XH_H
#define SI_XH_H

#include <QWidget>

//class QPaintEvent;
class TargetPositionNet;
class SI_XH : public QWidget
{
    Q_OBJECT
public:
    explicit SI_XH(QWidget *parent = 0);
protected:
 virtual void paintEvent(QPaintEvent*);
 virtual void mouseMoveEvent(QMouseEvent *event);
 void ShowTarget(QPainter& painter,TargetPositionNet tpn);

signals:
    void signalH(QString h) ;
public slots:
    
};

#endif // SI_XH_H
