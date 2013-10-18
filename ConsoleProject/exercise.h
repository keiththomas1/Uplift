#ifndef EXERCISE_H
#define EXERCISE_H

#include <QObject>
#include <iostream>
using namespace std;

class Exercise : public QObject
{
    Q_OBJECT
public:
    explicit Exercise( string newName, int newSetCount, float* newRepWeights, int* newRepCounts );

    string const GetName() { return name; }
    int GetSetCount() { return setCount; }
    float* GetRepWeights() { return repWeights; }
    int* GetRepCounts() { return repCounts; }

    void SetName( string newName ) { name = newName; }
    void SetSetCount( int newSetCount ) { setCount = newSetCount; }
    void SetRepWeights( float* newRepWeights ) { repWeights = newRepWeights; }
    void SetRepCounts( int* newRepCounts ) { repCounts = newRepCounts; }

    void PrintInfo();
  
private:
    string name;
    int setCount;
    float* repWeights;
    int* repCounts;

signals:

public slots:

};

#endif // EXERCISE_H
