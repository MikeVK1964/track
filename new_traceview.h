#ifndef NEW_TRACEVIEW_H
#define NEW_TRACEVIEW_H
#include <qsplitter.h>
#include <QStandardItem>
#include <QTimer>
#include <QTime>

class RightForm;
//class IKO;
class SI_XH;
class DocTras;
class BaseIko;

class New_traceView : public QSplitter
{

public:
 New_traceView(QWidget* pwgt=0);
    ~New_traceView();
//    IKO* pIKO;
    BaseIko* pIKO;
    SI_XH*  psi_xh;
    inline int GetCurSel(){return m_ntr_val;}
    void SetCurSel(int cur_sel);

    inline DocTras* GetDocument()
       { return (DocTras*)m_pDocument; }

    void CorNTras(int num_pos);
    void FillElList(int i);
    void FillList();
    void AddTras(float B, float D);
    int GetDefH();
    unsigned int GetDefA();
    unsigned int GetDefV();

    RightForm* pright1;
    unsigned int beg_tick; //
    //ulong  beg_tick;  //clock_t  beg_tick;  // время начала имитации в mc
                        // CLOCKS_PER_SEC -- говорит, сколько тиков в секунде, обычно, 1000 --т.е. мс
    double trace_time; // время движения с начала имитации в секундах
    // не нужна т.к. можно вычислить локально
private:
   int		m_ntr_val;  // номер трассы, выбранной в комбо
   DocTras* m_pDocument;
   QStandardItemModel* modelTrPoints; // модель точек трассы
};

#endif // NEW_TRACEVIEW_H
