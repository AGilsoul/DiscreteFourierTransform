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
    std::cout << "Hello World!\n";
    DiscreteSignal cosineSignal = getCosineSignal(1, 1, 1, 1000);
    // cout << cosineSignal << endl;
    FourierTransform transform(cosineSignal, 5);
    vector<ComplexNumber> res = transform.getFrequencySpectrum();
    printVector<ComplexNumber>(res);
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file