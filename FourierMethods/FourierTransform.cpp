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
		// Make sure we are looking at valid frequencies
		if (maxFreq < 1) throw new invalid_argument("Max frequency must be >= 1");
		// Get the number of data points in the signal
		double sampFreq = inputSignal.getNumSamples();

		// Get all data points from the signal
		vector<double> samples = inputSignal.getSamples();

		// Determine all of the frequencies to consider
		// The number of samples needs to be at least double the max frequency we are considering
		if (2.0 * maxFreq >= sampFreq)
		{
			frequencySpectrum = vector<ComplexNumber>(int(sampFreq) + 1.0);
		}
		else
		{
			frequencySpectrum = vector<ComplexNumber>(maxFreq + 1.0);
		}

		// Transform on every frequency
		for (int frequency = 0; frequency < frequencySpectrum.size(); frequency++)
		{
			// Where w is the current frequency, and n is the number of samples
			// b_n = -2pi * w / n
			double b_n = -2.0 * M_PI * frequency / sampFreq;
			cout << b_n << endl;
			// For every sample, add its contribution to the current 
			for (int sample = 0; sample < samples.size(); sample++)
			{
				// curb_n = b_n * sample index
				double curB_n = b_n * sample;
				// Real part is the sample value multiplied by cosine of curb_n
				double Re = samples[sample] * cos(curB_n);
				// Imaginary part is the sample value multiplied by sine of curb_n
				double Im = samples[sample] * sin(curB_n);
				// Convert this to a complex number
				ComplexNumber curFreq = ComplexNumber(Re, Im);
				// Add this sample's contribution to the current frequncy
				frequencySpectrum[frequency] += curFreq;
			}
			// Now multiply this frequency by 2/n
			frequencySpectrum[frequency] *= (2.0 / samples.size());
		}
	}
}

