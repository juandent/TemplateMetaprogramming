



template<typename D>
class B
{
public:
	// using t = typename D::T;
	void f(int i)
	{
		static_cast<D*>(this)->f(i);
	}
protected:
	int _i;
};

class D : public B<D>
{
public:
	using T = int;
	void f(int x)
	{
		_i += x;
	}
};

void fuz()
{
	D d;
	d.f(5);
	B<D>* p = new D;

	p->f(77);

	delete p;
}