#include "DataAccessLayer.h"

using namespace std;

//you will know query failed in business tier if
//query.next() == false
///Executes queries on the database and outputs debugging info if they fail
///\param command the sql query to be executed
QSqlQuery DBaseMan::executeQuery(QString command){
    if (!query.exec(command)) {
        qDebug("QUERY FAILED: %s", qPrintable(command));
        qDebug("\tERROR: %s\n", qPrintable(query.lastError().text()));
    }
    return query;
}
///Closes the database connection
void DBaseMan::closeDatabase() {
    db.close();
}
