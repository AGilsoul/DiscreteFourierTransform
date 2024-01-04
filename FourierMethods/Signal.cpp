#define _USE_MATH_DEFINES

#include "Signal.h"
#include "ComplexNumber.h"
#include <math.h>
#include <stdexcept>
#include <vector>
#include <random>


using namespace std;

namespace NumericalMethods
{
	double Signal::operator()(double t)
	{
		return amplitude * cos(2 * M_PI * frequency * t + phase);
	}

	DiscreteSignal::DiscreteSignal(vector<double> time, vector<double> samples, double dt, int numSamples) : dt(dt), numSamples(numSamples)
	{
		if (numSamples <= 1) throw new invalid_argument("Number of samples must be greater than 1");
		if (dt <= 0) throw new invalid_argument("dt must be a positive real number");
		samplingFrequency = 1 / dt;
		for (int i = 1; i < numSamples; i++)
		{
			double curDt = ceil((time[i] - time[i - 1]) * 1e5) / 1e5;
			// if (curDt != dt) throw new invalid_argument("dt not consistent");
		}

		this->time = time;
		this->samples = samples;
	}

	DiscreteSignal DiscreteSignal::operator+(const DiscreteSignal& signal)
	{
		if (this->numSamples != signal.numSamples || this->dt != signal.dt) throw new invalid_argument("Signals have different sampling frequency or different number of samples");

		DiscreteSignal sumSignal(this->time, this->samples, this->dt, this->numSamples);
		for (int i = 0; i < this->numSamples; i++)
		{
			sumSignal.samples[i] += signal.samples[i];
		}
		return sumSignal;
	}

	void DiscreteSignal::operator+=(const DiscreteSignal& signal)
	{
		if (this->numSamples != signal.numSamples || this->dt != signal.numSamples) throw new invalid_argument("Signals have different sampling frequency or different number of samples");
		for (int i = 0; i < this->numSamples; i++)
		{
			this->samples[i] += signal.samples[i];
		}
	}

	vector<double> getTime(double maxTime, int numSamples)
	{
		double dt = maxTime / (numSamples - 1);
		vector<double> time(numSamples);
		for (int i = 0; i < numSamples; i++)
		{
			time[i] = dt * i;
		}
		return time;
	}

	DiscreteSignal getRandomSignal(double maxAmplitude, double maxFrequency, double maxTime, int numWaves, int numSamples)
	{
		random_device rd;
		mt19937 gen(rd());
		uniform_real_distribution<double> ampDis(0, maxAmplitude);
		uniform_real_distribution<double> freqDis(1, maxFrequency);
		uniform_real_distribution<double> phaseDis(0, 2 * M_PI);

		vector<double> time = getTime(maxTime, numSamples);
		vector<double> samples(numSamples);

		for (int i = 0; i < numWaves; i++)
		{
			double curAmp = ampDis(gen);
			double curFreq = freqDis(gen);
			double curPhase = phaseDis(gen);
			Signal curWave(curAmp, curFreq, curPhase);
			cout << "Signal " << i << ": " << curWave << endl;
			for (int t = 0; t < numSamples; t++)
			{
				samples[t] += curWave(time[t]);
			}
		}

		return DiscreteSignal(time, samples, time[1] - time[0], numSamples);
	}

	DiscreteSignal getCosineSignal(double amplitude, double frequency, double maxTime, int numSamples)
	{
		vector<double> time = getTime(maxTime, numSamples);
		vector<double> samples(numSamples);

		Signal curWave(amplitude, frequency, 0);

		for (int t = 0; t < numSamples; t++) {
			samples[t] += curWave(time[t]);
		}

		return DiscreteSignal(time, samples, time[1] - time[0], numSamples);
	}

	DiscreteSignal getSineSignal(double amplitude, double frequency, double maxTime, int numSamples)
	{
		vector<double> time = getTime(maxTime, numSamples);
		vector<double> samples(numSamples);

		Signal curWave(amplitude, frequency, 3 * M_PI / 2);

		for (int t = 0; t < numSamples; t++) {
			samples[t] += curWave(time[t]);
		}

		return DiscreteSignal(time, samples, time[1] - time[0], numSamples);
	}

}

