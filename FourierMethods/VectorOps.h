#include <vector>
#include <iostream>
#include <iomanip>
#include "ComplexNumber.h"
#include "Signal.h"

using namespace std;

namespace NumericalMethods
{
	template<typename t>
	void printVector(vector<t> vec)
	{
		cout << "[" << vec[0] << setw(6);
		for (int i = 1; i < vec.size(); i++)
		{
			cout << ", " << vec[i] << setw(6);
		}
		cout << "]" << endl;
	}
}

