#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>
#include "ComplexNumber.h"

using namespace std;

namespace NumericalMethods
{
	class Signal
	{
	public:
		Signal() {}

		Signal(double amplitude, double frequency, double phase) : amplitude(amplitude), frequency(frequency), phase(phase) {}

		double operator()(double t);

		double getAmplitude() { return amplitude; }
		double getFrequency() { return frequency; }
		double getPhase() { return phase; }

		void setAmplitude(double x) { amplitude = x; }
		void setFrequency(double x) { frequency > 0 ? frequency = x : throw new invalid_argument("Frequency must be a positive real number"); }
		void setPhase(double x) { phase = x; }


		friend ostream& operator<<(ostream& out, const Signal& signal)
		{
			out << "amp: " << signal.amplitude << " freq: " << signal.frequency << " phase: " << signal.phase;
			return out;
		}

	private:
		double amplitude = 0, frequency = 0, phase = 0;
	};


	class DiscreteSignal
	{
	public:
		DiscreteSignal(vector<double> time, vector<double> samples, double dt, int numSamples);

		vector<double> getTime() { return time; }
		vector<double> getSamples() { return samples; }
		double getDt() { return dt; }
		double getSamplingFrequency() { return samplingFrequency; }
		int getNumSamples() { return numSamples; }

		friend ostream& operator<<(ostream& out, const DiscreteSignal& signal)
		{
			out << "time:    [" << signal.time[0];
			for (int i = 1; i < signal.numSamples; i++)
			{
				out << ", " << signal.time[i];
			}
			out << "]" << endl;
			out << "samples: [" << signal.samples[0];
			for (int i = 1; i < signal.numSamples; i++)
			{
				out << ", " << signal.samples[i];
			}
			out << "]" << endl;
			return out;
		}

	private:
		vector<double> time, samples;
		double dt, samplingFrequency;
		int numSamples;
	};


	vector<double> getTime(double maxTime, int numSamples);

	DiscreteSignal getRandomSignal(double maxAmplitude, double maxFrequency, double maxTime, int numWaves, int numSamples);

	DiscreteSignal getCosineSignal(double amplitude, double frequency, double maxTime, int numSamples);

	DiscreteSignal getSineSignal(double amplitude, double frequency, double maxTime, int numSamples);
}
