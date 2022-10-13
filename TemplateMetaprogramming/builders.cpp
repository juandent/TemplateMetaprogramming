

#include <chrono>
#include <optional>
#include <string>


using namespace std::chrono;

struct Item
{
	std::string name;
	std::optional<std::string> photo_url;
	std::string description;
	std::optional<float > price;
	time_point<std::chrono::system_clock> date_added{};
	bool featured;
};







template<typename ConcreteBuilder>
class GenericItemBuilder
{
protected:
	Item item;
public:
	explicit GenericItemBuilder(std::string name) : item{.name = std::move(name)} {}
	~GenericItemBuilder()
	{
		;
	}

	Item build() &&
	{
		item.date_added = system_clock::now();
		return std::move(item);
	}
	ConcreteBuilder&& with_description(std::string description) &&
	{
		item.description = description;
		return static_cast<ConcreteBuilder&&>(*this);
	}
	ConcreteBuilder&& marked_as_featured() &&
	{
		item.featured = true;
		return static_cast<ConcreteBuilder&&>(*this);
	}
	ConcreteBuilder&& with_price(float price) &&
	{
		item.price   = price;
		return static_cast<ConcreteBuilder&&>(*this);
	}

};

class ItemBuilder final : public GenericItemBuilder<ItemBuilder>
{
	using GenericItemBuilder<ItemBuilder>::GenericItemBuilder;
};


void useGenericItemBuilder()
{
	auto directly_loaded_item = ItemBuilder{ "Pot" }.with_description("A decent one").with_price(100).build();

}

