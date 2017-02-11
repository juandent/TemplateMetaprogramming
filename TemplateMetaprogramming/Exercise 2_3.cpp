//
//  Exercise 2_3.cpp
//  TemplateMetaprogramming
//
//  Created by Juan Dent on 3/January/17.
//  Copyright © 2017 Juan Dent. All rights reserved.
//
#include "stdafx.h"

#include "Exercise 2_3.hpp"

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

constexpr size_t BUF_SIZE = 50;

template <typename T>
struct type_description;

template<>
struct type_description<int>
{
    operator const char*()
    {
        return "int";
    }
    static const bool isFundamental = true;
};

template<typename T>
struct type_description<T*>
{
    operator const char*()
    {
        static char buf[BUF_SIZE];
        strcpy(buf, type_description<T>());
        strcat(buf, "*");
        return buf; 
    }
};

template<typename T>
struct type_description<T const>
{
    operator const char*()
    {
        static char buf[BUF_SIZE];
        strcpy(buf, type_description<T>());
        strcat(buf, " const");
        return buf; 
    }
};



template<typename T>
struct type_description<T&>
{
    operator const char*()
    {
        static char buf[BUF_SIZE];
        strcpy(buf, type_description<T>());
        strcat(buf, "&");
        return buf; 
    }
};

/*
template<typename T>
struct type_description<T[]>
{
    operator const char*()
    {
        static char buf[BUF_SIZE];
        strcpy(buf, type_description<T>());
        strcat(buf, "[]");
        return buf; 
    }
};
*/

// handle array
template<typename T, size_t N>
struct type_description<T[N]>
{
    operator const char*()
    {
        static char buf[BUF_SIZE];
        strcpy(buf, type_description<T>());
        strcat(buf, "[");
        string s = to_string(N);
        strcat(buf, s.c_str());
        strcat(buf, "]");
        return buf; 
    }
};

/*
template<typename T, size_t N, size_t M>
struct type_description<T[N][M]>
{
    operator const char*()
    {
        static char buf[BUF_SIZE];
        strcpy(buf, type_description<T>());
        strcat(buf, "[");
        string s = to_string(N);
        strcat(buf, s.c_str());
        strcat(buf, "]");
        return buf; 
    }
};
 */
/*
template<typename T, size_t N>
struct type_description<T[][N]>
{
    operator const char*()
    {
        static char buf[BUF_SIZE];
        strcpy(buf, type_description<T[]>());
        strcat(buf, "[");
        string s = to_string(N);
        strcat(buf, s.c_str());
        strcat(buf, "]");
        return buf; 
    }
};
*/

void print( int a[3][5])
{
    //for (
}



void useType_Description()
{
    cout << type_description<int>() << endl;
    cout << type_description<int*>() << endl;
    cout << type_description<int*&>() << endl;
    cout << type_description<int[3]>() << endl;
    cout << type_description<int*[2]>() << endl;
    cout << type_description<int* const>() << endl;
    cout << type_description<const int*>() << endl;    
    cout << type_description<int[3]>() << endl;
    cout << type_description<int[4][2]>() << endl;
    cout << type_description<int[3][5]>() << endl;
    cout << type_description<int[3][5][2]>() << endl;
    
    cout << is_same<remove_extent<int[3][5]>::type, int[5]>::value << endl;
    
    //cout << sizeof(int[][4]) << " " << sizeof(int[2][4]) << endl;
    cout << is_same<int[][4], int[2][4]>::value << endl;
    
}

