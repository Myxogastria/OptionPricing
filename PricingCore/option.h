#pragma once

#include "Argument.h"

double pricing(ArgumentContainer arg);

class Option {
	// the subclasses must have a constructor taking ArgumentContainer
public:
	virtual double getPrice() = 0;
};

class OptionFactory {
public:
	typedef Option* (*CreateOptionFunction)(ArgumentContainer);

	static OptionFactory& getInstance();
	void registerOption(std::string type, CreateOptionFunction pfun);
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
	OptionRegistrator(std::string type) {
		OptionFactory& factory = OptionFactory::getInstance();
		factory.registerOption(type, OptionRegistrator<T>::createOption);
	}

	static Option* createOption(ArgumentContainer arg) {
		return new T(arg);
	}
};
