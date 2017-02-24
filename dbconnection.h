#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QMessageBox>
#include <QtSql/QSqlDatabase>

static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("numbersource.db");

    if(!db.open()){
        QMessageBox::critical(0,"Cannot Open Database",
                              "Unable to establish a database connection.",
                              QMessageBox::Cancel);

        return false;
    }

    return true;
}

#endif // DBCONNECTION_H

