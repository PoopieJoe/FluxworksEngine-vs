// TestGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "FluxworksEngine.h"

int main()
{
    std::cout << "Hello World!\n";
    testf();
    TestObj o;
    o.i = 1;
    std::cout << "i is " << o.i << std::endl;
    o.inc();
    std::cout << "i is " << o.i << std::endl;
}