//
// Created by arik1 on 02/09/2019.
//

#ifndef EX1_GFIELD_H
#define EX1_GFIELD_H

#include <iostream>
using namespace std;

class GFNumber;

/**
 * class represent field
 */
class GField
{
public:
    /**
     * constructor
     */
    GField();
    /**
     *constructor
     * @param p - char field
     */
    GField(long p);
    /**
     *
     * @param p - char field
     * @param l - degree field
     */
    GField(long p, long l);
    /**
     * copy constructor
     * @param other
     */
    GField(const GField& other);
    /**
     *destructor
     */
    ~GField() = default;
    /**
     *
     * @return char getter
     */
    long getChar() const;
    /**
     *
     * @return degree getter
     */
    long getDegree()const;
    /**
     *
     * @return order getter
     */
    long getOrder() const;
    /**
     *
     * @param p - number to check
     * @return true if prime
     */
    static bool isPrime(long p);
    /**
     *
     * @param a first number
     * @param b second number
     * @return the gcd of them
     */
    GFNumber gcd(GFNumber a, GFNumber b) const;
    /**
     *
     * @param k number
     * @return GFNumber created
     */
    GFNumber createNumber(long k) const;
    /**
     * operator ovverloading
     * @param other
     * @return
     */
    GField& operator=(const GField& other);
    /**
     * operator ovverloading
     * @param other
     * @return
     */
    bool operator==(const GField& other);
    /**
     * operator ovverloading
     * @param other
     * @return
     */
    bool operator!=(const GField& other);
    /**
     * operator ovverloading
     * @param in
     * @param my
     * @return
     */
    friend istream & operator >> (istream &in,  GField &my);
    /**
     * operator ovverloading
     * @param out
     * @param my
     * @return
     */
    friend ostream & operator << (ostream &out, const GField &my);

private:
    long _p;
    long _l;
};


#endif //EX1_GFIELD_H
