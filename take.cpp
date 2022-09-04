#include "take.h"
#include "ui_take.h"

Take::Take(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Take)
{
    ui->setupUi(this);
   connect(this, SIGNAL(tSignal()), parent, SLOT(sUUI()));
}

Take::~Take() {
    delete ui;
}

void Take::sShow() {
    updateUI();
    show();
}

void Take::updateUI() {
    ui->laptopsCB->clear();

    QSqlQuery query(LaptopData::getInstance()->getData());
    query.prepare("select lno from laptops where available=1");

    if(!query.exec())
    {
        qDebug() <<"TAKE: "<< query.lastError().text() << query.lastQuery();
        ui->lblDialog->setText(query.lastError().text());
    }
    else{
        qDebug() << "TAKE: "<< query.lastQuery();
       }

    while(query.next())
    {

        ui->laptopsCB->addItem(query.value(0).toString());
    }
}

void Take::on_buttonTake_clicked() {
    QString sSlot = ui->laptopsCB->currentText();

    ui->laptopsCB->clear();
    ui->lblDialog->setText("");

    QSqlQuery query(LaptopData::getInstance()->getData());
    query.prepare("update laptops set available=0,lastuser=:user where lno='" + sSlot + "'");
    query.bindValue(":user",ui->userInput->text());

    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
        ui->lblDialog->setText(query.lastError().text());
    }
    else{
        if(query.numRowsAffected() > 0)
        {
            qDebug() << "TAKE: Laptop checked out: "<< query.lastQuery();
            ui->lblDialog->setText("Laptop successfully checked out.");
        }
        else {
            ui->lblDialog->setText("Error. Laptop could not be checked out.");
        }
       }
    ui->userInput->setText("Enter name");
    updateUI();
    emit tSignal();
}
