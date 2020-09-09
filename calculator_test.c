/**************************************/
/* author: Shahar maimon              */
/* date: 03.10.20                     */
/**************************************/


#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <stdio.h> /* fprintf */
#include <string.h>

#include "calculator.h"
#include "stack.h"
/* 

int main()
{
    double num1 = 0;
    double res = 0;
    char op = '\0';
    char *expression =  "2+8" ;
    status_t status = STAT_FAIL;

     status = Calculator(expression, &res);

    if(status == STAT_SUCCESS)
    {
        printf("result is %f\n", res);
    }
    else
    {
        printf("wrong input\n");
    }
    
    return 0;
} */




/* #include "calculator.h" 

int main()
{
    char expression[100] = "1+3+5";
    double res = 0;
    size_t test_number = 1;

    system("clear");
    printf("Calculator Program.\n\n"); */

 /* 
 
     printf(YELLOW"BASIC ADD\n"WHITE);
    TEST("1+2", &res, 1+2);
    TEST("3+4+5", &res, 3+4+5);
    TEST("10+20+30+40", &res, 10+20+30+40);
    printf(YELLOW"BASIC MULTIPLY\n"WHITE);
    TEST("0*5", &res, 0*5); 
    TEST("2*3*4", &res, 2*3*4);
    TEST("2*3*4*5", &res, 2*3*4*5);
    printf(YELLOW"BASIC DIVISION\n"WHITE);
    TEST("4/2", &res, 4/2); 
    TEST("2/4/6", &res, 2/4/6);
    TEST("120/4/15", &res, 120/4/15);
    TEST("120/4/15/23", &res, 120/4/15/23);
    printf(YELLOW"TWO OPERATORS\n"WHITE);
    TEST("1*4+3", &res, 1*4+3);
    TEST("1+4*3", &res, 1+4*3);
    TEST("2*3+4*5", &res, 2*3+4*5);
    TEST("5+10/5+1", &res, 5+10/5+1);
    TEST("2+18/3*1*2", &res, 2+18/3*1*2);
    TEST("5+10/5+1", &res, 5+10/5+1);
    TEST("5+10/5+1", &res, 5+10/5+1);
    TEST("6+2*2+5*3", &res, 6+2*2+5*3);
    printf(YELLOW"SUBTRACT/UNARY OPERATORS\n"WHITE);
    TEST("-1+3", &res, -1+3); 
     TEST("-1-3", &res, -1-3);
    TEST("1-3", &res, 1-3); 
    TEST("1+-3", &res, 1+-3);
    TEST("-1*3", &res, -1*3);
    TEST("-1*-3", &res, -1*-3);
    TEST("1*-3", &res, 1*-3);
    TEST("-1/3", &res, -1/3);
    TEST("-1/-3", &res, -1/-3);
    TEST("70-2", &res, 70-2);  */
/*     printf(YELLOW"THREE OPERATORS\n"WHITE);
    TEST("2*10/3*2+3*2", &res, 2*10/3*2+3*2);
    TEST("2-3*12/2+5/9.8", &res, 2-3*12/2+5/9.8);
    TEST("9/9+8", &res, 9/9+8);
    TEST("2*10/3*2+3*2", &res, 2*10/3*2+3*2);
    TEST("2*10/3*2+3*2", &res, 2*10/3*2+3*2);  */
    /* 
     TEST("2-(4*1)+(5*2)", &res, 2-(4*1)+(5*2));  
   printf(YELLOW"POWERS\n"WHITE);
    TEST("2^3", &res, pow(2, 3));
    TEST("2^0", &res, pow(2, 0));
    TEST("0^3", &res, pow(0, 3));
    TEST("-2^10", &res, pow(-2, 10));
    TEST("4.5^-3", &res, pow(4.5, -3));
    TEST("2^3^2", &res, pow(2, pow(3, 2))); 
    printf(YELLOW"POWER COMBINED\n"WHITE);
    TEST("2^3-3^2", &res, pow(2, 3) - pow(3, 2));
    TEST("-1+2^-3*4-5", &res, -1+pow(2, -3)*4-5);
    TEST("8/5^1.25/2.5", &res, 8/pow(5, 1.25)/2.5);
    TEST("8-5^2*2.5", &res, 8-pow(5,2)*2.5);
    printf(YELLOW"PARENTHESES\n"WHITE);
    TEST("(1+2)", &res, (1+2)); 
     TEST("(1+2)*3", &res, (1+2)*3);
    TEST("1/(2*5)", &res, 1/(2*5));
    TEST("10-(1+2)*3", &res, 10-(1+2)*3);
    TEST("1+(2+(3+4))*3", &res, 1+(2+(3+4))*3);
    TEST("30/(3)", &res, 30/(3));
    TEST("55*(-1*(2)-2)", &res, 55*(-1*(2)-2));
    TEST("8+2*(3*2+1+1)", &res, 8+2*(3*2+1+1));
   printf(YELLOW"SPACES\n"WHITE);
    TEST(" 1+2", &res, 1+2);
    TEST(" 2+3 ", &res, 2+3);   
    TEST(" 3 +4 ", &res, 3+4);   
    TEST(" 4+ 5 ", &res, 4+5);   
    TEST(" 5 + 6", &res, 5+6); 
    TEST("6 + 7 ", &res, 6+7); 
    printf(YELLOW"ERRORS TESTS\n"WHITE);
     TEST_ERROR("a", &res); 
    TEST_ERROR(" 1 + 2 3", &res); */
   /*  TEST_ERROR("2/0", &res); 
    TEST_ERROR("1+2+3+4+5*erez", &res);    
  

    printf("\nEnter expression to calculate: (q)uit to exit\n");
    do
    {
        char *new_line_searcher = NULL;

        if (INTERACTIVE == 1)
        {
            fgets(expression, 100, stdin);
        }
        if ((new_line_searcher = strchr(expression, '\n')) != NULL)
        {
            *new_line_searcher = '\0';
        }   
        if (strcmp(expression, "Q") != 0 && strcmp(expression, "q") != 0)
        {
            TEST_INTERACTIVE(expression, &res);
        }
        else
        {
            printf(GREEN"Thanks for visiting. See you again!\n"WHITE);
            break;
        } 
    } while (INTERACTIVE); 
    
    return 0;
}



#include <string.h> /* strchr */
#include <stdio.h>  /* printf */
#include <stdlib.h> /* system */
#include <math.h>   /* pow */

#include "calculator.h" /* forward declarations */

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define WHITE "\033[0m"

#define INTERACTIVE 0
#define TEST(expression, res, expected) (Calculator(expression, res) ==  STAT_SUCCESS && *res == (double)expected ?\
                                         printf("%2ld. %14s \t = %15f "GREEN"\tPass\n"WHITE, test_number++, expression, *res) :\
                                         printf(RED"%2ld"WHITE". %12s \t = %15f "RED"\tFail\n"WHITE, test_number++, expression, *res));\

#define TEST_ERROR(expression, res) (Calculator(expression, res) ==  STAT_FAIL ?\
                                        printf("%2ld. %12s "GREEN"\t\t\t\tERROR Returned\n"WHITE, test_number++, expression) :\
                                        printf("%2ld. %12s "RED"\t\t\t\tNOT-ERROR Returned\n"WHITE, test_number++, expression));\

#define TEST_INTERACTIVE(expression, res) (Calculator(expression, res) ==  STAT_SUCCESS ?\
                                        printf("%2ld. %12s \t = %15f "GREEN"\tSTAT_SUCCESS Returned\n"WHITE, test_number++, expression, *res) :\
                                        printf("%2ld. %12s \t = %15f "RED"\tSTAT_FAIL Returned\n"WHITE, test_number++, expression, 0.0f));\ 

double res = 0;
size_t test_number = 1;

void TestBasicAdd()
{
    printf(YELLOW"BASIC ADD\n"WHITE);
    TEST("1+2", &res, 1+2);
    TEST("3+4+5", &res, 3+4+5);
    TEST("10+20+30+40", &res, 10+20+30+40);
}

void TestBasicMultiply()
{
    printf(YELLOW"BASIC MULTIPLY\n"WHITE);
    TEST("0*5", &res, 0*5);
    TEST("2*3*4", &res, 2*3*4);
    TEST("2*3*4*5", &res, 2*3*4*5);
}

void TestBasicDivision()
{
    printf(YELLOW"BASIC DIVISION\n"WHITE);
    TEST("4/2", &res, 4/2); 
    TEST("2/4/6", &res, 2/4/6);
    TEST("120/4/15", &res, 120/4/15);
    TEST("120/4/15/23", &res, 120/4/15/23);
}

void TestTwoOperators()
{
    printf(YELLOW"TWO OPERATORS\n"WHITE);
    TEST("1*4+3", &res, 1*4+3);
    TEST("1+4*3", &res, 1+4*3);
    TEST("2*3+4*5", &res, 2*3+4*5);
    TEST("5+10/5+1", &res, 5+10/5+1);
    TEST("2+18/3*1*2", &res, 2+18/3*1*2);
    TEST("5+10/5+1", &res, 5+10/5+1);
    TEST("5+10/5+1", &res, 5+10/5+1);
    TEST("6+2*2+5*3", &res, 6+2*2+5*3);
}

void TestSubtractAndUnary()
{
    printf(YELLOW"SUBTRACT/UNARY OPERATORS\n"WHITE);
    TEST("-1+3", &res, -1+3);
    TEST("-1-3", &res, -1-3);
    TEST("1-3", &res, 1-3);
    TEST("1+-3", &res, 1+-3);
    TEST("-1*3", &res, -1*3);
    TEST("-1*-3", &res, -1*-3);
    TEST("1*-3", &res, 1*-3);
    TEST("-1/3", &res, -1/3);
    TEST("-1/-3", &res, -1/-3);
    TEST("70-2", &res, 70-2);
}

void TestThreeOperators()
{
    printf(YELLOW"THREE OPERATORS\n"WHITE);
    TEST("2*10/3*2+3*2", &res, 2*10/3*2+3*2);
    TEST("2-3*12/2+5/9.8", &res, 2-3*12/2+5/9.8);
    TEST("9/9+8", &res, 9/9+8);
    TEST("2*10/3*2+3*2", &res, 2*10/3*2+3*2);
    TEST("2*10/3*2+3*2", &res, 2*10/3*2+3*2);
    TEST("2-(4*1)+(5*2)", &res, 2-(4*1)+(5*2));
}

void TestPower()
{
    printf(YELLOW"POWER\n"WHITE);
    TEST("2^3", &res, pow(2, 3));
    TEST("2^0", &res, pow(2, 0));
    TEST("0^3", &res, pow(0, 3));
    TEST("-2^10", &res, pow(-2, 10));
    TEST("4.5^-3", &res, pow(4.5, -3));
    TEST("2^3^2", &res, pow(2, pow(3, 2)));
}

void TestPowerCombined()
{
    printf(YELLOW"POWER COMBINED\n"WHITE);
    TEST("2^3-3^2", &res, pow(2, 3) - pow(3, 2));
    TEST("-1+2^-3*4-5", &res, -1+pow(2, -3)*4-5);
    TEST("8/5^1.25/2.5", &res, 8/pow(5, 1.25)/2.5);
    TEST("8-5^2*2.5", &res, 8-pow(5,2)*2.5);
}

void TestParentheses()
{
    printf(YELLOW"PARENTHESES\n"WHITE);
    TEST("(1+2)", &res, (1+2));
    TEST("(1+2)*3", &res, (1+2)*3);
    TEST("1/(2*5)", &res, 1/(2*5));
    TEST("10-(1+2)*3", &res, 10-(1+2)*3);
    TEST("1+(2+(3+4))*3", &res, 1+(2+(3+4))*3);
    TEST("30/(3)", &res, 30/(3));
    TEST("8+2*(3*2+1+1)", &res, 8+2*(3*2+1+1));
}

void TestSpaces()
{
    printf(YELLOW"SPACES\n"WHITE);
    TEST(" 1+2", &res, 1+2);
    TEST(" 2+3 ", &res, 2+3);   
    TEST(" 3 +4 ", &res, 3+4);   
    TEST(" 4+ 5 ", &res, 4+5);   
    TEST(" 5 + 6", &res, 5+6); 
    TEST(" 6 + 7 ", &res, 6+7); 
}

void TestError()
{
     printf(YELLOW"ERRORS TESTS\n"WHITE);
     TEST_ERROR("a", &res);
    TEST_ERROR(" 1 + 2 3", &res);
    TEST_ERROR("1/0", &res); 
    TEST_ERROR("2+*9", &res);  
     TEST_ERROR(")8+5", &res);  
    TEST_ERROR("1+2+3+4+5*erez", &res);   
}


int main()
{
    char test_exp[100] = "";
    system("clear");
    printf("Calculator Program.\n\n");

    TestBasicAdd();
    TestBasicMultiply();
    TestBasicDivision();
    TestTwoOperators();
    TestSubtractAndUnary();
    TestThreeOperators();
    TestPower();
    TestPowerCombined();
    TestParentheses();
    TestSpaces();  
    TestError(); 

 
    if (INTERACTIVE)
    {
        printf("\nEnter expression to calculate: (q)uit to exit\n");
    }
    do
    {
        char *new_line_searcher = NULL;
        
        if (INTERACTIVE)
        {
            fgets(test_exp, 100, stdin);
            if ((new_line_searcher = strchr(test_exp, '\n')) != NULL)
            {
                *new_line_searcher = '\0';
            }   
            if (strcmp(test_exp, "Q") != 0 && strcmp(test_exp, "q") != 0)
            {
                TEST_INTERACTIVE(test_exp, &res);
            }
            else
            {
                break;
            } 
        }
    } while (INTERACTIVE);
    
    printf(GREEN"\nThanks for visiting. See you again!\n\n"WHITE);
    return 0;
}

