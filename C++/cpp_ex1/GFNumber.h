//
// Created by arik1 on 02/09/2019.
//

#ifndef EX1_GFNUMBER_H
#define EX1_GFNUMBER_H

#include "GField.h"

/**
 * class represents number with fields
 */
class GFNumber
{
public:
    /**
     * constructor
     */
    GFNumber() : _n(0), _z(GField())
    {
    }
    /**
     * constructor
     * @param n
     */
    GFNumber(long n);
    /**
     * constructor
     * @param n
     * @param z field
     */

    GFNumber(long n, GField z);
    /**
     * copy constructor
     * @param other
     */

    GFNumber(const GFNumber &other);
    /**
     * destructor
     */

    ~GFNumber() = default;
    /**
     *
     * @return number getter
     */

    long getNumber() const;
    /**
     * field getter
     * @return
     */

    GField getField() const;
    /**
     *
     * @param len adrress to put size
     * @return the prime factors of a number
     */

    GFNumber *getPrimeFactors(int* len);
    /**
     * print the factors
     */

    void printFactors();

    /**
     *
     * @return true if number is prime
     */
    bool getIsPrime();

    /**
     * operator ovverloading
     * @param other
     * @return
     */
    GFNumber &operator=(const GFNumber &other);
    /**
     * operator ovverloading
     * @param other
     * @return
     */

    GFNumber operator+(const GFNumber &other);
    /**
     * operator ovverloading
     * @param other
     * @return
     */

    GFNumber &operator+=(const GFNumber &other);
    /**
     * operator ovverloading
     * @param other
     * @return
     */
    GFNumber operator-(const GFNumber &other);
    /**
     * operator ovverloading
     * @param other
     * @return
     */
    GFNumber &operator-=(const GFNumber &other);
    /**
     * operator ovverloading
     * @param other
     * @return
     */
    GFNumber operator*(const GFNumber &other);
    /**
     * operator ovverloading
     * @param other
     * @return
     */
    GFNumber &operator*=(const GFNumber &other);
    /**
     * operator ovverloading
     * @param other
     * @return
     */
    GFNumber operator%(const GFNumber &other);
    /**
     * operator ovverloading
     * @param other
     * @return
     */
    GFNumber &operator%=(const GFNumber &other);
    /**
     * operator ovverloading
     * @param other
     * @return
     */
    GFNumber &operator=(const long &other);
    /**
     * operator ovverloading
     * @param other
     * @return
     */
    GFNumber operator+(const long &other);
    /**
     * operator ovverloading
     * @param other
     * @return
     */
    GFNumber &operator+=(const long &other);
    /**
     * operator ovverloading
     * @param other
     * @return
     */
    GFNumber operator-(const long &other);
    /**
     * operator ovverloading
     * @param other
     * @return
     */
    GFNumber &operator-=(const long &other);
    /**
     * operator ovverloading
     * @param other
     * @return
     */
    GFNumber operator*(const long &other);
    /**
     * operator ovverloading
     * @param other
     * @return
     */
    GFNumber &operator*=(const long &other);
    /**
     * operator ovverloading
     * @param other
     * @return
     */
    GFNumber operator%(const long &other);
    /**
     * operator ovverloading
     * @param other
     * @return
     */
    GFNumber &operator%=(const long &other);
    /**
     * operator ovverloading
     * @param other
     * @return
     */
    bool operator==(const GFNumber &other);
    /**
     * operator ovverloading
     * @param other
     * @return
     */
    bool operator!=(const GFNumber &other);
    /**
     * operator ovverloading
     * @param other
     * @return
     */
    bool operator>(const GFNumber &other);
    /**
     * operator ovverloading
     * @param other
     * @return
     */
    bool operator>=(const GFNumber &other);
    /**
     * operator ovverloading
     * @param other
     * @return
     */
    bool operator<=(const GFNumber &other);
    /**
     * operator ovverloading
     * @param other
     * @return
     */
    bool operator<(const GFNumber &other);
    /**
     * operator ovverloading
     * @param other
     * @return
     */
    friend istream &operator>>(istream &in, GFNumber &c);
    /**
     * operator ovverloading
     * @param other
     * @return
     */
    friend ostream &operator<<(ostream &out, const GFNumber &c);

private:
    /**
     * my number
     */
    long _n;
    /**
     * my field
     */
    GField _z;
    /**
     *
     * @param size original size
     * @param arr array to be resized
     * @return new size
     */
    int _resize(int size, GFNumber *arr);
    /**
     *
     * @param n number to check
     * @param len place to hold yhe size of factors
     * @return factors list of n
     */
    GFNumber *_directSearchFactorization(long n, int* len);
    /**
     *
     * @param n my number
     * @param field
     * @return a prime factor of n
     */
    long _pollardRho(GFNumber n, GField field);
};


#endif //EX1_GFNUMBER_H
