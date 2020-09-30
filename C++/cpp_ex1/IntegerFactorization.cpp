//
// Created by arik1 on 03/09/2019.
//


#include "GField.h"
#include "GFNumber.h"
#include <iostream>
#include <cassert>


/**
 * main func
 * @return 0
 */
int main()
{
    GFNumber my1, my2;
    std::cin >> my1;
    assert(!(std::
    cin.fail()));
    std::cin >> my2;
    assert(!(std::cin.fail()));

    std::cout << my1 + my2 << std::endl;
    std::cout << my1 - my2 << std::endl;
    std::cout << my2 - my1 << std::endl;
    std::cout << my1 * my2 << std::endl;

    my1.printFactors();
    my2.printFactors();

    return 0;
}