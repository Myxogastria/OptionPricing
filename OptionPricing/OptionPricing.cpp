#include "pch.h"
#include "OptionPricing.h"

OPTIONPRICING_API double WINAPI OptionPrice(LPSAFEARRAY* argNames, LPSAFEARRAY* argValues) {
	VARTYPE vt;
	HRESULT hResult = SafeArrayGetVartype(*argNames, &vt);

	if (FAILED(hResult)) {
		MessageBox(NULL, L"failed", L"dll", MB_OK | MB_ICONERROR);
		return 0.5;
	}
	return vt;
}