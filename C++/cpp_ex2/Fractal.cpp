//
// Created by arik1 on 09/09/2019.
//

#include "Fractal.h"

const int SIERPINSKI_CARPET_TYPE = 1;
const int SIERPINSKI_SIEVE_TYPE = 2;
const int CANTOR_DUST_TYPE = 3;

/**
 * constructor
 */
Fractal::Fractal() : _dim(1)
{
}
/**
 * constructor
 * @param dim
 */
Fractal::Fractal(int dim) : _dim(dim)
{
}
/**
 * copy constructor
 * @param other
 */
Fractal::Fractal(const Fractal &other) : _dim(other._getDim())
{
}
/**
 * move constructor
 * @param other
 */
Fractal::Fractal(const Fractal && other) noexcept : _dim(other._getDim())
{
}
/**
 * @return get the dim
 */
int Fractal::_getDim() const
{
    return _dim;
}
/**
 * move operand=
 * @param other
 * @return
 */
Fractal& Fractal::operator=(Fractal && other) noexcept
{
    _dim = other._getDim();
    return *this;
}
/**
 * function for drawing the fractals, uses the drawHelper of each class
 */
void Fractal::draw()
{
    for (int i = 0; i < pow(myXSize(), this->_getDim()); ++i)
    {
        for (int j = 0; j < pow(myYSize(), this->_getDim()); ++j)
        {
            if (drawHelper(i, j))
            {
                std::cout << '#';
            }
            else
            {
                std::cout << ' ';
            }
        }
        std::cout << std::endl;
    }
    std:: cout << std:: endl;
}


/**
 * constructor
 */
SierpinskiCarpet::SierpinskiCarpet() : Fractal()
{
}
/**
 * constructor
 * @param dim
 */
SierpinskiCarpet::SierpinskiCarpet(int dim) : Fractal(dim)
{
}
/**
 * copy constructor
 * @param other
 */
SierpinskiCarpet::SierpinskiCarpet(const SierpinskiCarpet &other) : Fractal(other)
{
}
/**
 * move constructor
 * @param other
 */
SierpinskiCarpet::SierpinskiCarpet(const SierpinskiCarpet && other) noexcept
{
    _dim = other._getDim();
}
/**
 * move operator
 * @param other
 * @return
 */
SierpinskiCarpet& SierpinskiCarpet::operator=(SierpinskiCarpet && other) noexcept
{
    _dim = other._getDim();
    return *this;
}
/**
 * checks if we need to draw '#' or ' ' at this coordinate
 * @param x - coordinate
 * @param y - coordinate
 * @return true if '#'
 */
bool SierpinskiCarpet:: drawHelper(int x, int y)
{
    while (x > 0 || y > 0)
    {
        if (x % 3 == 1 && y % 3 == 1)
        {
            return false;
        }
        x /= 3;
        y /= 3;
    }
    return true;
}

/**
 * constructor
 */
SierpinskiSieve::SierpinskiSieve() : Fractal()
{
}
/**
 * constructor
 * @param dim
 */
SierpinskiSieve::SierpinskiSieve(int dim) : Fractal(dim)
{
}
/**
 * copy constructor
 * @param other
 */
SierpinskiSieve::SierpinskiSieve(const SierpinskiSieve &other) : Fractal(other)
{
}
/**
 * move constructor
 * @param other
 */
SierpinskiSieve::SierpinskiSieve(const SierpinskiSieve && other) noexcept
{
    _dim = other._getDim();
}
/**
 * move operand
 * @param other
 * @return
 */
SierpinskiSieve& SierpinskiSieve::operator=(SierpinskiSieve && other) noexcept
{
    _dim = other._getDim();
    return *this;
}
/**
 * checks if we need to draw '#' or ' ' at this coordinate
 * @param x - coordinate
 * @param y - coordinate
 * @return true if '#'
 */
bool SierpinskiSieve:: drawHelper(int x, int y)
{
    while (x > 0 || y > 0)
    {
        if (x % 2 == 1 && y % 2 == 1)
        {
            return false;
        }
        x /= 2;
        y /= 2;
    }
    return true;
}
/**
 * constructor
 */
CantorDust::CantorDust() : Fractal()
{
}
/**
 * constructor
 * @param dim
 */
CantorDust::CantorDust(int dim) : Fractal(dim)
{
}
/**
 * copy constructor
 * @param other
 */
CantorDust::CantorDust(const CantorDust &other) : Fractal(other)
{
}
/**
 * move constructor
 * @param other
 */
CantorDust::CantorDust(const CantorDust && other) noexcept
{
    _dim = other._getDim();
}
/**
 * move operand
 * @param other
 * @return
 */
CantorDust& CantorDust::operator=(CantorDust && other) noexcept
{
    _dim = other._getDim();
    return *this;
}
/**
 * checks if we need to draw '#' or ' ' at this coordinate
 * @param x - coordinate
 * @param y - coordinate
 * @return true if '#'
 */
bool CantorDust:: drawHelper(int x, int y)
{
    while (x > 0 || y > 0)
    {
        if ((x % 3 == 0 && y % 3 == 1) || (x % 3 == 1) || (x % 3 == 2 && y % 3 == 1))
        {
            return false;
        }
        x /= 3;
        y /= 3;
    }
    return true;
}
/**
 * constructor
 */
FractalFactory::FractalFactory()
{
}
/**
 * creating a pointer to fractal
 * @param argone - the type
 * @param argtwo - the dim
 * @return pointer to a fractal
 */
Fractal* FractalFactory::createFractal(int argOne, int argTwo)
{
    Fractal *myFractal;
    switch(argOne)
    {
        case SIERPINSKI_CARPET_TYPE:
        {
            myFractal = new SierpinskiCarpet(argTwo);
            break;
        }
        case SIERPINSKI_SIEVE_TYPE:
        {
            myFractal = new SierpinskiSieve(argTwo);
            break;
        }

        case CANTOR_DUST_TYPE:
        {
            myFractal = new CantorDust(argTwo);
            break;
        }
        default:
        {
            break;
        }
    }
    return myFractal;
}
