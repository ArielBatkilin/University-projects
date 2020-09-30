/**
 * @file ex3.c
 * @author  Ariel Batkilin <ariel.batkilin@mail.huji.ac.il>
 * @version 1.0
 * @date 30/11/18
 *
 * @brief Program for comparing infix postfix and value from input
 *
 * @section LICENSE
 * This program is not a free software;
 *
 * @section DESCRIPTION
 * Program for comparing infix postfix and value from input
 * Input  : formula from user
 * Process: making an infix and postfix represntation using stacks
 * Output : printing the infix postfix and the value of the formula
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include "stack.h"


/**
 * @def MAX_INPUT 100
 * @brief maximum input length
 */
#define MAX_INPUT 100
/**
 * @def NUMBER_TYPE 0
 * @brief 0 represnts number
 */
#define NUMBER_TYPE 0
/**
 * @def OPERATOR_TYPE 1
 * @brief 1 represnts operator
 */
#define OPERATOR_TYPE 1
/**
 * @def PARENTHESIS_TYPE 2
 * @brief 2 represnts parenthesis
 */
#define PARENTHESIS_TYPE 2
/**
 * @def LEFT_PARENTHESIS '('
 * @brief left parenthesis
 */
#define LEFT_PARENTHESIS '('
/**
 * @def RIGHT_PARENTHESIS ')'
 * @brief right parenthesis
 */
#define RIGHT_PARENTHESIS ')'
/**
 * @def PLUS_OP '+'
 * @brief plus operator
 */
#define PLUS_OP '+'
/**
 * @def MINUS_OP '-'
 * @brief minus operator
 */
#define MINUS_OP '-'
/**
 * @def MUL_OP '*'
 * @brief mul operator
 */
#define MUL_OP '*'
/**
 * @def DIVIDE_OP '/'
 * @brief divide operator
 */
#define DIVIDE_OP '/'
/**
 * @def POW_OP '^'
 * @brief power operator
 */
#define POW_OP '^'
/**
 * @def BASE 10
 * @brief num represntasion in base 10
 */
#define BASE 10
/**
 * @def ERR_MSG_MEMORY "failed to allocate memory"
 * @brief if alocation of memory failed
 */
#define ERR_MSG_MEMORY "failed to allocate memory"
/**
 * @def WEAK_OP 0
 * @brief 0 represnts weakst operators
 */
#define WEAK_OP 0
/**
 * @def MEDIUM_OP 1
 * @brief 1 represnts medium operators
 */
#define MEDIUM_OP 1
/**
 * @def STRONG_OP 2
 * @brief 2 represents strong operators
 */
#define STRONG_OP 2
/**
 * @def TRUE 1
 * @brief true
 */
#define TRUE 1
/**
 * @def FALSE 0
 * @brief false
 */
#define FALSE 0
/**
 * @def ZERO_DIVISION_ERR "can't divide on zero\n"
 * @brief zero devision msg
 */
#define ZERO_DIVISION_ERR "can't divide on zero\n"


/**
 * A struct that represent an element in the infix. The struct holds the number that represent the element
 * (the number for numbers, the assci number for operators or parenthesis).
 * if type = 0 it's a number, 1 for operators, 2 for parenthesis.
 */
typedef struct Element
{
    int name;
    int type;
} Element;

/**
 * @brief - getting an array of Elemnts and printing them
 * @param array - an array of elemnts to be printed
 * @param elementNum - number of elemnts in this array
 */
void printFunc(Element array[MAX_INPUT + 1], int elementNum)
{
    for (int i = 0; i < elementNum; ++i)
    {
        if (array[i].type == NUMBER_TYPE)
        {
            printf(" %d ", array[i].name);
        }
        else
        {
            printf("%c", array[i].name);
        }
    }
    printf("\n");
}

/**
 * @brief - calc the power of an operator
 * @param operator - char that represnts operator
 * @return Int That represnts the power of this operator
 */
int whatNum(char operator)
{
    if(operator == PLUS_OP || operator == MINUS_OP)
    {
        return WEAK_OP;
    }
    else if(operator == MUL_OP || operator == DIVIDE_OP)
    {
        return MEDIUM_OP;
    }
    else
    {
        return STRONG_OP;
    }
}

/**
 * @brief - cheking if the stack is empty and that the top elemnt in the stack is not left parenthesis
 * @param stack - a stack object
 * @return if the condition is true or false
 */
int conditionCheck(Stack* stack)
{
    if (!isEmptyStack(stack))
    {
        Element myPeek;
        peek(stack, &myPeek);
        if(!((myPeek.type == PARENTHESIS_TYPE) && (myPeek.name == LEFT_PARENTHESIS)))
        {
            return TRUE;
        }
    }
    return FALSE;
}

/**
 * @brief - the func recives the infix array and from him building the postfix array
 * @param postfix - pointer to an array of Elements that we are gonna fill
 * @param infix - pointer to an array of ellements we are gonna use
 * @param numOfElements - the number of elements in infix
 * @return the number of elements in the the postfix array
 */
int infixToPostfix(Element* postfix, Element* infix, int numOfElements)
{
    Stack* myStack = stackAlloc(sizeof(Element));
    if (myStack == NULL)
    {
        fprintf(stderr, ERR_MSG_MEMORY);
    }
    int posCounter = 0;
    for (int i = 0; i < numOfElements; ++i)
    {
        Element* p = &infix[i];
        if (infix[i].type == NUMBER_TYPE)
        {
            postfix[posCounter].type = NUMBER_TYPE;
            postfix[posCounter].name = infix[i].name;
            posCounter++;
        }
        else if (infix[i].type == PARENTHESIS_TYPE)
        {
            if (infix[i].name == LEFT_PARENTHESIS)
            {
                push(myStack, &infix[i]);
            }
            else
            {
                while(conditionCheck(myStack))
                {
                    pop(myStack, &postfix[posCounter]);
                    posCounter++;
                }
                Element garbich;
                pop(myStack, &garbich);
            }
        }
        else if(infix[i].type == OPERATOR_TYPE)
        {

            if(!conditionCheck(myStack))
            {
                push(myStack, &infix[i]);
            }
            else
            {
                Element myPeek;
                peek(myStack, &myPeek);
                int myOperatorNum = whatNum(infix[i].name);
                int topOperatorNum = whatNum(myPeek.name);
                while(conditionCheck(myStack) && myOperatorNum <= topOperatorNum)
                {
                    pop(myStack, &postfix[posCounter]);
                    posCounter++;
                    if (isEmptyStack(myStack))
                    {
                        break;
                    }
                    Element myPeek;
                    peek(myStack, &myPeek);
                    topOperatorNum = whatNum(myPeek.name);
                }
                push(myStack, &infix[i]);
            }
        }
    }
    while (!isEmptyStack(myStack))
    {
        pop(myStack, &postfix[posCounter]);
        posCounter++;
    }
    freeStack(&myStack);
    myStack = NULL;
    return posCounter;
}

/**
 * @brief - calculating the value of the postfix formula
 * @param postfix - pointer of the postfix array
 * @param numOfElemnts - the number of elemnts in postfix
 * @return the value of the postfix eqation
 */
int calcPostfix(Element* postfix, int numOfElemnts)
{
    Stack* myStack = stackAlloc(sizeof(Element));
    if (myStack == NULL)
    {
        fprintf(stderr, ERR_MSG_MEMORY);
    }
    for (int i = 0; i < numOfElemnts; ++i)
    {
        if(postfix[i].type == NUMBER_TYPE)
        {
            push(myStack, &postfix[i]);
        }
        else if(postfix[i].type == OPERATOR_TYPE)
        {
            Element a, b;
            pop(myStack, &a);
            pop(myStack, &b);
            Element result;
            result.type = NUMBER_TYPE;
            if(postfix[i].name == PLUS_OP)
            {
                result.name = a.name + b.name;
            }
            else if(postfix[i].name == MINUS_OP)
            {
                result.name = b.name - a.name;
            }
            else if(postfix[i].name == MUL_OP)
            {
                result.name = a.name * b.name;
            }
            else if(postfix[i].name == DIVIDE_OP)
            {
                if(a.name == 0)
                {
                    fprintf(stderr, ZERO_DIVISION_ERR);
                    exit(EXIT_FAILURE);
                }
                result.name = b.name / a.name;
            }
            else
            {
                result.name = (int)pow(b.name, a.name);
            }
            push(myStack, &result);
        }
    }
    Element finalResult;
    pop(myStack, &finalResult);
    return finalResult.name;
}

/**
 * @brief - building an infix from the users input
 * @param infix - pointer to an array of Elements that we are gonna fill
 * @param input - the line yhe user gave us
 * @return the number of elements in the infix
 */
int infixBuild(Element* infix, char *input)
{
    int counter = 0;
    char *ptr = input;
    while(*ptr != '\0' && *ptr != '\n')
    {
        if((*ptr == LEFT_PARENTHESIS) || (*ptr == RIGHT_PARENTHESIS))
        {
            infix[counter].name = *ptr;
            infix[counter].type = PARENTHESIS_TYPE;
            counter++;
            ptr++;
        }
        else if((*ptr == PLUS_OP) || (*ptr == MINUS_OP) || (*ptr == MUL_OP) || (*ptr == DIVIDE_OP) || (*ptr == POW_OP))
        {
            infix[counter].name = *ptr;
            infix[counter].type = OPERATOR_TYPE;
            counter++;
            ptr++;
        }
        else
        {
            char* temp;
            long int result = 0;
            errno = 0;
            result = strtol(ptr, &temp, BASE);
            if(result == 0 && (errno != 0 || temp == input))
            {
                fprintf(stderr, "Error: input is not a valid\n");
                exit(EXIT_FAILURE);
            }
            int myNum = (int)result;
            ptr = temp;
            infix[counter].name = myNum;
            infix[counter].type = NUMBER_TYPE;
            counter++;
        }
    }
    return counter;
}

/**
 * @brief - gets formulas from the user, making from the infix and postfix represntations and calculating the value
 * from the postfix formula
 * @return 0 if the program finished running ok
 */
int main()
{
    char input[MAX_INPUT + 1];
    while (fgets(input, MAX_INPUT + 1, stdin) != NULL)
    {
        Element infix[MAX_INPUT + 1];
        int counter = infixBuild(infix, input);
        printf("Infix: ");
        printFunc(infix, counter);
        Element postfix[MAX_INPUT + 1];
        int posCounter = infixToPostfix(postfix, infix, counter);
        printf("Postfix: ");
        printFunc(postfix, posCounter);
        int result = calcPostfix(postfix, posCounter);
        printf("The value is %d\n", result);
    }
    return 0;
}
