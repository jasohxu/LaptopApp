#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "take.h"
#include "return.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void sShow();

private slots:
    void on_btnTake_clicked();
    void on_btnReturn_clicked();

    void sUUI();

private:
    Ui::MainWindow *ui;
    void updateUI();
    Take *pTake;
    Return *pReturn;
};
#endif // MAINWINDOW_H
