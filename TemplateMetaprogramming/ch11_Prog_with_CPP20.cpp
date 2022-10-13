



#include <type_traits>
#include <memory>
#include <iostream>
#include <vector>

class Keeper
{
    std::vector<int> data{ 2,3,4 };
public:
    ~Keeper()
    {
        std::cout << "dtor\n";
    }
    auto& items()  { return data; }
};

Keeper GetKeeper() { return {}; }

void Use()
{
    for (auto&& items = GetKeeper(); auto& item : items.items())
    {
        std::clog << item << "\n";
    }
}
