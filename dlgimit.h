#ifndef DLGIMIT_H
#define DLGIMIT_H

#include <QDialog>

namespace Ui {
class DlgImit;
}

class DlgImit : public QDialog
{
    Q_OBJECT

public:
    explicit DlgImit(QWidget *parent = nullptr);
    ~DlgImit();
    bool GetStateNetServer();
private slots:
    void on_pushButton_clicked();

    void on_comboBoxValSpeed_activated(int index);

private:
    Ui::DlgImit *ui;
};

#endif // DLGIMIT_H
