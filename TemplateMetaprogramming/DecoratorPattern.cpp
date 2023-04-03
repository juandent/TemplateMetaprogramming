

// common interface for Decorator and ConcreteComponent
struct Component
{
	virtual void operation() = 0;

};


struct ConcreteComponent : Component
{

	void operation() override
	{
		
	}
};


struct Decorator : Component
{
	Component* component;

	Decorator( Component* comp ) : component(comp) {}

};

struct ConcreteDecorator : Decorator
{
	void operation() override
	{
		
	}
};