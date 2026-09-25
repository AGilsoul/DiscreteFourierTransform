#pragma once

#include "Signal.h"
#include "ComplexNumber.h"
#include <vector>

using namespace std;

namespace NumericalMethods
{
	/**
	 * @brief Fourier transform object, performs a transformation on a discrete signal
	 * 
	 */
	class FourierTransform
	{
	public:
		/**
		 * @brief Construct a new Fourier Transform object
		 * 
		 * @param inputSignal Discrete signal to transform
		 * @param maxFreq Maximum frequency to consider
		 * @param numTerms Not currently used
		 */
		FourierTransform(NumericalMethods::DiscreteSignal& inputSignal, int maxFreq, int numTerms = -1);
		
		/**
		 * @brief Returns the transformed signal frequncy spectrum as a vector of complex numbers
		 * 
		 * @return vector<NumericalMethods::ComplexNumber> 
		 */
		vector<NumericalMethods::ComplexNumber> getFrequencySpectrum() { return frequencySpectrum; }

	private:
		NumericalMethods::DiscreteSignal& inputSignal;
		vector<NumericalMethods::ComplexNumber> frequencySpectrum;
		int maxFreq, numTerms;
	};
}

