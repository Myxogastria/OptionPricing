#pragma once

#include "Argument.h"

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
