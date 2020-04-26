#include "ConcreteOptions.h"

namespace {
	OptionRegistrator<TestOption> registratorTest("test");
	OptionRegistrator<EuropeanCallOption> registratorEuropeanCall("call");
	OptionRegistrator<EuropeanPutOption> registratorEuropeanPut("put");
	OptionRegistrator<DoubleDigitalOption> registratorDoubleDigital("double_digital");
}