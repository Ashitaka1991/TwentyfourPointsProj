#include "mainwidget.h"
#include <QApplication>

#include "dbconnection.h"
#include <QSqlQuery>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //connect database
    if(!createConnection()){
        return 1;
    }



    MainWidget w;
    w.show();

    return a.exec();
}
