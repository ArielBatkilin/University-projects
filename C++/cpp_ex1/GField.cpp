//
// Created by arik1 on 02/09/2019.
//

#include <iostream>
#include "GField.h"
#include "GFNumber.h"
#include <cmath>
#include <cassert>

/**
 * constructor
 */
GField::GField() : _p(2), _l(1)
{
}
/**
 *constructor
 * @param p - char field
 */
GField::GField(long p) : _p(abs(p)), _l(1)
{
    assert(isPrime(p));
}
/**
 *
 * @param p - char field
 * @param l - degree field
 */
GField::GField(long p, long l): _p(abs(p)), _l(l)
{
    assert(isPrime(p));
    assert(l > 0);
}
/**
 * copy constructor
 * @param other
 */
GField::GField(const GField& other)
{
    _l = other.getDegree();
    _p = other.getChar();
}
/**
 *
 * @return char getter
 */
long GField::getChar() const
{
    return _p;
}
/**
 *
 * @return degree getter
 */
long GField::getDegree() const
{
    return _l;
}
/**
 *
 * @return order getter
 */
long GField::getOrder() const
{
    return std::pow(_p, _l);
}
/**
 *
 * @param p - number to check
 * @return true if prime
 */
bool GField::isPrime(long p)
{
    int i;
    long newP = abs(p);
    if (newP <= 1)
    {
        return false;
    }
    for(i = 2; i*i <= newP; ++i)
    {
        if(newP % i == 0)
        {
            return false;
        }
    }
    return true;
}
/**
 *
 * @param a first number
 * @param b second number
 * @return the gcd of them
 */
GFNumber GField::gcd(GFNumber a, GFNumber b) const
{
    if (b.getNumber() == 0)
    {
        return a;
    }
    else
    {
        return gcd(b, a % b);
    }
}
/**
 *
 * @param k number
 * @return GFNumber created
 */
GFNumber GField::createNumber(long k) const
{
    return GFNumber(k, *this);
}
/**
 * operator ovverloading
 * @param other
 * @return
 */
GField& GField::operator=(const GField &other)
{
    _p = other.getChar();
    _l = other.getDegree();
    return *this;
}
/**
 * operator ovverloading
 * @param other
 * @return
 */
bool GField::operator==(const GField &other)
{
    if (this->getOrder() == other.getOrder())
    {
        return true;
    }
    return false;
}
/**
 * operator ovverloading
 * @param other
 * @return
 */
bool GField::operator!=(const GField &other)
{
    if (this->getOrder() != other.getOrder())
    {
        return true;
    }
    return false;
}
/**
 * operator ovverloading
 * @param out
 * @param my
 * @return
 */
ostream& operator<<(ostream& out, const GField& my)
{
    out << "GF(" << my.getChar() << "**" << my.getDegree() << ")" << endl;
    return out;
}
/**
 * operator ovverloading
 * @param in
 * @param my
 * @return
 */
istream& operator>> (istream  &in, GField& my)
{
    long myP, myDeg;
    in >> myP >> myDeg;
    my = GField(myP, myDeg);
    return in;
}