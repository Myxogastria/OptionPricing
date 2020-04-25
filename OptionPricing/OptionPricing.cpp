#include "pch.h"
#include "OptionPricing.h"

OPTIONPRICING_API double WINAPI OptionPrice(LPVARIANT argNames, LPVARIANT argValues) {
	if (!argNames) {
		MessageBox(NULL, L"argNames is NULL", L"DLL", MB_OK | MB_ICONERROR);
		return 0;
	}
	if (!argNames) {
		MessageBox(NULL, L"argValues is NULL", L"DLL", MB_OK | MB_ICONERROR);
		return 0;
	}

	IDispatch* pdispVal;
	double retval = 0.0;
	switch (argNames->vt)
	{
	case VT_DISPATCH:
		MessageBox(NULL, L"argNames->vt is VT_DISPATCH", L"DLL", MB_OK);
		pdispVal = *(argNames->ppdispVal);
		if (!pdispVal) {
			MessageBox(NULL, L"pdispVal is NULL", L"DLL", MB_OK | MB_ICONERROR);
			break;
		}
		//sizeof(ppdispVal) = sizeof(*ppdispVal) = 4
		retval = sizeof(pdispVal);
		return retval;
		break;
	default:
		break;
	}
	if (argNames->vt & VT_ARRAY) {
		MessageBox(NULL, L"argNames->vt is VT_ARRAY", L"DLL", MB_OK);
	}
	else {
		MessageBox(NULL, L"argNames->vt is not VT_ARRAY", L"DLL", MB_OK);
	}

	switch (argValues->vt)
	{
	case VT_DISPATCH:
		MessageBox(NULL, L"argValues->vt is VT_DISPATCH", L"DLL", MB_OK);
		break;
	default:
		break;
	}
	if (argValues->vt & VT_ARRAY) {
		MessageBox(NULL, L"argValues->vt is VT_ARRAY", L"DLL", MB_OK);
	}
	else {
		MessageBox(NULL, L"argValues->vt is not VT_ARRAY", L"DLL", MB_OK);
	}

	return 0.0 + argNames->vt + argValues->vt;
}