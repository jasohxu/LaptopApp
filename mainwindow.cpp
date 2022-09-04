#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pReturn = new Return(this);
    pTake = new Take(this);

    connect(pTake, SIGNAL(tSignal()), this, SLOT(sUUI()));
    connect(pReturn, SIGNAL(rSignal()), this, SLOT(sUUI()));

    updateUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateUI()
{
    QSqlQuery query(LaptopData::getInstance()->getData());
    query.prepare("select lno, available, lastuser from laptops");

    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
        ui->lblInfo->setText(query.lastError().text());
    }
    else{
        qDebug() << "MAIN: Data located and read: "<< query.lastQuery();
    }

    while(query.next())
    {
        QString sLabel = "lbl" + query.value(0).toString();
        QLabel * ptr = this->findChild<QLabel*>(sLabel);
        if(ptr!=nullptr)
        {
            if(query.value(1) == 0)
            {
                ptr->setText("TAKEN\n(" + query.value(2).toString() + ")");
                qDebug() << "MAIN: Laptop " << query.value(0).toString() << " has been checked out.";
            }
            else
            {
                ptr->clear();
                ptr->setText(query.value(0).toString());
            }


        }
        qDebug()<<query.value(0).toString()<< query.value(1).toString();
    }

}


void MainWindow::on_btnTake_clicked()
{
    pTake->sShow();
}

void MainWindow::on_btnReturn_clicked()
{
    pReturn->sShow();
}

void MainWindow::sUUI() {
    updateUI();
}
