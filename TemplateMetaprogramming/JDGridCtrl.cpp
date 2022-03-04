
#include "stdafx.h"






auto returnLocalConst()
{
	const wchar_t* p = _T("People");
	wchar_t* pp = const_cast<wchar_t*>(p);
	int a = 4;
	++a;
	//m_ti.lpszText = const_cast<wchar_t*>(p);
	return a;
}