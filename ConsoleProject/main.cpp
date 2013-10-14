#include <QCoreApplication>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    cout << "Start of application." << endl;

    // Exercise( string name, int setCount, int* repCount, ? )
    //int sets = 3;
    //int repCount[3] = { 10, 8, 6 };
    // Exercise e("Bench Press", sets, repCount)

    // cout << e.getName() << endl;
    // cout << e.getSets() << endl;
    // int* reps = e.getReps();
    // cout << reps << endl;

    cout << "End of application." << endl;
    return a.exec();
}
