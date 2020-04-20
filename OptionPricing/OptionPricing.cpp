#include "pch.h"
#include "OptionPricing.h"

OPTIONPRICING_API double WINAPI OptionPrice(const LPVARIANT& argNames, const LPVARIANT& argValues) {
	MessageBox(NULL, L"OptionPrice", L"DLL", MB_OK);
	if (!argNames) {
		MessageBox(NULL, L"argNames is NULL", L"DLL", MB_OK | MB_ICONERROR);
		return 0;
	}
	if (!argValues) {
		MessageBox(NULL, L"argValues is NULL", L"DLL", MB_OK | MB_ICONERROR);
		return 0;
	}
	// with const ref, argNames->vt seems to crash on Excel
	if (argNames->vt) {
		MessageBox(NULL, L"argNames->vt is not NULL", L"DLL", MB_OK);
	}
	else {
		MessageBox(NULL, L"argNames->vt is NULL", L"DLL", MB_OK);
	}
	return 1.0;
}