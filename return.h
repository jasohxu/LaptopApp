#ifndef RETURN_H
#define RETURN_H
#include <QDialog>
#include "laptopdata.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class Return;
}
QT_END_NAMESPACE

class Return : public QDialog
{
    Q_OBJECT
public:
    Return(QWidget *parent = nullptr);
    ~Return();
    void sShow();

private:
    Ui::Return *ui;
    void updateUI();

signals:
 void rSignal();
private slots:
 void on_btnReturn_clicked();
};

#endif // RETURN_H
