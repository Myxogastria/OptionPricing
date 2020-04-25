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
