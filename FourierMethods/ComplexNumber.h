#pragma once

#include <iostream>
#include <iomanip>

using std::ostream;
using std::setw;
using std::endl;

namespace NumericalMethods
{
	class ComplexNumber
	{
	public:
		ComplexNumber() {}

		ComplexNumber(double a, double b) : Re(a), Im(b) {}

		double getModulus();

		double getPhase();

		double getRe() { return Re; }
		double getIm() { return Im; }

		void operator+=(const ComplexNumber& z);
		ComplexNumber operator+(const ComplexNumber& z);
		void operator-=(const ComplexNumber& z);
		ComplexNumber operator-(const ComplexNumber& z);
		void operator*=(const ComplexNumber& z);
		ComplexNumber operator*(const ComplexNumber& z);
		void operator*=(double x);
		ComplexNumber operator*(double x);
		void operator/=(double x);
		ComplexNumber operator/(double x);


		friend ostream& operator<<(ostream& out, const ComplexNumber z)
		{
			out << z.Re;
			if (z.Im > 0)
			{
				out << "+" << z.Im << "i";
			}
			else
			{
				out << "-" << abs(z.Im) << "i";
			}
			return out;
		}

	private:
		double Re = 0, Im = 0;
	};
}


