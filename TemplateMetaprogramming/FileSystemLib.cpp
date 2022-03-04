


#include <filesystem>
#include <string>
#include <vector>
#include <iostream>

namespace fs = std::filesystem;

void useFS()
{
	fs::path p = fs::current_path();
	std::vector<std::u8string> utf8paths;
	for( const auto& entry : fs::directory_iterator(p))
	{
		utf8paths.push_back(entry.path().u8string());
	}
}

struct ignoreCaseTraits : public std::char_traits<char>
{
	 static bool eq(const char& c1, const char& c2)
	{
		return std::toupper(c1, std::locale{}) == std::toupper(c2, std::locale{});
	}
	 static bool lt(const char& c1, const char& c2)
	{
		return std::toupper(c1, std::locale{}) < std::toupper(c2, std::locale{});
	}
	 static int compare(const char* s1, const char* s2, std::size_t n)
	{
		for(auto i=0u; i < n; ++i)
		{
			if (lt(s1[i], s2[i]))
				return -1;
			if (lt(s2[i], s1[i]))
				return 1;
			if (s1[i] == 0 || s2[i] == 0)	// end loop
				break;
		}
		return 0;
	}
	static const char* find(const char* s, std::size_t n, const char& c)
	 {
		for (auto i = 0u; i < n; ++i)
		{
			if (eq(s[i], c))
				return s + i;
			if (s[i] == 0)
				break;
		}
		return nullptr;
	 }
};





using ICT = ignoreCaseTraits;
using icstring = std::basic_string<char, ICT>;


void useICT()
{
	int c1 = ICT::compare("juan", "jose", 6);
	c1 = ICT::compare("juan", "juan", 6);
	auto c2 = ICT::compare("leslie", "cristina", 8);
}


struct Basics {
	int i;
	char c;
	float f;
	double d;
	auto operator<=>(const Basics&) const = default;
};


struct Arrays {
	int ai[1];
	char ac[2];
	float af[3];
	double ad[2][2];
	auto operator<=>(const Arrays&) const = default;
};




struct Bases : Basics, Arrays {
	auto operator<=>(const Bases&) const = default;
};


void useSpaceshipOp() {
	constexpr Basics bb = { 5, 'v', 1.3f, 3.5 };
	constexpr Basics cc = { 6, 'v', 1.3f, 3.5 };
	//static_assert(bb == cc);
	static_assert(bb < cc);
	
	constexpr Bases a = { { 0, 'c', 1.f, 1. },
	{ { 1 }, { 'a', 'b' }, { 1.f, 2.f, 3.f }, { { 1., 2. }, { 3., 4. } } } };
	constexpr Bases b = { { 0, 'c', 1.f, 1. },
	{ { 1 }, { 'a', 'b' }, { 1.f, 2.f, 3.f }, { { 1., 2. }, { 3., 4. } } } };
	static_assert(a == b);
	static_assert(!(a != b));
	static_assert(!(a < b));
	static_assert(a <= b);
	static_assert(!(a > b));
	static_assert(a >= b);
}



struct Point2D {
	 int x;
	 int y;
	
};

 class Point3D {
 public:
	 int x;
	 int y;
	 int z;
	
};

 void designatedInitialization() {

	 std::cout << "\n";

	 Point2D point2D{ .x = 1, .y = 2 };
	 Point2D point2D_{ .y = 2 };
 }
