#include "exercise.h"

Exercise::Exercise( string newName, int newSetCount, float* newRepWeights, int* newRepCounts )
{
    name = newName;
    setCount = newSetCount;
    repWeights = newRepWeights;
    repCounts = newRepCounts;
}

void Exercise::PrintInfo()
{
    cout << "Name: " << name << endl;
    cout << setCount << " sets." << endl;

    int i;
    for( i=0; i<setCount; i++ )
    {
        cout << repCounts[i] << " reps of ";
        cout << repWeights[i] << "lb." << endl;
    }
}
