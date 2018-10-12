#pragma once

struct Nil{};

template<typename HeadT, typename TailT=Nil>
struct Cons
{
	using Head = HeadT;
	using  Tail = TailT;
};

