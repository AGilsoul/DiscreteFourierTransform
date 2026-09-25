// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Signal.h>
#include "VectorOps.h"
#include "FourierTransform.h"
#include "ComplexNumber.h"

using namespace std;
using namespace NumericalMethods;

int main()
{
    DiscreteSignal cosineSignal = getCosineSignal(1, 1, 1, 1000);
    FourierTransform transform(cosineSignal, 5);
    vector<ComplexNumber> res = transform.getFrequencySpectrum();
    printVector<ComplexNumber>(res);
}