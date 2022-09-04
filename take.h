#ifndef TAKE_H
#define TAKE_H
#include <QDialog>
#include "laptopdata.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class Take;
}
QT_END_NAMESPACE

class Take : public QDialog
{
    Q_OBJECT
public:
    Take(QWidget *parent = nullptr);
    ~Take();
    void sShow();

private:
    Ui::Take *ui;
    void updateUI();
signals:
 void tSignal();
private slots:
 void on_buttonTake_clicked();
};

#endif // TAKE_H
