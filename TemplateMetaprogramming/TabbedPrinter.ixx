module;

#include "stdafx.h"


import DefaultPrinter;


export module TabbedPrinter;

export struct TabbedPrinter : DefaultPrinter
{
    void print_separator()
    {
        std::cout << "\t";
    }
};

