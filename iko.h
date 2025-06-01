#ifndef IKO_H
#define IKO_H
#include <QLabel>
#include "baseiko.h"

class TargetPositionNet;
//class IKO : public QLabel // QWidget
class IKO : public BaseIko // QWidget
{
    Q_OBJECT
public:
    explicit IKO(QWidget *parent = 0);
protected:
 virtual void paintEvent(QPaintEvent*) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    void slotShowContextMenu(const QPoint& pos);
    void ResizeEvent(QResizeEvent* e);
    virtual int heightForWidth(int w) ;

signals:
//    void signalBearing(QString strb);
//    void signalDistance(QString d);
//    void sigXkm(QString sxkm);
//    void sigYkm(QString sykm);
//    void signalAddTras(float b,float dxykm);
public slots:
    void OnDelTr();
    void OnRubeg();
    void OnDelTP();
    void OnProp();

private:
//    void ShowTarget(QPainter& painter,TargetPositionNet tpn);
    QList<QPoint> mDrawBuffer;

    bool DragMode;
    QPoint dragPoint;
    int num_point;  // найденная точка трассы при нажатии мышью

    
};

#endif // IKO_H
