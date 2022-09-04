#ifndef LAPTOPDATA_H
#define LAPTOPDATA_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QFile>
#include <QDebug>
#include <QSqlError>

class LaptopData
{
public:
    static void resetInstance();
    static LaptopData* getInstance();
    QSqlDatabase getData();
    ~LaptopData();
private:
    LaptopData();
    static LaptopData* instance;
    QSqlDatabase db;
};

#endif // LAPTOPDATA_H
