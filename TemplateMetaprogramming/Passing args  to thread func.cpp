


#include <thread>


struct widget_id {};

struct widget_data
{
	void print(int i) {}
};

void update_data_for_widget(widget_id  w, widget_data& data) {}

void oops_again(widget_id w)
{
	widget_data data;
	std::thread t(update_data_for_widget, w, std::ref(data));


	auto x = std::ref(data);
	auto& y = x;

	std::invoke(  &widget_data::print, x.get(), 1);

	
	// display_status();
	t.join();
	// process_widget_data(data);
}
