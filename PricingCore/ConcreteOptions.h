#pragma once

#include "option.h"

class TestOption : public Option {
public:
	TestOption(const ArgumentContainer& arg);
	double getPrice();
};

class EuropeanOption : public Option {
public:
	double getPrice();

protected:
	EuropeanOption(const ArgumentContainer arg) : arg(arg) {}
	virtual double getPayoff(double spot) = 0;
	virtual ~EuropeanOption() {}

	ArgumentContainer arg;
};

class EuropeanCallOption : public EuropeanOption {
public:
	EuropeanCallOption(const ArgumentContainer& arg) : 
		EuropeanOption(arg) {}
	double getPayoff(double spot);
};

class EuropeanPutOption : public EuropeanOption {
public:
	EuropeanPutOption(const ArgumentContainer& arg) : 
		EuropeanOption(arg) {}
	double getPayoff(double spot);
};

class DoubleDigitalOption : public EuropeanOption {
public:
	DoubleDigitalOption(const ArgumentContainer& arg) : 
		EuropeanOption(arg) {}
	double getPayoff(double spot);
};


