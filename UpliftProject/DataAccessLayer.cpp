#include "DataAccessLayer.h"

using namespace std;

//you will know query failed in business tier if
//query.next() == false
QSqlQuery DBaseMan::executeQuery(QString command){
    if (!query.exec(command)) {
        qDebug("QUERY FAILED: %s", qPrintable(command));
        qDebug("\tERROR: %s\n", qPrintable(query.lastError().text()));
    }
    return query;
}
//!This is used to close the database on exit of the program.
void DBaseMan::closeDatabase() {
    db.close();
}
