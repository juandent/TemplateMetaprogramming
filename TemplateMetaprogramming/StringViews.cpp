

#include <optional>
#include <string_view>
#include <charconv>
#include <iomanip>
#include <iostream>

std::optional<int> asInt(std::string_view sv)
{
	int val;

	auto [ptr, ec] = std::from_chars(sv.data(), sv.data() + sv.size(), val);

	if (ec != std::errc{})
		return std::nullopt;
	return val;
}


std::string retString()
{
	return std::string{ "hey!" };
}

std::string_view substring(const std::string& s, std::size_t idx=0)
{
	return s.substr(idx);	// DANGER temporary dies at end of block
}

std::string substring_ext(const std::string& s, std::size_t idx = 0)
{
	return s.substr(idx);	// NOT DANGEROUS
}

class Person
{
	std::string name;
public:
	Person(const std::string& name) : name{name} {}
	std::string_view getName() const
	{
		return name;
	}
	std::string getNameStr() const
	{
		return name;
	}
};

Person createPerson(const std::string& name )
{
	return Person{ name };
}

void useStringViews()
{
	using namespace std;

	for(auto s: { "42", "  077", "hello", "0x33"})
	{
		optional<int> oi = asInt(s);
		if (oi)
			cout << "convert '" << s << "' to int: " << *oi << endl;
		else
			cout << "can't convert '" << s << "' to int" << endl;
	}


	std::string s1 = retString();
	// std::string& s2 = retString();   // initial value of reference to non-const must be an lvalue
	const std::string& s3 = retString();
	std::string&& s4 = retString();		// ok, rvalue reference to rvalue

	auto sub = substring("very nice", 4);
	cout << sub << endl;	// DANGER!!

	const string str{ "very nice" };
	auto ss = substring(str, 4);  // DANGER
	cout << ss << endl;

	auto sss = substring_ext(str, 4);	// NOT DANGEROUS
	cout << sss << endl;

	auto n = createPerson("juan").getName();	// DELETES temp string
	cout << n << endl;

	auto m = createPerson("juan").getNameStr();	// COPIES temp string
	cout << m << endl;

	// auto& q = createPerson("juan").getNameStr();	// initial value of reference to non-const must be an lvalue
	// cout << q << endl;

	const auto& q = createPerson("juan").getNameStr();	
	cout << q << endl;

	string_view sv1 = "hello"s;
	string_view sv2 = "world";
	// auto s20 = std::string(sv1) + sv2;   // not defined

	auto ssss = R"(some\value)"sv;
	cout << std::quoted(ssss) << endl;
	
}

