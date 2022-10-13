
#include <codecvt>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#define _AMD64_
#include <WinNls.h>
#include <atlstr.h>
#include <vector>
#include <xlocale>

namespace str_converting
{

	static std::string convert(const CStringW str, const int targetEncoding)
	{
		std::string result;
		const int size = WideCharToMultiByte(targetEncoding, 0U, str.GetString(), str.GetLength(), NULL, 0, NULL, NULL);
		if (size > 0)
		{
			std::vector<char> buffer(size);
			const int ret = WideCharToMultiByte(targetEncoding, 0U, str.GetString(), str.GetLength(), buffer.data(), (int)buffer.size(), NULL, NULL);
			if ((ret > 0) && (ret <= size))
			{
				result = std::string(buffer.cbegin(), buffer.cend());
			}

		}
		return result;
	}

	static CStringW convert(const std::string str, const int sourceEncoding)
	{
		CStringW result;
		const int size = MultiByteToWideChar(sourceEncoding, 0U, str.c_str(), str.length(), NULL, 0);
		if (size > 0)
		{
			std::vector<wchar_t> buffer(size);
			const int ret = MultiByteToWideChar(sourceEncoding, 0U, str.c_str(), str.length(), buffer.data(), (int)buffer.size());
			if ((ret > 0) && (ret <= size))
			{
				result = CStringW(buffer.data(), ret);
			}
		}
		return result;
	}


	void main()
	{
		std::locale loc("en-US.UTF8");
		auto ret = setlocale(LC_ALL, "en-US");
		CStringW locInfo{};
		GetLocaleInfoEx(LOCALE_NAME_SYSTEM_DEFAULT, LC_ALL, locInfo.GetBufferSetLength(100), 100);

		CStringW input(L"Mu\x00F1oz!");
		std::string res = convert(input, CP_UTF8);   // CP_ACP
		CStringW output = convert(res, CP_UTF8);

		DWORD written;
		auto cp = GetConsoleOutputCP();
		SetConsoleOutputCP(CP_UTF8);
		auto cpage = GetKBCodePage();
		WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), res.data(), res.length(), &written, NULL);
		WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), output.GetBuffer(), output.GetLength(), &written, NULL);
		std::cout.imbue(loc);
		std::cout << '"' << res << "\" " << std::endl;  // CP_UTF8
		std::wcout << output.GetBuffer() << std::endl;
	}

}


using namespace std;

class Cvt_to_upper : public codecvt<char, char, mbstate_t>
{
public:
	explicit Cvt_to_upper(size_t r = 0) : codecvt(r) {}

protected:
	// read external representation, write internal representation
	result do_in(state_type& s, const extern_type* from, const extern_type* from_end, const extern_type*& from_next,
		intern_type* to, intern_type* to_end, intern_type*& to_next) const override
	{
		while (from != from_end && to != to_end)
		{
			*to++ = toupper(*from++);
		}
		from_next = from;
		to_next = to;
		return ok;
	}

	bool   do_always_noconv() const noexcept override { return false; }
};


void useCvt()
{
	locale ulocale{ locale{}, new Cvt_to_upper };

	fstream f{ "test.txt", fstream::in | fstream::out | fstream::trunc };
	if (!f) {
		cerr << "Could not open test.txt" << endl;
		exit(1);
	}

	f.imbue(ulocale);
	f << "Make this uppercase\n";	 // will be converted to uppercase

	f.seekg(0, ios_base::beg);
	for (string s; getline(f, s);)
		cout << s << endl;



	locale olocale{ locale{}, new codecvt<char,wchar_t, mbstate_t>{} };

	wostringstream oss{};

	oss.imbue(olocale);
	oss << L"This is wide\n";


}