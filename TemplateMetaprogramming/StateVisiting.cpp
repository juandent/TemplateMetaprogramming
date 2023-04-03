
#include <iostream>
#include <variant>
#include <stdexcept>
#include <string>

namespace state
{

	struct Depleted {};

	struct Available
	{
		int count;
	};
	struct Discontinued {};

}


using State = std::variant<state::Depleted, state::Available, state::Discontinued>;


namespace event
{
	struct DeliveryArrived
	{
		int count;
	};

	struct Purchased
	{
		int count;
	};

	struct Discontinued {};
}




State on_event( state::Available available, event::DeliveryArrived delivery)
{
	available.count += delivery.count;
	return available;
}

State on_event( state::Available available, event::Purchased purchase)
{
	available.count -= purchase.count;
	if( available.count > 0)
	{
		return available;
	}
	return state::Depleted{};
}

template<typename S>
State on_event(S state, event::Discontinued)
{
	return state::Discontinued{};
}


State on_event(state::Depleted depleted, event::DeliveryArrived delivery)
{
	return state::Available{ delivery.count };
}

State on_event(state::Discontinued discontinued, event::DeliveryArrived delivery)
{
	return state::Available{ delivery.count };
}

template<typename ...Ts>
struct overload : Ts...
{
	using Ts::operator()...;
};

template<typename ...Ts> overload(Ts...)->overload<Ts...>;

class ItemStateMachine
{
	State  _state;
public:
	template<typename Event>
	void process_event(Event&& event)
	{
		_state = std::visit(overload{
			[&] (const auto& state) requires std::is_same_v<decltype(on_event(state, std::forward<Event>(event))), State>
			{
				return on_event(state, std::forward<Event>(event));
			},
			[&](const auto& unsupported_state)->State
			{
				//using type = decltype(on_event(unsupported_state, std::forward<Event>(event)));
			//	type* p;
				throw std::logic_error("unsupported state transition");
			}
			}, _state);
	}
	std::string report_current_state()
	{
		return std::visit(
			overload{
				[](const state::Available& state)-> std::string
				{
					return std::to_string(state.count) + " items available";
				},
				[](const state::Depleted& state) -> std::string
				{
					return "item is temporarily out of stock";
				},
				[](const state::Discontinued& state) -> std::string
				{
					return "item has been discontinued";
				} }, _state);
	}
};



void useFSM()
{
	using std::cout;
	using std::endl;
	auto fsm = ItemStateMachine{};
	cout << fsm.report_current_state() << endl;
	fsm.process_event(event::DeliveryArrived {3});
	cout << fsm.report_current_state() << endl;
	fsm.process_event(event::Purchased {2});
	cout << fsm.report_current_state() << endl;
	fsm.process_event(event::DeliveryArrived {2});
	cout << fsm.report_current_state() << endl;
	fsm.process_event(event::Purchased {3});
	cout << fsm.report_current_state() << endl;
	fsm.process_event(event::Discontinued {});
	cout << fsm.report_current_state() << endl;
	fsm.process_event(event::DeliveryArrived {1});

}
