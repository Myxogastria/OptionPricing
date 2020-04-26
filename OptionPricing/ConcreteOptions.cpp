#include <cmath>
#include <random>
#include <algorithm>
#include "ConcreteOptions.h"

TestOption::TestOption(const ArgumentContainer& arg) {

}

double TestOption::getPrice() {
	return 3.14;
}

double EuropeanOption::getPrice() {
	double expiry = arg.getDouble("expiry");
	double r = arg.getDouble("risk_free");

	double variance = arg.getDouble("vol");
	double rootVariance = sqrt(variance);
	double itoCorrection = -0.5 * variance;

	double movedSpot = arg.getDouble("spot") * std::exp(r * expiry + itoCorrection);
	double runningSum = 0;

	unsigned long npath = static_cast<unsigned long>(arg.getDouble("npath"));

	std::random_device seed_gen;
	std::default_random_engine engine(seed_gen());
	std::normal_distribution<> ndist(0.0, 1.0);

	for (unsigned long i = 0; i < npath; i++) {
		double nrand = ndist(engine);
		runningSum += getPayoff(movedSpot * std::exp(rootVariance * ndist(engine)));
	}

	return runningSum / npath * std::exp(-r * expiry);
}

double EuropeanCallOption::getPayoff(double spot) {
	return std::max(spot - arg.getDouble("strike"), 0.0);
}

double EuropeanPutOption::getPayoff(double spot) {
	return std::max(arg.getDouble("strike") - spot, 0.0);
}

double DoubleDigitalOption::getPayoff(double spot) {
	double lower = std::min(arg.getDouble("strike1"), arg.getDouble("strike2"));
	double upper = std::max(arg.getDouble("strike1"), arg.getDouble("strike2"));
	return (spot >= lower) && (spot <= upper) ? 1 : 0;
}



