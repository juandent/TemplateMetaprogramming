//********************************************************
// The following code example is taken from the book
//  C++20 - The Complete Guide
//  by Nicolai M. Josuttis (www.josuttis.com)
//  http://www.cppstd20.com
//
// The code is licensed under a
//  Creative Commons Attribution 4.0 International License
//  http://creativecommons.org/licenses/by/4.0/
//********************************************************

#include <sqlite_orm/sqlite_orm.h>

#include <iostream>
#include <string>
#include <vector>
#include <ranges>
#include <numbers>    // for math constants
#include <algorithm>  // for sort()

#if 0
void print(std::ranges::input_range auto&& coll)
{
    for (const auto& elem : coll) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}
#endif
template<typename T>
requires std::ranges::input_range<T>
void print(T&& coll)
{
    for (const auto& elem : coll) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}

struct Constant
{
    int id;
    std::string name;
    double value;
};



void elements_view()
{
    using namespace sqlite_orm;

    auto storage = make_storage("constants.sqlite",
        make_table("constants", make_column("id", &Constant::id, primary_key().autoincrement()),
            make_column("name", &Constant::name),
            make_column("value", &Constant::value)));
    storage.sync_schema();

    storage.remove_all<Constant>();

    std::vector<Constant> constants = {
        {-1, "pi", std::numbers::pi },
        {-1, "e", std::numbers::e },
        {-1, "golden-ratio", std::numbers::egamma },
        {-1, "euler-constant", std::numbers::phi } };

    storage.insert_range(constants.begin(), constants.end());

    auto vec = storage.get_all<Constant>();


    storage.remove<Constant>(vec[0].id);


    auto lines = storage.select(columns(&Constant::id, &Constant::name, &Constant::value));


    // print all elements #2 in the tuple (the Constant::values)
    print(lines | std::views::elements<2>);

    

#if 0

    std::ranges::sort(coll, std::less{},
        [](const auto& e) {return std::get<2>(e); });

    print(std::ranges::elements_view<decltype(std::views::all(coll)), 1>{coll});
    print(coll | std::views::elements<2>);
#endif
}

