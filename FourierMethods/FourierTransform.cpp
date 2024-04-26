#define _USE_MATH_DEFINES

#include "FourierTransform.h"
#include "ComplexNumber.h"
#include <exception>
#include <math.h>

using namespace std;

namespace NumericalMethods
{
	FourierTransform::FourierTransform(DiscreteSignal& inputSignal, int maxFreq, int numTerms) : inputSignal(inputSignal), maxFreq(maxFreq), numTerms(numTerms)
	{
		// Check that the max frequency is >= 1
		if (maxFreq < 1) throw new invalid_argument("Max frequency must be >= 1");
		double sampFreq = inputSignal.getNumSamples();
		vector<double> samples = inputSignal.getSamples();

		// Make sure that the frequency spectrum vector size is
		// - sampling frequency + 1 if sampling frequency is less than or equal to double the max frequency
		// - max frequency + 1 if sampling frequency is greater than double the max frequency
		if (2.0 * maxFreq >= sampFreq)
		{
			frequencySpectrum = vector<ComplexNumber>(int(sampFreq) + 1.0);
		}
		else
		{
			frequencySpectrum = vector<ComplexNumber>(maxFreq + 1.0);
		}

		// For every frequency in the spectrum
		for (int frequency = 0; frequency < frequencySpectrum.size(); frequency++)
		{
			// b_n = -2*pi*frequency / sampling frequency
			double b_n = -2.0 * M_PI * frequency / sampFreq;
			// for every sample
			for (int sample = 0; sample < samples.size(); sample++)
			{
				// b_n *= sample value
				double curB_n = b_n * sample;
				// real part from b_n
				double Re = samples[sample] * cos(curB_n);
				// imaginary part from b_n
				double Im = samples[sample] * sin(curB_n);
				// complex number from real and imaginary parts
				ComplexNumber curFreq = ComplexNumber(Re, Im);
				// update frequency spectrum
				frequencySpectrum[frequency] += curFreq;
			}
			// Average value of frequency on spectrum
			frequencySpectrum[frequency] *= (2.0 / samples.size());
		}
	}
}

