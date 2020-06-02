
class X
{
public:
	X() {}
	X(int, int);
	X(int, int, int);
};

X::X(int,int = 0, int = 0)
{

}

class D : public X
{
	X x = 0;
};

D d2;
