#pragma once

#include <iostream>
#include <iomanip>

using std::ostream;
using std::setw;
using std::endl;

namespace NumericalMethods
{
	/**
	 * @brief Complex number class, contains a real and imaginary part
	 * 
	 */
	class ComplexNumber
	{
	public:
		ComplexNumber() {}

		ComplexNumber(double a, double b) : Re(a), Im(b) {}

		/**
		 * @brief Returns the modulus of the complex number
		 * 
		 * @return double 
		 */
		double getModulus();

		/**
		 * @brief Returns the phase of the complex number
		 * 
		 * @return double 
		 */
		double getPhase();

		/**
		 * @brief Returns the real part of the complex number
		 * 
		 * @return double 
		 */
		double getRe() { return Re; }
		/**
		 * @brief Returns the imaginary part of the complex number
		 * 
		 * @return double 
		 */
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


