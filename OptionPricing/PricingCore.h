#pragma once

#include <map>
#include <string>
#include <iostream>

template <typename T> class Argument {
public:
	void add(const std::string& name, const T& value) {
		argumentMap.insert(std::make_pair(name, value));
		usedMap.insert(std::make_pair(name, false));
	}

	T get(const std::string& name) {
		usedMap.at(name) = true;
		return argumentMap.at(name);
	}

	bool usedAllArguments() const {
		for (auto record : usedMap)
		{
			if (!record.second) {
				return false;
			}
		}
		return true;
	}

private:
	std::map<std::string, T> argumentMap;
	std::map<std::string, bool> usedMap;
};

class ArgumentContainer {
public:
	void addDouble(const std::string& name, const double& value) {
		argDouble.add(name, value);
	}

	double getDouble(const std::string& name) {
		return argDouble.get(name);
	}

	void addString(const std::string& name, const std::string& value) {
		argString.add(name, value);
	}

	std::string getString(const std::string& name) {
		return argString.get(name);
	}

	bool usedAllArguments() const {
		return argDouble.usedAllArguments() & argString.usedAllArguments();
	}

private:
	Argument<double> argDouble;
	Argument<std::string> argString;
};


double pricing(const ArgumentContainer& arg);

class Option {
	// the subclasses must have a constructor taking const ArgumentContainer&
public:
	virtual double getPrice() = 0;
	virtual ~Option() {}
};

class OptionFactory {
public:
	typedef Option* (*CreateOptionFunction)(const ArgumentContainer&);

	static OptionFactory& getInstance();
	void registerOption(const std::string& type, const CreateOptionFunction& pfun);
	Option* createOption(ArgumentContainer arg);
	~OptionFactory() {};

private:
	std::map<std::string, CreateOptionFunction> creatorMap;
	OptionFactory() {}
	OptionFactory(const OptionFactory&) {}
	OptionFactory& operator= (const OptionFactory&) { return *this; }
};

template <class T> class OptionRegistrator {
public:
	OptionRegistrator(const std::string& type) {
		OptionFactory& factory = OptionFactory::getInstance();
		factory.registerOption(type, OptionRegistrator<T>::createOption);
	}

	static Option* createOption(const ArgumentContainer& arg) {
		return new T(arg);
	}
};


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


