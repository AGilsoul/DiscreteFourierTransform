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
		if (maxFreq < 1) throw new invalid_argument("Max frequency must be >= 1");
		double sampFreq = inputSignal.getNumSamples();
		vector<double> samples = inputSignal.getSamples();

		if (2.0 * maxFreq >= sampFreq)
		{
			frequencySpectrum = vector<ComplexNumber>(int(sampFreq) + 1.0);
		}
		else
		{
			frequencySpectrum = vector<ComplexNumber>(maxFreq + 1.0);
		}

		for (int frequency = 0; frequency < frequencySpectrum.size(); frequency++)
		{
			double b_n = -2.0 * M_PI * frequency / sampFreq;
			cout << b_n << endl;
			for (int sample = 0; sample < samples.size(); sample++)
			{
				double curB_n = b_n * sample;
				double Re = samples[sample] * cos(curB_n);
				double Im = samples[sample] * sin(curB_n);
				ComplexNumber curFreq = ComplexNumber(Re, Im);
				frequencySpectrum[frequency] += curFreq;
			}
			frequencySpectrum[frequency] *= (2.0 / samples.size());
		}
	}
}

