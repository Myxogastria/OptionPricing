#pragma once

extern "C" {
#define OPTIONPRICING_API __declspec(dllexport)
	OPTIONPRICING_API double WINAPI OptionPrice(const LPVARIANT& argNames, const LPVARIANT& argValues);
}
