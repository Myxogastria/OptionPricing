#include "option.h"

double pricing(ArgumentContainer arg) {
	Option* pOption = OptionFactory::getInstance().createOption(arg);
	return pOption->getPrice();
}


OptionFactory& OptionFactory::getInstance() {
	static OptionFactory singleton;
	return singleton;
}

void OptionFactory::registerOption(std::string type, OptionFactory::CreateOptionFunction pfun) {
	creatorMap.insert(std::make_pair(type, pfun));
}

Option* OptionFactory::createOption(ArgumentContainer arg) {
	return (creatorMap.at(arg.getString("type")))(arg);
}

