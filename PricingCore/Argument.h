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
