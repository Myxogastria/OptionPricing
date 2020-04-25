#include "pch.h"
#include "OptionPricing.h"

void hTest(HRESULT h) {
	switch (h)
	{
	case S_OK:
		MessageBox(NULL, L"OK", L"hTest", MB_OK);
		break;

	case E_INVALIDARG:
		MessageBox(NULL, L"invalid arg", L"hTest", MB_OK);
		break;

	case DISP_E_BADINDEX:
		MessageBox(NULL, L"badindex", L"hTest", MB_OK);
		break;

	default:
		break;
	}
}

OPTIONPRICING_API double WINAPI OptionPriceDll(LPVARIANT argNames, LPVARIANT argValues) {
	if (!(argNames->vt & VT_ARRAY)) {
		return -1;
	}
	if (!(argValues->vt & VT_ARRAY)) {
		return -1;
	}

	UINT dim = SafeArrayGetDim(argValues->parray);

	HRESULT h;
	long lbound1;
	long ubound1;
	h = SafeArrayGetLBound(argValues->parray, 1, &lbound1);
	h = SafeArrayGetUBound(argValues->parray, 1, &ubound1);

	long lbound2;
	long ubound2;
	h = SafeArrayGetLBound(argValues->parray, 2, &lbound2);
	h = SafeArrayGetUBound(argValues->parray, 2, &ubound2);

	unsigned short vtx = argValues->vt ^ VT_ARRAY;
	long i[2] = { lbound1, lbound2 };
	VARIANT vElement;
	h = SafeArrayGetElement(argValues->parray, i, &vElement);
	hTest(h);
	return vElement.vt;
}