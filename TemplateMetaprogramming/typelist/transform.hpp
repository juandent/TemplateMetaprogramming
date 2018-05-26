#pragma once

#include "Typelist.hpp"
#include "IsEmpty.hpp"
#include "typelistPopFront.hpp"
#include "typelistFront.hpp"
#include "typelistPushFront.hpp"

template<typename List, template<typename T> class MetaFun, bool Empty = IsEmpty<List>::value>
class TransformT;


template<typename List, template<typename T> class MetaFun>
class TransformT<List, MetaFun, false>
	: public PushFrontT< typename TransformT<PopFront<List>, MetaFun>::Type, typename MetaFun<Front<List>>::Type>
{};

template<typename List, template<typename T> class MetaFun>
class TransformT<List, MetaFun, true>
{
public:
	using Type = List;
};

template<typename List, template<typename T> class MetaFun>
using Transform = typename TransformT<List, MetaFun>::Type;

//////   List = 'int, char, long', MF = AddConstT
// PF< T< 'char, long', MF>::Type, MF< 'int' >
// PF< T< 'long', MF>::Type, MF< 'char'>
// PF< T< '', MF>::Type, MF<'long'>
//		PF< '', 'const long'> => 'const long'
//		PF< 'long', 'const char'> => 'const char, const long'
//		PF< 'const char,const long', 'const int'> => 'const int,const char,const long'