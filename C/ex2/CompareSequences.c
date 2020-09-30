/**
 * @file ex2.c
 * @author  Ariel Batkilin <ariel.batkilin@mail.huji.ac.il>
 * @version 1.0
 * @date 15/11/18
 *
 * @brief Program for comparing string sequences (for later dna and rna use)
 *
 * @section LICENSE
 * This program is not a free software;
 *
 * @section DESCRIPTION
 * Program for comparing string sequences (for later DNA and RNA use)
 * Input  : files locations that contain the information in special format, and mach, mismatch and a gap score
 * Process: From the files takes only the naccery information (sequences) , buitding a 2D array from them
 *           and calculate the best score from each 2 sequences.
 * Output : The score between every 2 sequences.
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
/**
 * @def NUM_ARG_ERR_MSG "CompareSequences <path_to_sequences_file> <m> <s> <g>"
 * @brief The error message that we will display if there not enough arguments
 */
#define NUM_ARG_ERR_MSG "CompareSequences <path_to_sequences_file> <m> <s> <g>"
/**
 * @def  ARGS_REQUIRED 5
 * @brief The number of required arguments
 */
#define ARGS_REQUIRED 5
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
 * @def FILE_ARG 1
 * @brief the file place in argv
 */
#define FILE_ARG 1
/**
 * @def MAX_SEQ_AMOUNT 100
 * @brief maximum amount of sequences
 */
#define MAX_SEQ_AMOUNT 100
/**
 * @def MAX_LINE_LEN 101
 * @brief Max length of line
 */
#define MAX_LINE_LEN 101
/**
 * @def HEADER_START ">"
 * @brief Each header start with ">"
 */
#define HEADER_START ">"
/**
 * @def END_LINE "\n"
 * @brief Each line ends with "\n"
 */
#define END_LINE "\n"
/**
 * @def MATCH_PLACE 2
 * @brief match place in the arv[]
 */
#define MATCH_PLACE 2
/**
 * @def MATCH_PLACE 3
 * @brief mismatch place in the arv[]
 */
#define MISMATCH_PLACE 3
/**
 * @def MATCH_PLACE 4
 * @brief gap place in the arv[]
 */
#define GAP_PLACE 4


/**
 * A struct that represent a sequence. The struct holds pointers to the sequence name and the sequence it self.
 */
typedef struct Seq
{
    char* name;
    char* myString;
} Seq;

/**
 * @brief - initialize a new sequence.
 * @param a pointer to sequence.
 * @param name - the name i want to give the sequence argument 'name'.
 * @param myString - the string i want to give to the sequence argument 'my_string'.
 */
void initSeq(Seq *a, size_t name, size_t myString)
{
    a->name = (char *)calloc(name + 1, sizeof(char));
    if(a->name == NULL)
    {
        exit(BAD_EXIT_CODE);
    }
    a->myString = (char *)calloc(myString + 1, sizeof(char));
    if(a->myString == NULL)
    {
        exit(BAD_EXIT_CODE);
    }
}

/**
 * @brief - adds a string to my sequence argument 'my_string'.
 * @param a - pointer to a sequence.
 * @param str - the str we wont to add to the 'my_string'.
 */
void insertSeq(Seq *a, const char* str)
{
    int reSize = (strlen(a->myString) + strlen(str) + 1)* sizeof(char);
    a->myString = (char*)realloc(a->myString, reSize);
    a->myString = strcat(a->myString, str);
}

/**
 * @brief - free all the sequences args.
 * @param a - the sequence we want to free (pointer).
 */
void freeSeq(Seq *a)
{
    free(a->name);
    free(a->myString);
    a->name = NULL;
    a->myString = NULL;
}

/**
 * @brief This func gets a string, destination place, start point and end point, cut
 *         the string by the start and end, and put it in the destination.
 * @param str - the string we want to cut.
 * @param dest - our destination place.
 * @param start - the place we want to start cutting from.
 * @param end  - the place we want to stop the cutting.
 */
void sliceStr(const char* str, char* dest, int start, int end)
{
    int j = 0;
    while((j + start) < end)
    {
        dest[j] = str[start + j];
        ++j;
    }
    dest[j] = '\0';
}

/**
 * @brief - the func gets a file and an empty sequences array, and filling the array from the file
 *          and returns the number of sequences it found.
 * @param pMyFile - the file i'm reading the sequences from.
 * @param seqArray - an array of pointer to sequences that we are gonna initialize.
 * @return the number of sequences.
 */
int fileToArray(FILE *pMyFile, Seq* seqArray[MAX_SEQ_AMOUNT])
{
    char line[MAX_LINE_LEN];
    int seqNum = -1;
    while (fgets(line, MAX_LINE_LEN, pMyFile) != NULL)
    {
        char *headStart = HEADER_START;
        char *end = END_LINE;
        if (strncmp(line, headStart, 1) == 0)
        {
            seqNum += 1;
            size_t nameLen = strlen(line) - 2;  // without the \n and the \0
            size_t strLeng = 1;     // for initialize
            seqArray[seqNum] = (Seq*)malloc(sizeof(Seq));
            initSeq(seqArray[seqNum], nameLen, strLeng);
            sliceStr(line, seqArray[seqNum]->name, 1, strlen(line) - 1);
            if(seqArray[seqNum]->name[strlen(seqArray[seqNum]->name) - 1] == '\r')
            {
                seqArray[seqNum]->name[strlen(seqArray[seqNum]->name) - 1] = '\0';
            }
            else
            {
                seqArray[seqNum]->name[strlen(seqArray[seqNum]->name)] = '\0';
            }
        }
        else if (strncmp(line, end, 1) == 0)
        {
            continue;
        }
        else
        {
            int garbich = 0;
            while ((line[strlen(line) - 1 - garbich] == '\r') || (line[strlen(line) - 1 - garbich] == '\n'))
            {
                garbich += 1;
            }
            char *temp = (char*)malloc((strlen(line) - garbich + 1) * sizeof(char));
            strncpy(temp, line, (size_t)(strlen(line) - garbich));
            temp[strlen(line) - garbich] = '\0';
            insertSeq(seqArray[seqNum], temp);
            free(temp);
            temp = NULL;
        }
    }
    return seqNum + 1;
}

/**
 * @brief - the func gets 2 sequences and return the score between them.
 * @param a - first sequence.
 * @param b - second sequence.
 * @param match - the match score.
 * @param mismatch - the mismatch score.
 * @param gap - the gap score.
 * @return - the score between thus two sequences.
 */
int scoreCalc(Seq *a, Seq *b, int match, int mismatch, int gap)
{
    int rows = strlen(a->myString) + 1;
    int colums = strlen(b->myString) + 1;
    int i;
    int **scoresTable = (int **)malloc(rows * sizeof(int *));
    for (i = 0; i < rows; i++)
    {
        scoresTable[i] = (int *)malloc(colums * sizeof(int));
    }
    int j, k;
    for (j = 0; j < rows; ++j)
    {
        for (k = 0; k < colums; ++k)
        {
            if(j == 0 || k == 0)
            {
                if(j == 0)
                {
                    scoresTable[0][k] = k * gap;
                }
                else
                {
                    scoresTable[j][0] = j * gap;
                }
            }
            else
            {
                int score1, score2, score3;
                if(a->myString[j-1] == b->myString[k-1])
                {
                    score1 = scoresTable[j-1][k-1] + match;
                }
                else
                {
                    score1 = scoresTable[j-1][k-1] + mismatch;
                }
                int max = score1;
                score2 = scoresTable[j-1][k] + gap;
                if(score2 > max)
                {
                    max = score2;
                }
                score3 = scoresTable[j][k-1] + gap;
                if(score3 > max)
                {
                    max = score3;
                }
                scoresTable[j][k] = max;
            }
        }
    }
    int my_score = scoresTable[rows - 1][colums - 1];
    int i1 = 0;
    for (; i1 < rows; i1++)
    {
        free(scoresTable[i1]);
        scoresTable[i1] = NULL;
    }
    free(scoresTable);
    scoresTable = NULL;
    return my_score;
}

/**
 * @brief - the main function of my program. reading the file, initialize it into an array, calculating
 *          the score between 2 different sequences and printing the results. returns 0 if every thing was OK!
 * @param argc - the number of arguments.
 * @param argv - my arguments.
 * @return 0 if every thing was ok.
 */
int main(int argc, char* argv[])
{
    if (argc != ARGS_REQUIRED)              // number of arguments check
    {
        fprintf(stderr, NUM_ARG_ERR_MSG);
        exit(BAD_EXIT_CODE);
    }
    FILE* pMyFile = fopen(argv[FILE_ARG], "r");
    if (pMyFile == NULL)              // if the file wasn't found
    {
        fprintf(stderr, BAD_ARG_ERR_MSG);
        exit(BAD_EXIT_CODE);
    }
    Seq *seqArray[MAX_SEQ_AMOUNT];
    int seqNum = fileToArray(pMyFile, seqArray);  // initialize the array of seq
    int match = atoi(argv[MATCH_PLACE]);
    int mismatch = atoi(argv[MISMATCH_PLACE]);
    int gap = atoi(argv[GAP_PLACE]);
    for (int i = 0; i < seqNum - 1; ++i)      // comparing and printing the results
    {
        for (int j = i + 1; j < seqNum; ++j)
        {
            int score = scoreCalc(seqArray[i], seqArray[j], match, mismatch, gap);
            printf("Score for alignment of %s to %s is %d\n", seqArray[i]->name, seqArray[j]->name, score);
        }
    }
    int k;
    for (k = 0; k < seqNum; ++k)     // free the seq array
    {
        freeSeq(seqArray[k]);
        free(seqArray[k]);
        seqArray[k] = NULL;
    }
    fclose(pMyFile);
}