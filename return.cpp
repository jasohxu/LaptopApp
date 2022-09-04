#include "return.h"
#include "ui_return.h"

Return::Return(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Return)
{
    ui->setupUi(this);
   connect(this, SIGNAL(rSignal()), parent, SLOT(sUUI()));
}

Return::~Return() {
    delete ui;
}

void Return::sShow() {
    updateUI();
    show();
}

void Return::updateUI() {
    ui->laptopsCB->clear();

    QSqlQuery query(LaptopData::getInstance()->getData());
    query.prepare("select lno from laptops where available='0'");

    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
        ui->lblDialog->setText(query.lastError().text());
    }
    else{
        qDebug() << "RTRN: "<< query.lastQuery();
       }

    while(query.next())
    {
        ui->laptopsCB->addItem(query.value(0).toString());
    }
    ui->btnReturn->setEnabled(true);
    if(ui->laptopsCB->count()<=0)
        ui->btnReturn->setEnabled(false);


}

void Return::on_btnReturn_clicked()
{
    QString sSlot = ui->laptopsCB->currentText();

    QSqlQuery query(LaptopData::getInstance()->getData());
    query.prepare("update laptops set available='1' where lno='" + sSlot + "' ");

    if(!query.exec())
    {
        qDebug() << "RTRN: " << query.lastError().text() << query.lastQuery();
        ui->lblDialog->setText(query.lastError().text());
    }
    else{
        if(query.numRowsAffected() > 0)
        {
            ui->lblDialog->setText("Laptop returned. Thank you.");
            qDebug() << "RTRN: Slot updated: "<< query.lastQuery();
            updateUI();
        }
        else
        {
            ui->lblDialog->setText("Error updating status.");
            qDebug() << "RTRN: Error: " << query.lastQuery();
        }
    }

     emit rSignal();
}
