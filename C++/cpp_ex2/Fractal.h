//
// Created by arik1 on 09/09/2019.
//

#ifndef EX2_FRACTAL_H
#define EX2_FRACTAL_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stack>
#include <math.h>

/**
 * abstract class that represent a fractal
 */
class Fractal
{
public:
    /**
     * constructor
     */
    Fractal();
    /**
     * constructor
     * @param dim
     */
    explicit Fractal(int dim);
    /**
     * copy constructor
     * @param other
     */
    Fractal(const Fractal& other);
    /**
     * move constructor
     * @param other
     */
    Fractal(const Fractal && other) noexcept;
    /**
     * destructor
     */
    virtual ~Fractal() = default;
    /**
     * move operand=
     * @param other
     * @return
     */
    Fractal& operator=(Fractal && other) noexcept;
    /**
     * function for drawing the fractals, uses the drawHelper of each class
     */
    void draw();


protected:
    /**
     * dim of fractal
     */
    int _dim;
    /**
     * @return get the dim
     */
    virtual int _getDim() const;
    /**
     *
     * virtual
     */
    virtual int myXSize() const = 0;
    /**
     *
     * virtual
     */
    virtual int myYSize() const = 0;
    /**
     * virtual
     */
    virtual bool drawHelper(int x, int y) = 0;

};

/**
 * the class of Sierpinski Carpet fractal
 */
class SierpinskiCarpet : public Fractal
{
public:
    /**
     * constructor
     */
    SierpinskiCarpet();
    /**
     * constructor
     * @param dim
     */
    SierpinskiCarpet(int dim);
    /**
     * copy constructor
     * @param other
     */
    SierpinskiCarpet(const SierpinskiCarpet& other);
    /**
     * move constructor
     * @param other
     */
    SierpinskiCarpet(const SierpinskiCarpet && other) noexcept;
    /**
     * destructor
     */
    ~SierpinskiCarpet() = default;
    /**
     * move operator
     * @param other
     * @return
     */
    SierpinskiCarpet& operator=(SierpinskiCarpet && other) noexcept;

protected:
    /**
     * get basic grid size x
     * @return
     */
    int myXSize() const override
    {
        return xSize;
    }
    /**
     * get basic grid size y
     * @return
     */
    int myYSize() const override
    {
        return ySize;
    }
    /**
     * checks if we need to draw '#' or ' ' at this coordinate
     * @param x - coordinate
     * @param y - coordinate
     * @return true if '#'
     */
    bool drawHelper(int x, int y) override;


private:
    /**
     * basic grid size x
     */
    const int xSize = 3;
    /**
     * basic grid size y
     */
    const int ySize = 3;
};

/**
 * the class of Sierpinski Sieve fractal
 */
class SierpinskiSieve : public Fractal
{
public:
    /**
     * constructor
     */
    SierpinskiSieve();
    /**
     * constructor
     * @param dim
     */
    SierpinskiSieve(int dim);
    /**
     * copy constructor
     * @param other
     */
    SierpinskiSieve(const SierpinskiSieve& other);
    /**
     * move constructor
     * @param other
     */
    SierpinskiSieve(const SierpinskiSieve && other) noexcept;
    /**
     * destructor
     */
    ~SierpinskiSieve() = default;
    /**
     * move operand
     * @param other
     * @return
     */
    SierpinskiSieve& operator=(SierpinskiSieve && other) noexcept;
protected:
    /**
     * get basic grid size x
     * @return
     */
    int myXSize() const override
    {
        return xSize;
    }
    /**
     * get basic grid size y
     * @return
     */
    int myYSize() const override
    {
        return ySize;
    }
    /**
     * checks if we need to draw '#' or ' ' at this coordinate
     * @param x - coordinate
     * @param y - coordinate
     * @return true if '#'
     */
    bool drawHelper(int x, int y) override;


private:
    /**
     * basic grid size x
     */
    const int xSize = 2;
    /**
     * basic grid size y
     */
    const int ySize = 2;
};

/**
 * the class of Cantor Dust fractal
 */
class CantorDust : public Fractal
{
public:
    /**
     * constructor
     */
    CantorDust();
    /**
     * constructor
     * @param dim
     */
    CantorDust(int dim);
    /**
     * copy constructor
     * @param other
     */
    CantorDust(const CantorDust& other);
    /**
     * move constructor
     * @param other
     */
    CantorDust(const CantorDust && other) noexcept;
    /**
     * destructor
     */
    ~CantorDust() = default;
    /**
     * move operand
     * @param other
     * @return
     */
    CantorDust& operator=(CantorDust && other) noexcept;
protected:
    /**
     * get basic grid size x
     * @return
     */
    int myXSize() const override
    {
        return xSize;
    }
    /**
     * get basic grid size y
     * @return
     */
    int myYSize() const override
    {
        return ySize;
    }
    /**
     * checks if we need to draw '#' or ' ' at this coordinate
     * @param x - coordinate
     * @param y - coordinate
     * @return true if '#'
     */
    bool drawHelper(int x, int y) override;


private:
    /**
     * basic grid size x
     */
    const int xSize = 3;
    /**
     * basic grid size y
     */
    const int ySize = 3;
};

/**
 * a factory class for fractals
 */
class FractalFactory
{
public:
    /**
     * constructor
     */
    FractalFactory();
    /**
     * destructor
     */
    ~FractalFactory() = default;
    /**
     * creating a pointer to fractal
     * @param argone - the type
     * @param argtwo - the dim
     * @return pointer to a fractal
     */
    Fractal* createFractal(int argone, int argtwo);
};




#endif //EX2_FRACTAL_H
