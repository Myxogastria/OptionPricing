#include "pch.h"
#include "OptionPricing.h"
#include "PricingCore.h"

// https://stackoverflow.com/questions/6284524/bstr-to-stdstring-stdwstring-and-vice-versa
std::string ConvertWCSToMBS(const wchar_t* pstr, long wslen)
{
    int len = ::WideCharToMultiByte(CP_ACP, 0, pstr, wslen, NULL, 0, NULL, NULL);

    std::string dblstr(len, '\0');
    len = ::WideCharToMultiByte(CP_ACP, 0 /* no flags */,
                                pstr, wslen /* not necessary NULL-terminated */,
                                &dblstr[0], len,
                                NULL, NULL /* no default char */);

    return dblstr;
}

std::string ConvertBSTRToMBS(BSTR bstr)
{
    int wslen = ::SysStringLen(bstr);
    return ConvertWCSToMBS((wchar_t*)bstr, wslen);
}


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

	//UINT dim = SafeArrayGetDim(argNames->parray);

	HRESULT h;
	long lbound1;
	long ubound1;
	h = SafeArrayGetLBound(argNames->parray, 1, &lbound1);
	h = SafeArrayGetUBound(argNames->parray, 1, &ubound1);

	long lbound2;
	long ubound2;
	h = SafeArrayGetLBound(argNames->parray, 2, &lbound2);
	h = SafeArrayGetUBound(argNames->parray, 2, &ubound2);

	ArgumentContainer arg;
	for (long i1 = lbound1; i1 <= ubound1; i1++) {
		//for (long i2 = lbound2; i2 < ubound2; i2++) {
		for (long i2 = lbound2; i2 <= lbound2; i2++) {
			long idx[2] = { i1, i2 };
			VARIANT vName;
			h = SafeArrayGetElement(argNames->parray, idx, &vName);
			if ( (h != S_OK) || !(vName.vt & VT_BSTR) ) {
				continue;
			}

			VARIANT vValue;
			h = SafeArrayGetElement(argValues->parray, idx, &vValue);
			if (h != S_OK) {
				continue;
			}

			std::string name = ConvertBSTRToMBS(vName.bstrVal);
			
			switch (vValue.vt)
			{
			case VT_R8:
				arg.addDouble(name, vValue.dblVal);
				break;
			case VT_BSTR:
				arg.addString(name, ConvertBSTRToMBS(vValue.bstrVal));
				break;
			default:
				break;
			}

		}
	}

	return pricing(arg);
}