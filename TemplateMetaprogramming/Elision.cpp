

struct C
{
	C() :
	i{0}
	{}
	
	C(const C& other)
	: i{other.i} {}

private:
    int i;
};

C f()
{
	return C{};
}

struct D;

D g();


struct D : C {
    D() : C(f()) { }    // no elision when initializing a base-class subobject
    D(int) : D(g()) { } // no elision because the D object being initialized might
                        // be a base-class subobject of some other class
};

D g()
{
	return D{};
}



void tryElision()
{
	D d;
	D e{ 6 };
	D f{ d };
}
