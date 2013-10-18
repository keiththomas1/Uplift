#include <QCoreApplication>
#include "exercise.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    cout << "Start of application." << endl << endl;

    string name = "Bench Press";
    int setCount = 3;
    int repCounts[3] = { 10, 8, 6 };
    float repWeights[3] = { 120, 130, 140 };

    Exercise e( name, setCount, repWeights, repCounts );

    e.PrintInfo();

    cout << endl << "End of application." << endl;
    return a.exec();
}
