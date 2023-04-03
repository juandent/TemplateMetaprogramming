#include <windows.h>
#include <iostream>
#include <vector>
#include <string>

static std::vector<std::wstring> locales;

BOOL __stdcall LocaleEnumProc(LPWSTR locale, [[maybe_unused]] DWORD flags, LPARAM data)
{
	const wchar_t* question = reinterpret_cast<const wchar_t*>(data);

	if (question != nullptr)
	{
		if (std::wstring(question).compare(locale) == 0)
		{
			locales.push_back(question);
			return FALSE;
		}
	}
	else
	{
		locales.push_back(locale);
	}

	return TRUE;
}

bool LocaleExists(const wchar_t* locale)
{
	locales.clear();
	const BOOL status = EnumSystemLocalesEx(
		LocaleEnumProc, LOCALE_WINDOWS, reinterpret_cast<LPARAM>(locale), nullptr);

	return (status != FALSE) && (!locales.empty());
}

namespace locale_list
{
	int main()
	{
		// Enumerate all locales on system
		EnumSystemLocalesEx(LocaleEnumProc, LOCALE_WINDOWS, 0, nullptr);

		for (const auto& ref : locales)
		{
			std::wcout << ref << std::endl;
		}

		// Check if specific locale exist on system
		if (LocaleExists(L"de-DE"))
		{
			std::wcout << L"de-DE exists" << std::endl;
		}
		else
		{
			std::wcout << L"de-DE does not exist" << std::endl;
		}

		return 0;
	}
}
