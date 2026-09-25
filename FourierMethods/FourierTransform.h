#pragma once

#include "Signal.h"
#include "ComplexNumber.h"
#include <vector>

using namespace std;

namespace NumericalMethods
{
	/*
	* FourierTransform Class
	*  - Used to perform a Fourier transform on a given discrete input signal
	*/
	class FourierTransform
	{
	public:
		/*
		* Fourier Transform Constructor
		* Params:
		*  - inputSignal:	Signal to transform
		*  - maxFreq:		Maximum frequency to evaluate in the frequency spectrum
		*  - numTerm:		If specified, maximum number of frequencies to return in the spectrum
		*/
		FourierTransform(NumericalMethods::DiscreteSignal& inputSignal, int maxFreq, int numTerms = -1);
		/*
		* Frequency Spectrum Getter
		* Returns:
		*  - vector<NumericalMethods::ComplexNumber>: the calculated frequency spectrum
		*/
		vector<NumericalMethods::ComplexNumber> getFrequencySpectrum() { return frequencySpectrum; }

	private:
		/*
		* Fourier Transform Computation
		*  - Immediately called by constructor, transforms inputSignal into the frequency spectrum
		*/
		void ComputeTransform();

		NumericalMethods::DiscreteSignal& inputSignal;
		vector<NumericalMethods::ComplexNumber> frequencySpectrum;
		int maxFreq, numTerms;
	};
}

