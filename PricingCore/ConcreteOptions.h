#pragma once

#include "option.h"

class TestOption : public Option {
public:
	TestOption(ArgumentContainer arg);
	double getPrice();
};
