#pragma once

#include "Signal.h"
#include "ComplexNumber.h"
#include <vector>

using namespace std;

namespace NumericalMethods
{
	class FourierTransform
	{
	public:
		FourierTransform(NumericalMethods::DiscreteSignal& inputSignal, int maxFreq, int numTerms = -1);
		vector<NumericalMethods::ComplexNumber> getFrequencySpectrum() { return frequencySpectrum; }

	private:
		void ComputeTransform();

		NumericalMethods::DiscreteSignal& inputSignal;
		vector<NumericalMethods::ComplexNumber> frequencySpectrum;
		int maxFreq, numTerms;
	};
}

