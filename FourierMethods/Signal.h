#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>
#include "ComplexNumber.h"

using namespace std;

namespace NumericalMethods
{
	/*
	* Signal Class
	*  - Used to store cosine functions
	*/
	class Signal
	{
	public:
		/*
		* Base constructor
		*/
		Signal() {}
		/*
		* Overloaded constructor
		* Params:
		*  - amplitude: amplitude of wave
		*  - frequency: frequency of wave
		*  - phase:		phase of wave
		*/
		Signal(double amplitude, double frequency, double phase) : amplitude(amplitude), frequency(frequency), phase(phase) {}
		/*
		* Overloaded () operator
		*  - Evaluates wave at time t
		* Params:
		*  - t:	time to evaluate at
		* Returns:
		*  - double: value of function at t
		*/
		double operator()(double t);
		/*
		* Amplitude getter
		* Returns:
		*  - double: wave amplitude
		*/
		double getAmplitude() { return amplitude; }
		/*
		* Frequency getter
		* Returns:
		*  - double: wave frequency
		*/
		double getFrequency() { return frequency; }
		/*
		* Phase getter
		* Returns:
		*  - double: wave phase
		*/
		double getPhase() { return phase; }
		/*
		* Amplitude setter
		* Params:
		*  - x: amplitude
		*/
		void setAmplitude(double x) { amplitude = x; }
		/*
		* Frequency setter
		* Params:
		*  - x: frequency
		*/
		void setFrequency(double x) { frequency > 0 ? frequency = x : throw new invalid_argument("Frequency must be a positive real number"); }
		/*
		* Phase setter
		* Params:
		*  - x: phase
		*/
		void setPhase(double x) { phase = x; }


		friend ostream& operator<<(ostream& out, const Signal& signal)
		{
			out << "amp: " << signal.amplitude << " freq: " << signal.frequency << " phase: " << signal.phase;
			return out;
		}

	private:
		double amplitude = 0, frequency = 0, phase = 0;
	};

	/*
	* DiscreteSignal Class
	*  - Used to store discrete signals
	*/
	class DiscreteSignal
	{
	public:
		/*
		* Constructor
		* Params:
		*  - time:		timesteps of all samples
		*  - samples:	values of all samples
		*  - dt:		timestep size
		*/
		DiscreteSignal(vector<double> time, vector<double> samples, double dt);
		/*
		* Time getter
		* Returns:
		*  - vector<double>:	all timesteps
		*/
		vector<double> getTime() { return time; }
		/*
		* Sample getter
		* Returns:
		*  - vector<double>:	all samples
		*/
		vector<double> getSamples() { return samples; }
		/*
		* dt getter
		* Returns:
		*  - double:	timestep size
		*/
		double getDt() { return dt; }
		/*
		* Sampling frequency getter
		* Returns:
		*  - double:	sampling frequency
		*/
		double getSamplingFrequency() { return samplingFrequency; }
		/*
		* Number samples getter
		* Returns:
		*  - int:	number samples
		*/
		int getNumSamples() { return numSamples; }

		DiscreteSignal operator+(const DiscreteSignal& signal);
		void operator+=(const DiscreteSignal& signal);

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
