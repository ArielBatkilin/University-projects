//
// Created by arik1 on 02/09/2019.
//

#include "GFNumber.h"
#include "GField.h"
#include <cassert>
#include <random>

/**
 * constructor
 * @param n
 */
GFNumber::GFNumber(long n)
:_n(n), _z(GField())
{
    if (n >= 0)
    {
        _n = n % _z.getOrder();
    }
    else
    {
        while (n < 0)
        {
            n += _z.getOrder();
        }
        _n = n;
    }
}
/**
 * constructor
 * @param n
 * @param z field
 */
GFNumber::GFNumber(long n, GField z)
:_z(z)
{
    if (n >= 0)
    {
        _n = n % _z.getOrder();
    }
    else
    {
        while (n < 0)
        {
            n += _z.getOrder();
        }
        _n = n;
    }
}
/**
 * copy constructor
 * @param other
 */
GFNumber::GFNumber(const GFNumber &other)
:_z(other._z)
{
    _n = other.getNumber();
}
/**
 *
 * @return number getter
 */
long GFNumber::getNumber() const
{
    return _n;
}
/**
 * field getter
 * @return
 */

GField GFNumber::getField() const
{
    return _z;
}
/**
 *
 * @param n my number
 * @param field
 * @return a prime factor of n
 */
long GFNumber:: _pollardRho(GFNumber n, GField field)
{
    random_device randomDevice;
    mt19937 gen(randomDevice());
    uniform_int_distribution<long> dis(1, n.getNumber() - 1);
    long x1 = dis(gen);
    GFNumber x(x1, field);
    GFNumber y(x);
    GFNumber p(1, field);
    while (p.getNumber() == 1)
    {
        x = x * x + 1;
        y = (x * x + 1) * ( x*x + 1) + 1;
        if (x >= y)
        {
            p = field.gcd(x - y, n);
        }
        else
        {
            p = field.gcd(y - x, n);
        }
    }
    if (p == n)
    {
        return -1;
    }
    return p.getNumber();
}
/**
 *
 * @param n number to check
 * @param len place to hold yhe size of factors
 * @return factors list of n
 */
GFNumber* GFNumber::_directSearchFactorization(long n, int* len)
{
    int size = 1;
    GFNumber *factors = new GFNumber[size];
    int i = 2;
    int place = 0;
    while (i * i <= n)
    {
        if (n % i == 0)
        {
            GFNumber myNum(i, this->_z);
            factors[place] = myNum;
            place++;
            if (place == size)
            {
                size = _resize(size, factors);
            }
            n = n / i;
        }
        else
        {
            i++;
        }
    }
    if (n>1)
    {
        GFNumber myN(n, this->_z);
        factors[place] = myN;
    }
    *len = size;
    return factors;
}
/**
 *
 * @param len adrress to put size
 * @return the prime factors of a number
 */
GFNumber* GFNumber::getPrimeFactors(int* len)
{

    int size = 64;
    int place = 0;
    bool flag = true;
    GFNumber myWork(_n, _z);
    GFNumber *factors = new GFNumber[size];
    if (_n<2)
    {
        *len = 0;
        return factors;
    }
    if (this->getIsPrime())
    {
        *len = 0;
        return factors;
    }
    while (myWork.getNumber() % 2 == 0 && myWork._n != 0)
    {
        GFNumber myNum(2, _z);
        factors[place] = myNum;
        place ++;
        if (place == size)
        {
            size = _resize(size, factors);
        }
        myWork._n /= 2;
    }
    while (!myWork.getIsPrime() && myWork > 1)
    {
        long stam = _pollardRho(myWork, _z);
        if (stam == -1)
        {
            flag = false;
            break;
        }
        else
        {
            GFNumber stamG(stam, _z);
            factors[place] = stamG;
            place ++;
            if (place == size)
            {
                size = _resize(size, factors);
            }
            myWork._n /= stam;
        }
    }
    if (!flag)
    {
        int lengo = 0;
        _directSearchFactorization(_n, &lengo);
        GFNumber *factors2 = new GFNumber[lengo];
        factors2 = _directSearchFactorization(_n, &lengo);
        return factors2;
    }
    if (myWork.getIsPrime())
    {
        factors[place] = myWork;
        *len = place + 1;
        return factors;
    }
    return factors;
}
/**
 * print the factors
 */
void GFNumber::printFactors()
{
    int len = 0;
    GFNumber *primeFactors = getPrimeFactors(&len);
    cout << _n << "=" ;
    if(len == 0)
    {
        cout << _n << "*1" << endl;
    }
    else
    {
        for (int i = 0; i < len - 1; ++i)
        {
            cout << primeFactors[i].getNumber() << "*";
        }
        cout << primeFactors[len - 1].getNumber() << endl;
    }
    delete[] primeFactors;
    primeFactors = nullptr;
}
/**
 *
 * @return true if number is prime
 */
bool GFNumber::getIsPrime()
{
    int i;
    if (_n <= 1)
    {
        return false;
    }
    for(i = 2; i*i <= _n; ++i)
    {
        if(this->getNumber() % i == 0)
        {
            return false;
        }
    }
    return true;
}
/**
 *
 * @param size original size
 * @param arr array to be resized
 * @return new size
 */
int GFNumber::_resize(int size, GFNumber* arr)
{
    GFNumber* resize_arr = new GFNumber[size*2];
    for(int i = 0; i < size; i++)
    {
        resize_arr[i] = arr[i];
    }
    arr = resize_arr;
    delete[] resize_arr;
    resize_arr = nullptr;
    return size*2;
}
/**
 * operator ovverloading
 * @param other
 * @return
 */
GFNumber& GFNumber::operator=(const GFNumber &other)
{
    _z = other.getField();
    _n = other.getNumber();
    return *this;
}
/**
 * operator ovverloading
 * @param other
 * @return
 */
GFNumber GFNumber::operator+(const GFNumber &other)
{
    assert(_z == other._z);
    long newN = _n + other.getNumber();
    newN = newN % _z.getOrder();
    GFNumber newGFNum(newN, _z);
    return newGFNum;
}
/**
 * operator ovverloading
 * @param other
 * @return
 */
GFNumber& GFNumber::operator+=(const GFNumber &other)
{
    assert(_z == other._z);
    _n += other.getNumber();
    _n = _n % _z.getOrder();
    return *this;
}
/**
 * operator ovverloading
 * @param other
 * @return
 */
GFNumber GFNumber::operator-(const GFNumber &other)
{
    assert(_z == other._z);
    long newN = _n-other.getNumber();
    while (newN < 0)
    {
        newN += _z.getOrder();
    }
    GFNumber newGFNum(newN, _z);
    return newGFNum;
}
/**
 * operator ovverloading
 * @param other
 * @return
 */
GFNumber& GFNumber::operator-=(const GFNumber &other)
{
    assert(_z == other._z);
    _n -= other.getNumber();
    while (_n < 0)
    {
        _n += _z.getOrder();
    }
    return *this;
}
/**
 * operator ovverloading
 * @param other
 * @return
 */
GFNumber GFNumber::operator*(const GFNumber &other)
{
    assert(_z == other._z);
    long newN = _n*other.getNumber();
    newN = newN % _z.getOrder();
    GFNumber newGFNum(newN, _z);
    return newGFNum;
}
/**
 * operator ovverloading
 * @param other
 * @return
 */
GFNumber& GFNumber::operator*=(const GFNumber &other)
{
    assert(_z == other._z);
    _n *= other.getNumber();
    _n = _n % _z.getOrder();
    return *this;
}
/**
 * operator ovverloading
 * @param other
 * @return
 */
GFNumber GFNumber::operator%(const GFNumber &other)
{
    assert(_z == other._z);
    long newN = _n % other.getNumber();
    return _z.createNumber(newN);
}
/**
 * operator ovverloading
 * @param other
 * @return
 */
GFNumber& GFNumber::operator%=(const GFNumber &other)
{
    assert(_z == other._z);
    _n %= other.getNumber();
    return *this;
}
/**
 * operator ovverloading
 * @param other
 * @return
 */
GFNumber& GFNumber::operator=(const long &other)
{
    if (other >= 0)
    {
        _n = other % _z.getOrder();
    }
    else
    {
        _n = other + _z.getOrder();
    }
    return *this;
}
/**
 * operator ovverloading
 * @param other
 * @return
 */
GFNumber GFNumber::operator+(const long &other)
{
    long newN = _n + other;
    newN = newN % _z.getOrder();
    GFNumber newGFNum(newN, _z);
    return newGFNum;
}
/**
 * operator ovverloading
 * @param other
 * @return
 */
GFNumber& GFNumber::operator+=(const long &other)
{
    _n += other;
    _n = _n % _z.getOrder();
    while (_n < 0)
    {
        _n += _z.getOrder();
    }
    return *this;
}
/**
 * operator ovverloading
 * @param other
 * @return
 */
GFNumber GFNumber::operator-(const long &other)
{
    long newN = _n-other;
    while (newN < 0)
    {
        newN += _z.getOrder();
    }
    GFNumber newGFNum(newN, _z);
    return newGFNum;
}
/**
 * operator ovverloading
 * @param other
 * @return
 */
GFNumber& GFNumber::operator-=(const long &other)
{
    _n -= other;
    while (_n < 0)
    {
        _n += _z.getOrder();
    }
    return *this;
}
/**
 * operator ovverloading
 * @param other
 * @return
 */
GFNumber GFNumber::operator*(const long &other)
{
    long newN = _n*other;
    newN = newN % _z.getOrder();
    GFNumber newGFNum(newN, _z);
    return newGFNum;
}
/**
 * operator ovverloading
 * @param other
 * @return
 */
GFNumber& GFNumber::operator*=(const long &other)
{
    _n *= other;
    _n = _n % _z.getOrder();
    return *this;
}
/**
 * operator ovverloading
 * @param other
 * @return
 */
GFNumber GFNumber::operator%(const long &other)
{
    assert(other != 0);
    long newN = _n % other;
    GFNumber newGFNum(newN, _z);
    return newGFNum;
}
/**
 * operator ovverloading
 * @param other
 * @return
 */
GFNumber& GFNumber::operator%=(const long &other)
{
    long gig = other;
    while (gig < 0)
    {
        gig += _z.getOrder();
    }
    _n %= gig;
    return *this;
}
/**
 * operator ovverloading
 * @param other
 * @return
 */
bool GFNumber::operator==(const GFNumber &other)
{
    if (_n == other._n && _z == other._z)
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
bool GFNumber::operator!=(const GFNumber &other)
{
    if (_n != other._n || _z != other._z)
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
bool GFNumber::operator>(const GFNumber &other)
{
//    assert(_z == other._z);
    return _n > other._n;
}
/**
 * operator ovverloading
 * @param other
 * @return
 */
bool GFNumber::operator>=(const GFNumber &other)
{
    assert(_z == other._z);
    return _n >= other._n;
}
/**
 * operator ovverloading
 * @param other
 * @return
 */
bool GFNumber::operator<(const GFNumber &other)
{
    assert(_z == other._z);
    return _n < other._n;
}
/**
 * operator ovverloading
 * @param other
 * @return
 */
bool GFNumber::operator<=(const GFNumber &other)
{
    assert(_z == other._z);
    return _n <= other._n;
}
/**
 * operator ovverloading
 * @param other
 * @return
 */
ostream& operator<<(ostream& out, const GFNumber& my)
{
    out << my._n << " GF(" << my._z.getChar() << "**" << my._z.getDegree() << ")" << endl;
    return out;
}
/**
 * operator ovverloading
 * @param other
 * @return
 */
istream& operator>> (istream  &in, GFNumber& my)
{
    long myN, myP, myDeg;
    in >> myN >> myP >> myDeg;
    GField myField(myP, myDeg);
    my = GFNumber(myN, myField);
    return in;
}

