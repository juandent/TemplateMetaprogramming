#include "stdafx.h"

 class C
 {

 public:

	 [[nodiscard]] friend bool operator== (const C&, const C&)
	 {
		 return true;
	 }
	 friend bool operator!= [[nodiscard]] (const C&, const C&)
	 {
		 return true;
	 }
	 
 };