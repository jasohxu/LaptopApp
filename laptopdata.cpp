#include "laptopdata.h"

LaptopData* LaptopData::instance = nullptr;

LaptopData::LaptopData() {
    qDebug() << "LPDT: Refreshing Database.";
    db = QSqlDatabase::addDatabase("QSQLITE", "Data");
    db.setDatabaseName("laptops.db");

    if(!QFile::exists("laptops.db")) {
           qDebug() << "LPDT: Data file doesn't exist. Please manually create a laptops.db database.";
    }
    if (db.open()) {
        qDebug() << "LPDT: Data located and ready.";
    }
    else {
        qDebug() << db.lastError().text();
    }
}

LaptopData* LaptopData::getInstance() {
    qDebug() << "LPDT: Getting instance.";

    if(instance == nullptr)
        instance = new LaptopData();

    return instance;
}

QSqlDatabase LaptopData::getData() {
    qDebug() <<"LPDT: Getting SQL Database.";
    return db;
}

void LaptopData::resetInstance() {
    qDebug() << "LPDT: Resetting Database to null.";
    delete instance;
    instance = nullptr;
}

LaptopData::~LaptopData() {
    qDebug() << "LPDT: Closing Database.";
    db.close();
}
