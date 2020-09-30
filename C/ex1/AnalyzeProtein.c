/**
 * @file ex1.c
 * @author  Ariel Batkilin <ariel.batkilin@mail.huji.ac.il>
 * @version 1.0
 * @date 01/11/18
 *
 * @brief Program for calculating information about proteins
 *
 * @section LICENSE
 * This program is not a free software;
 *
 * @section DESCRIPTION
 * Program for calculating information about proteins
 * Input  : files locations that contain the information in special format
 * Process: From the files takes only the naccery information, in this case atoms
 *          and do caculations on them.
 * Output : The gravity center, the spinning radius and the largest distance.
 */



#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
/**
 * @def NUM_ARG_ERR_MSG "Usage: AnalyzeProtein <pdb1> <pdb2> ..."
 * @brief The error message that we will display if there not enough arguments
 */
#define NUM_ARG_ERR_MSG "Usage: AnalyzeProtein <pdb1> <pdb2> ..."
/**
 * @def MIN_REQUIRED  2
 * @brief The minimum of arguments required
 */
#define MIN_REQUIRED 2
/**
 * @def BAD_EXIT_CODE 1
 * @brief If an error will occure the exit code will be 1
 */
#define BAD_EXIT_CODE 1
/**
 * @def BAD_ARG_ERR_MSG "Error opening file:"
 * @brief If the file not found we will display this massege
 */
#define BAD_ARG_ERR_MSG "Error opening file:"
/**
 * @def MY_SEARCH_OBJECT "ATOM "
 * @brief the name of the object im searching for
 */
#define MY_SEARCH_OBJECT "ATOM  "
/**
 * @def X_COORDINATES_START 32
 * @brief The coulmn where x coordinates start
 */
#define X_COORDINATES_START 31
/**
 * @def X_COORDINATES_END 37
 * @brief The coulmn where x coordinates end
 */
#define X_COORDINATES_END 38
/**
 * @def Y_COORDINATES_START 40
 * @brief The coulmn where y coordinates start
 */
#define Y_COORDINATES_START 39
/**
 * @def Y_COORDINATES_END 45
 * @brief The coulmn where y coordinates end
 */
#define Y_COORDINATES_END 46
/**
 * @def Z_COORDINATES_START 48
 * @brief The coulmn where z coordinates start
 */
#define Z_COORDINATES_START 47
/**
 * @def Z_COORDINATES_END 53
 * @brief The coulmn where z coordinates end
 */
#define Z_COORDINATES_END 54
/**
 * @def MAX_ARRAY_SIZE 20000
 * @brief The max amount of atoms
 */
#define MAX_ARRAY_SIZE 20000
/**
 * @def NUMBER_OF_COORDINATES 3
 * @brief Atoms have 3 coordinates
 */
#define NUMBER_OF_COORDINATES 3
/**
 * @def LETTERS_NUM_IN_GOAL 5
 * @brief 5 leeters we check to know its an atom for sure
 */
#define LETTERS_NUM_IN_GOAL 5
/**
 * @def MAX_LINE_LEN 80
 * @brief Max length of line
 */
#define MAX_LINE_LEN 80
/**
 * @def COORDINATE_LENGTH 7
 * @brief our coordinates length
 */
#define COORDINATE_LENGTH 8
/**
 * @def MIX_LINE_LEN 60
 * @brief the maximum length of an atom line
 */
#define MIX_LINE_LEN 60

/**
 * @brief This func gets a string, destination place, start point and end point, cut
 *         the string by the start and end, and put it in the destination
 * @param str - the string we want to cut
 * @param dest - our destination place
 * @param start - the place we want to start cutting from
 * @param end  - the place we want to stop the cutting
 */
void slice_str(const char* str, char* dest, int start, int end)
{
    int j = 0;
    for (int i = start; i <= end; ++i)
    {
        dest[j++] = str[i];
    }
    dest[j] = '\0';
}

/**
 * @param input - our coordinate to check
 * @return 1 if all good
 */
int validCheck(const char *input)
{
    char *end;
    float result = 0.0;
    errno = 0;
    result = strtof(input, &end);
    if(result == 0 && (errno != 0 || end == input))
    {
        fprintf(stderr, "Error in Coordinate conversion %s!\n", end);
        exit(EXIT_FAILURE);
    }
    return 1;
}

/**
 * @brief This function recives a file and an array, and fills the array with the coordinates of the atoms
 * @param pMyFile - A pointer to my file
 * @param atatomsCoordinates - the array that i'm goona fill
 */
int fileToArray(FILE *pMyFile, float atomsCoordinates[MAX_ARRAY_SIZE][NUMBER_OF_COORDINATES])
{
    char line[MAX_LINE_LEN];
    int numOfAtom = 0;
    while (fgets(line, MAX_LINE_LEN, pMyFile) != NULL)
    {
        char myName[LETTERS_NUM_IN_GOAL - 1];
        slice_str(line, myName, 0, LETTERS_NUM_IN_GOAL);
        int isAtom = strcmp(myName, MY_SEARCH_OBJECT);
        if (isAtom != 0)
        {
            continue;
        }
//        int lineLen = (int)strlen(line);      /// it didnt worked
//        if (lineLen <= MIX_LINE_LEN)
//        {
//            fprintf(stderr, "ATOM line is too short %d characters\n", lineLen);
//            exit(EXIT_FAILURE);
//        }
        char xCoordinates[COORDINATE_LENGTH + 1];
        char yCoordinates[COORDINATE_LENGTH + 1];
        char zCoordinates[COORDINATE_LENGTH + 1];
        slice_str(line, xCoordinates, X_COORDINATES_START, X_COORDINATES_END);
        slice_str(line, yCoordinates, Y_COORDINATES_START, Y_COORDINATES_END);
        slice_str(line, zCoordinates, Z_COORDINATES_START, Z_COORDINATES_END);

        atomsCoordinates[numOfAtom][0] = strtof(xCoordinates, NULL);
        validCheck(xCoordinates);
        atomsCoordinates[numOfAtom][1] = strtof(yCoordinates, NULL);
        validCheck(yCoordinates);
        atomsCoordinates[numOfAtom][2] = strtof(zCoordinates, NULL);
        validCheck(zCoordinates);
        ++numOfAtom;
    }
    return numOfAtom;
}

/**
 *@brief calculates the gravity center of list of coordinates
 * @param atomsCoordinates  - an array with the coordinates of all the atoms
 * @param numberOfAtoms - the number of atoms
 * @param cg - Array of the 3 cooardinates, in the end of the function this array will contain the gravity center of
 *              the protein
 */
void gravityCenter(float atomsCoordinates[MAX_ARRAY_SIZE][NUMBER_OF_COORDINATES], int numberOfAtoms,
                   float cg[3])
{
    float xSum = 0.0;
    float ySum = 0.0;
    float zSum = 0.0;
    for(int i = 0; i < numberOfAtoms; ++i)
    {
        xSum += atomsCoordinates[i][0];
        ySum += atomsCoordinates[i][1];
        zSum += atomsCoordinates[i][2];
    }
    float xAvg = xSum/numberOfAtoms;
    float yAvg = ySum/numberOfAtoms;
    float zAvg = zSum/numberOfAtoms;
    cg[0] = xAvg;
    cg[1] = yAvg;
    cg[2] = zAvg;
}

/**
 * @brief - caculating the spin radius
 * @param atomsCoordinates - an array with the coordinates of all the atoms
 * @param numberOfAtoms - the number of atoms
 * @param cg - the gravity center of the protein
 * @return the spin radius
 */
float spinRadius(float atomsCoordinates[MAX_ARRAY_SIZE][NUMBER_OF_COORDINATES], int numberOfAtoms,
                 float cg[3])
{
    float sumDistPower2 = 0;
    for (int i = 0; i < numberOfAtoms ; ++i)
    {
        float distPower2 = powf((atomsCoordinates[i][0] - cg[0]), 2) + powf((atomsCoordinates[i][1] - cg[1]), 2) +
                           powf((atomsCoordinates[i][2] - cg[2]), 2);
        sumDistPower2 += distPower2;
    }
    float avgSum = sumDistPower2/numberOfAtoms;
    float rg = sqrtf(avgSum);
    return rg;
}

/**
 * @brief - caculating the largest distance between atoms
 * @param atomsCoordinates - an array with the coordinates of all the atoms
 * @param numberOfAtoms  - the number of atoms
 * @return - the max destination between atoms
 */
float maxDistAllAtoms(float atomsCoordinates[MAX_ARRAY_SIZE][NUMBER_OF_COORDINATES], int numberOfAtoms)
{
    float max=0;
    for (int i = 0; i <numberOfAtoms-1 ; ++i)
    {
        for (int j = i+1; j <numberOfAtoms ; ++j) {
            float distPow2 = powf((atomsCoordinates[i][0] - atomsCoordinates[j][0]), 2) +
                          powf((atomsCoordinates[i][1] - atomsCoordinates[j][1]), 2) +
                          powf((atomsCoordinates[i][2] - atomsCoordinates[j][2]), 2);
            float dist = sqrtf(distPow2);
            if (dist > max)
            {
                max=dist;
            }
        }
    }
    return max;
}


/**
 * @brief The main function. Reciving the arguments from the user and checking them.
 *         Puting the Atoms coordinates in array and calculating the The gravity center,
 *         the spinning radius and the largest distance. printing the information to the
 *         user. Return 0 if every thing was excuted fine.
 * @param argc - the number of arguments
 * @param argv - my arguments
 * @return 0, to tell the system the execution ended without errors.
 */
int main(int argc, char* argv[])
{
    if (argc < MIN_REQUIRED)              // number of arguments check
    {
        fprintf(stderr, NUM_ARG_ERR_MSG);
        return BAD_EXIT_CODE;
    }
    int i;
    for (i = 1; i < argc; i++)             // for each argument we will do the neccery
    {
        FILE* pMyFile = fopen(argv[i], "r");
        char* fileName = argv[i];
        if (pMyFile == NULL)              // if the file wasn't found
        {
            fprintf(stderr, BAD_ARG_ERR_MSG);
            return BAD_EXIT_CODE;
        }
        float atomsCoordinates[MAX_ARRAY_SIZE][NUMBER_OF_COORDINATES];
        int numOfAtoms;
        numOfAtoms = fileToArray(pMyFile, atomsCoordinates); // puting the neccery informatin in an array
        if (numOfAtoms == 0)
        {
            fprintf(stderr, "Error - 0 atoms were fount in the file %S\n", fileName);
        }
        float cg[3];
        gravityCenter(atomsCoordinates, numOfAtoms, cg);
        float rg;
        rg = spinRadius(atomsCoordinates, numOfAtoms, cg);
        float maxDist = 0.0;
        maxDist = maxDistAllAtoms(atomsCoordinates, numOfAtoms);
        printf("PDB file %s, %d atoms were read\n", fileName, numOfAtoms);
        printf("Cg = %.3f %.3f %.3f\n", cg[0], cg[1], cg[2]);
        printf("Rg = %.3f\n", rg);
        printf("Dmax = %.3f\n", maxDist);

        fclose(pMyFile);
    }
    return 0;
}