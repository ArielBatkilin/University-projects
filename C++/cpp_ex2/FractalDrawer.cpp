//
// Created by arik1 on 08/09/2019.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stack>
#include "Fractal.h"


const int ARG_NUMBER = 2;
const char* const BAD_USG_MSG = "Usage: FractalDrawer <file path>";
const char* const BAD_FILE_MSG = "Invalid input";
const int FILE_PLACE_NUM = 1;
const int ARGS_IN_TABLE = 2;
const int MIN_TYPE = 1;
const int MAX_TYPE = 3;
const int MIN_DIM = 1;



/**
 * getting a file location
 * @param argc - number of args
 * @param argv - my arguments
 * @return
 */
int main(int argc, char *argv[])
{
    // arg check
    if (argc != ARG_NUMBER)
    {
        std::cerr << BAD_USG_MSG << std::endl;
        return EXIT_FAILURE;
    }
    // file open
    std::string filePath = argv[FILE_PLACE_NUM];
    std::ifstream myStream;
    myStream.open(filePath);
    if (myStream.fail())
    {
        std::cerr << BAD_FILE_MSG << std::endl;
        return EXIT_FAILURE;
    }
    // raeding the file
    std::string line;
    std::stack<Fractal*> fractals;
    FractalFactory myFactory;
    while (std::getline(myStream, line))
    {
        // split by ','
        std::vector<std::string> parts;
        std::string part;
        std::istringstream tokenStream(line);
        while (std::getline(tokenStream, part, ','))
        {
            parts.push_back(part);
        }
        // check num of columns
        if (parts.size() != ARGS_IN_TABLE)
        {
            std::cerr << BAD_FILE_MSG << std::endl;
            return EXIT_FAILURE;
        }
        // casting string to int
        std::stringstream firstArg(parts[0]);
        std::stringstream secondArg(parts[1]);
        parts.clear();
        int argOne = 0;
        int argTwo = 0;
        firstArg >> argOne;
        secondArg >> argTwo;
        // checking arguments in line
        if (argOne < MIN_TYPE || argOne > MAX_TYPE || argTwo < MIN_DIM)
        {
            std::cerr << BAD_FILE_MSG << std::endl;
            return EXIT_FAILURE;
        }
        fractals.push(myFactory.createFractal(argOne, argTwo));
    }
    // printing the fractals
    while(!fractals.empty())
    {
        fractals.top()->draw();
        delete fractals.top();
        fractals.pop();
    }
    myStream.close();
    return 0;
};