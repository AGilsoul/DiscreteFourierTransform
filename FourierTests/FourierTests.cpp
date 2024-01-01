#include "pch.h"
#include <random>
#include <sstream>
#include <cstring>
#include "CppUnitTest.h"
#include "../FourierMethods/ComplexNumber.h"
#include "../FourierMethods/ComplexNumber.cpp"
#include "../FourierMethods/Signal.h"
#include "../FourierMethods/Signal.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using Microsoft::VisualStudio::CppUnitTestFramework::Logger;
using namespace NumericalMethods;
using namespace std;

random_device rd;
mt19937 gen(rd());
uniform_real_distribution<double> dis;

double eps = 1e-4;

enum operation
{
	sum, dif, prod, quot
};


namespace ComplexNumberTests
{
	ComplexNumber zero;
	double a1 = dis(gen);
	double a2 = dis(gen);
	double b1 = dis(gen);
	double b2 = dis(gen);

	ComplexNumber z1(a1, b1);
	ComplexNumber z2(a2, b2);

	void complexOpTest(ComplexNumber z1, ComplexNumber z2, operation op)
	{
		ComplexNumber z1Copy(z1.getRe(), z1.getIm());
		ComplexNumber complexResult;
		double resultRe, resultIm;
		switch (op)
		{
		case 0:
			complexResult = z1 + z2;
			z1Copy += z2;
			resultRe = z1.getRe() + z2.getRe();
			resultIm = z1.getIm() + z2.getIm();
			break;
		case 1:
			complexResult = z1 - z2;
			z1Copy -= z2;
			resultRe = z1.getRe() - z2.getRe();
			resultIm = z1.getIm() - z2.getIm();
			break;
		case 2:
			complexResult = z1 * z2;
			z1Copy *= z2;
			resultRe = z1.getRe() * z2.getRe() - z1.getIm() * z2.getIm();
			resultIm = z1.getRe() * z2.getIm() + z1.getIm() * z2.getRe();
			break;
		default:
			Assert::Fail();
			break;
		}
		Assert::AreEqual(complexResult.getRe(), resultRe);
		Assert::AreEqual(complexResult.getIm(), resultIm);
		Assert::AreEqual(z1Copy.getRe(), resultRe);
		Assert::AreEqual(z1Copy.getIm(), resultIm);
	}

	void complexOpTest(ComplexNumber z, double x, operation op)
	{
		ComplexNumber z1Copy(z1.getRe(), z1.getIm());
		ComplexNumber complexResult;
		double resultRe, resultIm;
		switch (op)
		{
		case 2:
			complexResult = z1 * x;
			z1Copy *= x;
			resultRe = z1.getRe() * x;
			resultIm = z1.getIm() * x;
			break;
		case 3:
			complexResult = z1 / x;
			z1Copy /= x;
			resultRe = z1.getRe() / x;
			resultIm = z1.getIm() / x;
			break;
		default:
			Assert::Fail();
			break;
		}
		Assert::AreEqual(complexResult.getRe(), resultRe);
		Assert::AreEqual(complexResult.getIm(), resultIm);
		Assert::AreEqual(z1Copy.getRe(), resultRe);
		Assert::AreEqual(z1Copy.getIm(), resultIm);
	}

	TEST_CLASS(Basic)
	{
	public:
		TEST_METHOD(Constructor)
		{
			Assert::AreEqual(zero.getRe(), 0.0);
			Assert::AreEqual(zero.getIm(), 0.0);

			double a = dis(gen);
			double b = dis(gen);
			ComplexNumber z(a, b);
			Assert::AreEqual(z.getRe(), a);
			Assert::AreEqual(z.getIm(), b);
		}

		TEST_METHOD(ZeroAddition)
		{
			complexOpTest(z1, zero, sum);
		}

		TEST_METHOD(ZeroSubtraction)
		{
			complexOpTest(z1, zero, dif);
		}

		TEST_METHOD(ZeroMultiplication)
		{
			complexOpTest(z1, zero, prod);
		}
	};
	TEST_CLASS(ComplexArithmetic)
	{
	public:
		TEST_METHOD(Addition)
		{
			complexOpTest(z1, z2, sum);
		}

		TEST_METHOD(Subtraction)
		{
			complexOpTest(z1, z2, dif);
		}

		TEST_METHOD(Multiplication)
		{
			complexOpTest(z1, z2, prod);
		}

		TEST_METHOD(Modulus)
		{
			double z1Mod = sqrt(pow(z1.getRe(), 2) + pow(z1.getIm(), 2));
			Assert::AreEqual(z1.getModulus(), z1Mod);
		}

		TEST_METHOD(PhaseAngle)
		{
			double z1Phase = atan2(z1.getIm(), z1.getRe());
			Assert::AreEqual(z1.getPhase(), z1Phase);
		}
	};
	TEST_CLASS(ScalarArithmetic)
	{
	public:
		TEST_METHOD(ScalarMultiplication)
		{
			complexOpTest(z1, dis(gen), prod);
		}

		TEST_METHOD(ScalarDivision)
		{
			complexOpTest(z1, dis(gen), quot);
		}
	};
		

	
}

namespace SignalTests
{
	Signal zeroSignal;
	Signal cosine(1, 1, 0);
	Signal sine(1, 1, M_PI * 3 / 2);
	DiscreteSignal discreteCos = getCosineSignal(1, 1, 1, 1000);
	DiscreteSignal discreteSin = getSineSignal(1, 1, 1, 1000);

	template<typename T>
	void withinThreshold(T a, T b)
	{
		Assert::IsTrue(abs(a - b) < eps);
	}

	TEST_CLASS(Basic)
	{
		TEST_METHOD(ZeroSignal)
		{
			Assert::AreEqual(zeroSignal(dis(gen)), 0.0);
		}

		TEST_METHOD(SinCosIdentity)
		{
			for (int i = 0; i < 100; i++)
			{
				double x = dis(gen);
				double sinVal = pow(sine(x), 2);
				double cosVal = pow(cosine(x), 2);
				double sum = sinVal + cosVal;
				Assert::IsTrue(abs(sum - 1) < eps);
			}
		}
	};

	TEST_CLASS(DiscreteBasic)
	{
		TEST_METHOD(VectorSize)
		{
			Assert::AreEqual(discreteCos.getSamples().size(), size_t(1000));
		}

		TEST_METHOD(SamplingTimes)
		{
			double dt = discreteCos.getDt();
			vector<double> time = discreteCos.getTime();
			Assert::AreEqual(*min_element(begin(time), end(time)), 0.0);
			Assert::AreEqual(*max_element(begin(time), end(time)), 1.0);
			for (int i = 1; i < time.size(); i++)
			{
				withinThreshold<double>(time[i] - time[i - 1], dt);
			}
		}
	};
}
