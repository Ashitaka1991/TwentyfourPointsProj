#include "originalnumber.h"
#include <cstdlib>
#include <ctime>
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>

OriginalNumber::OriginalNumber()
{

    initialRandomFunction();
    initialRandomBase();

}

OriginalNumber::~OriginalNumber()
{

}

//public functions
void OriginalNumber::generateNewNumbers()
{
    int r_id;

    r_id = generateRandomLine();
    getNumbers(r_id);


    //qDebug()

    return;
}

int OriginalNumber::getNum_1()
{
    return num_1;
}

int OriginalNumber::getNum_2()
{
    return num_2;
}

int OriginalNumber::getNum_3()
{
    return num_3;
}

int OriginalNumber::getNum_4()
{
    return num_4;
}



//private functions
int OriginalNumber::generateRandomLine()
{
    //Here needs a check function which checks whether the random id has been used.
    //It may implement with file data and set container.

    return ((rand()%num_quantity) + 1);
}

void OriginalNumber::getNumbers(int id)
{
    //qDebug() << "id: " << id << endl;

    QSqlQuery query;
    query.exec(QString("select num_1,num_2,num_3,num_4 from numbers_tbl "
               "where id = %1").arg(id));
    query.next();

    num_1 = query.value(0).toInt();
    num_2 = query.value(1).toInt();
    num_3 = query.value(2).toInt();
    num_4 = query.value(3).toInt();

    //qDebug() << "n1 : " << num_1 << "  n2: " << num_2 << "  n3: " << num_3 << "  n4: " << num_4 << endl;

    return;
}

void OriginalNumber::initialRandomFunction()
{
    srand((unsigned int)time(NULL));

    return;
}

void OriginalNumber::initialRandomBase()
{
    QSqlQuery query;
    query.exec("select count(*) from numbers_tbl");
    query.next();
    num_quantity = query.value(0).toInt();
    //qDebug() << "num quantity : " << num_quantity << endl;

    return;
}
