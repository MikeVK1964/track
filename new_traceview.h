#ifndef NEW_TRACEVIEW_H
#define NEW_TRACEVIEW_H
#include <qsplitter.h>
#include <QStandardItem>
#include <QTimer>
#include <QTime>
#include "mknetserver.h"
#include "baseview.h"
#include "threadscontroller.h"

class RightForm;
//class IKO;
class SI_XH;
class DocTras;
class BaseIko;
//BaseView
//class New_traceView : public QSplitter
class New_traceView : public BaseView

{

public:
 New_traceView(QWidget* pwgt=0);
 ~New_traceView();
 ThreadsController* GetpThreadContr() {return pThreadsController;}

private:
   MKNetServer* m_pmkServer;
   ThreadsController* pThreadsController;

};

#endif // NEW_TRACEVIEW_H
