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

/*
void DBaseMan::testDatabase() {
    //commands
    query.exec("INSERT INTO exercise_table VALUES (99, 'squat')");
    query.exec("INSERT INTO workout_table VALUES (99, 'all pro')");
    query.exec("INSERT INTO workout_pairs VALUES ('test','test', 99)");
    query.exec("INSERT INTO user_table VALUES (99, 'user', 'pass')");
    query.exec("INSERT INTO workout_log VALUES (99, 99, NULL)");
    if (!query.exec("INSERT INTO exercise_set_log VALUES (99, 99, 99, 99, 99, 99)")) {
        qDebug() << "insert to exercise_set_log failed";
    }

    bool t1 = false, t2 = false, t3 = false, t4 = false, t5 = false, t6 = false;

    //tests
    query.exec("SELECT * from exercise_table"); query.next();
    if (query.value(0).toInt() == 99 && query.value(1).toString() == "squat")
        t1 = true;
    query.exec("SELECT * from workout_table"); query.next();
    if (query.value(0).toInt() == 99 && query.value(1).toString() == "all pro")
        t2 = true;
    query.exec("SELECT * from workout_pairs"); query.next();
    if (query.value(0).toString == "test" && query.value(1).toString() == "test" && query.value(2).toInt() == 99)
        t3 = true;
    query.exec("SELECT * from user_table"); query.next();
    if (query.value(0).toInt() == 99 && query.value(1).toString() == "user" && query.value(2).toString() == "pass")
        t4 = true;
    query.exec("SELECT * from workout_log"); query.next();
    if (query.value(0).toInt() == 99 && query.value(1).toInt() == 99)
        t5 = true;
    query.exec("SELECT * from exercise_set_log"); query.next();
    if (query.value(0).toInt() == 99 && query.value(1).toInt() == 99 && query.value(2).toInt() == 99 &&
            query.value(3).toInt() == 99 && query.value(4).toInt() == 99) {
        t6 = true;
    }

    //results
    qDebug() << "t1: " << t1;
    qDebug() << "t2: " << t2;
    qDebug() << "t3: " << t3;
    qDebug() << "t4: " << t4;
    qDebug() << "t5: " << t5;
    qDebug() << "t6: " << t6;


}
*/

//UNUSED: Database is currently managing IDs (pass NULL)
void DBaseMan::StoreIDs(int id1, int id2, int id3, int id4, int id5, int id6) {
    if (!query.exec("DELETE FROM id_table")) {
        qDebug("Deleting IDs FAILED");
        qDebug("\tERROR: %s\n", qPrintable(query.lastError().text()));
    }
    query.prepare("INSERT INTO id_table VALUES (?, ?, ?, ?, ?, ?)");
    query.addBindValue(id1);
    query.addBindValue(id2);
    query.addBindValue(id3);
    query.addBindValue(id4);
    query.addBindValue(id5);
    query.addBindValue(id6);
    if (!query.exec()) {
        qDebug("Storing IDs FAILED");
        qDebug("\tERROR: %s\n", qPrintable(query.lastError().text()));
    }
}

//!This is used to close the database on exit of the program.
void DBaseMan::closeDatabase() {
    db.close();
}
