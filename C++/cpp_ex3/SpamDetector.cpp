//
// Created by arik1 on 22/09/2019.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "HashMap.hpp"





const int ARG_NUMBER = 4;
const char* const BAD_USG_MSG = "Usage: SpamDetector <database path> <message path> <threshold>";
const char* const BAD_FILE_MSG = "Invalid input";
const int DATABASE_PLACE_NUM = 1;
const int MSG_PLACE_NUM = 2;
const int THRESHOLD_PLACE_NUM = 3;
const int ARGS_IN_TABLE = 2;
const char* const SPAM_MSG = "SPAM";
const char* const NOT_SPAM_MSG = "NOT_SPAM";






/**
 * main program that reads 2 files and a threshold
 * and prints if its spam or not
 * @param argc
 * @param argv
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
    /**
     * thershold check
     */

    if (*argv[THRESHOLD_PLACE_NUM] <= 0)
    {
        std::cerr << BAD_FILE_MSG << std::endl;
        return EXIT_FAILURE;
    }

    //file opening

    std::string dataFilePath = argv[DATABASE_PLACE_NUM];
    std::string msgFilePath = argv[MSG_PLACE_NUM];
    std::ifstream dataStream;
    std::ifstream msgStream;

    dataStream.open(dataFilePath);
    if (dataStream.fail())
    {
        std::cerr << BAD_FILE_MSG << std::endl;
        return EXIT_FAILURE;
    }

    msgStream.open(msgFilePath);
    if (msgStream.fail())
    {
        std::cerr << BAD_FILE_MSG << std::endl;
        return EXIT_FAILURE;
    }

    // hash map construction

    HashMap<std::string, int> myMap;
    std::string line1;
    while (std::getline(dataStream, line1))
    {
        std::vector<std::string> parts;
        std::string part;
        std::istringstream tokenStream(line1);
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
        std::stringstream secondArg(parts[1]);
        std::string argOne = parts[0];
        parts.clear();
        int argTwo = 0;
        secondArg >> argTwo;

        std::transform(argOne.begin(), argOne.end(), argOne.begin(),
                       [](unsigned char c){ return std::tolower(c); });
        myMap.insert(argOne, argTwo);
    }

    // msg construction
    std::string line2;
    std::vector<std::string> myText;

    while (std::getline(msgStream, line2))
    {
        std::vector<std::string> parts;
        std::string part;
        std::istringstream tokenStream(line2);
        while (std::getline(tokenStream, part, ' '))
        {
            parts.push_back(part);
        }

        for(int i = 0; i < (int)(parts.size()); i++)
        {
            std::transform(parts[i].begin(), parts[i].end(), parts[i].begin(),
                           [](unsigned char c){ return std::tolower(c); });
            myText.push_back(parts[i]);
        }
    }

    //threshold construction
    int myThershold = 0;
    std::stringstream thersholdd(argv[THRESHOLD_PLACE_NUM]);
    thersholdd >> myThershold;

    // calaculate the score
    int badScore = 0;
    for (int i = 0; i < (int)(myText.size()); i++)
    {
        for (std::pair<std::string, int> myPair : myMap)
        {
            if (myText[i].find(myPair.first) != std::string::npos)
            {
                badScore += myPair.second;
            }
        }
    }

    // ans printing
    if (badScore >= myThershold)
    {
        std::cout << SPAM_MSG << std::endl;
    }
    else
    {
        std::cout << NOT_SPAM_MSG << std::endl;
    }
    dataStream.close();
    msgStream.close();

    return 0;
};
