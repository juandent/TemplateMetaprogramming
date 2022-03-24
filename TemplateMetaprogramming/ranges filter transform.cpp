#include "stdafx.h"

#include <ranges>

using namespace std;

struct PhoneBookEntry
{
	string name;
	int number;
};

void printPhoneBook( auto& phoneBook)
{
	for(auto& x : phoneBook)
	{
		cout << x.name << " " << x.number << endl;
	}
}
void useFilterTransform()
{
	vector<int> numbers = { 1,2,3,4,5,6 };
	auto results = numbers | views::filter([](int n) {return n % 2 == 0; })
		| views::transform([](int n) {return n * 2; });


	vector<PhoneBookEntry> phoneBook{ {"Brown", 111}, {"Smith", 444}, {"Grimm", 666}, {"Butcher", 222}, {"Taylor", 555}, {"Wilson", 333} };
	ranges::sort(phoneBook, ranges::greater(), &PhoneBookEntry::name);
	printPhoneBook(phoneBook);
}
