

class X
{
public:
	X(int, int);
	X(int, int, int);
};

X::X(int, int=0)
{
	
}

class D
{
	X x = 0;
};

D d1;
