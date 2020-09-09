#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <stdio.h> /* fprintf */
#include <math.h> /* pow */
#include <string.h> /*printf*/ 

#include "calculator.h"
#include "stack.h"

typedef enum {LOWEST, LOW, MEDIUM, HIGH} precedenc_t;
typedef enum {LEFTTORIGHT, RIGHTTOLEFT} assoc_t;
typedef enum {NUMS, OPERS, ERROR} state_t;
typedef enum {NUM, OP, ILLEGAL, NUM_OF_INPUT} input_t;
typedef enum {PLUS, MINUS, DIVIDE, MULTI, OPEN, CLOSE, POW, NUM_OF_ACTIONS} action_t;
typedef state_t (*transition_t)(char **expression, stack_t *, stack_t *);


static status_t Subtract(double *num1, double *num2);
static status_t Multiply(double *num1, double *num2);
static status_t Divide(double *num1, double *num2);
static status_t Add(double *num1, double *num2);
static status_t Pow(double *num1, double *num2);
static state_t operState(char **expression, stack_t *stack_ops, stack_t *stack_nums);
static state_t numState(char **expression, stack_t *stack_ops, stack_t *stack_nums);
static state_t errorState(char **expression, stack_t *stack_ops, stack_t *stack_nums);
static input_t getInput(char **expression);
static int isOp(char symbol);
static int isNum(char symbol);
static int isOptoStart(char symbol);
static status_t Calculate(stack_t *stack_ops, stack_t *stack_nums);
static void cleanUp(stack_t *stack_ops, stack_t *stack_nums);
static void RemoveSpaces(char **expression);
static void FreeNum(double *num);
static void FreeOp(action_t *op);
static state_t NumPushAndCheck(stack_t *stack, double *num);
static state_t OpPushAndCheck(stack_t *stack, action_t *op);


typedef struct
{
	const char oper;
	precedenc_t prec;
	assoc_t assoc;
	status_t (*Actionfuncs)(double *num1, double *num2);
}oper_t;

oper_t OperLut[]=
{
	{'+', LOW, LEFTTORIGHT, Add},
	{'-', LOW, LEFTTORIGHT, Subtract},
	{'/', MEDIUM, LEFTTORIGHT, Divide},
	{'*', MEDIUM, LEFTTORIGHT, Multiply},
	{'(', LOWEST, LEFTTORIGHT, NULL},
	{')', LOWEST, LEFTTORIGHT, NULL},
    {'^', HIGH, RIGHTTOLEFT, Pow},
	{'\0', '\0', '\0', '\0'}
};


transition_t (lut_fsm[][NUM_OF_INPUT])=
{ 
   { numState, errorState, errorState},
   { errorState, operState, errorState}
};



status_t Calculator(const char *expression, double *res)
{

	char **runner = NULL; 
	size_t len = 0;
	stack_t *stack_ops = NULL;
	stack_t *stack_nums = NULL;
	state_t state = NUM;
	input_t input = ILLEGAL;
	status_t status = STAT_SUCCESS;

	assert(expression && res);

	runner = (char**)&expression;
	len = strlen(expression);

	stack_nums = StackCreate(len*sizeof(double));
	if (NULL == stack_nums)
	{
		fprintf(stderr, "allocation failed\n");
		return STAT_FAIL;
	}

	stack_ops = StackCreate(len*sizeof(char));
	if (NULL == stack_ops)
	{
		fprintf(stderr, "allocation failed\n");
		StackDestroy(stack_nums);
		return STAT_FAIL;
	}

	while(**runner != '\0' && state != ERROR)
	{	
        RemoveSpaces(runner);
        input = getInput(runner);
		state = lut_fsm[state][input](runner, stack_ops, stack_nums); 
        RemoveSpaces(runner);
	} 

    if(state == ERROR || input == ILLEGAL)
    {
        res = NULL;
        cleanUp(stack_ops, stack_nums);
        return STAT_FAIL;
    }

	while(!StackIsEmpty(stack_ops))
	{
		status = Calculate(stack_ops, stack_nums);
	}
	
	*res = *(double*)StackPeek(stack_nums);
 
    cleanUp(stack_ops, stack_nums);

	return status;
}



/******************** input ************************/

input_t getInput(char **expression)
{
	double num = 0;
	input_t input = ILLEGAL;
	char *leftover = NULL;
	char symbol;

	num = strtod(*expression, &leftover);
	num = abs(num); 

	symbol = *expression[0];

	if(isNum(symbol))
	{
		input = NUM;
	}

	if(isOp(symbol))
	{
	 	if( isOp(*(*expression - 1)) && (symbol == '-'))
		{
			input = NUM;
		} 
         else 
		{
			input = OP;	
		}
	}

return input;
}



/******************** isop ************************/
static int isOp(char symbol)
{
	char *op = "+-*/^()";
	char *ret = NULL;

	ret = strchr(op, symbol);

	return ret != NULL ? 1 : 0;
}

/******************** optostart ************************/
static int isOptoStart(char symbol)
{
	char *startop = "+-(";
	char *ret = NULL;

	ret = strchr(startop, symbol);

	return ret != NULL ? 1 : 0;
}


/********************  isNum************************/
static int isNum(char symbol)
{
	char *num = "-0123456789.";
	char *ret = NULL;

	ret = strchr(num, symbol);

	return ret != NULL ? 1 : 0;
}

/******************** state actions ************************/
static state_t numState(char **expression, stack_t *stack_ops, stack_t *stack_nums)
{
	double *num = NULL;
	state_t state = ERROR;

 	num = (double *)malloc(sizeof(double));
	if (NULL == num)
	{
		fprintf(stderr, "allocation failed\n");
		return ERROR;
	}

	*num = strtod(*expression, expression);


    if(*expression[0] != '(')
    {
        state = NumPushAndCheck(stack_nums, num);
    }

	return state;
}




static state_t operState(char **expression, stack_t *stack_ops, stack_t *stack_nums)
{
	char op = '\0';
	action_t *i = NULL;
    action_t *tofree = NULL;
    state_t state = NUMS;

	i = (action_t *)malloc(sizeof(action_t));
	if(i == NULL)
    {
        fprintf(stderr, "allocation failed\n");
		return ERROR;
    }

	op = *expression[0];

    if(!isOp(op) || 
	(StackIsEmpty(stack_nums) && !isOptoStart(op)) ||
	(*(*expression + 1) == '\0' && op != ')'))
    {
		/* cleanUp(stack_ops, stack_nums); */
        return ERROR;
    }

	for((*i)=0; OperLut[*i].oper != '\0'; (*i)++ )
	{
		if(OperLut[*i].oper == op)
		{
            if( *i  == CLOSE )
            {
                while(!StackIsEmpty(stack_ops) &&  (*(action_t*)StackPeek(stack_ops) != OPEN))
                {
                    if(Calculate(stack_ops, stack_nums) != STAT_SUCCESS)
					{
						return ERROR;
					}
                    state = OPERS;
                }
                tofree = (action_t*)StackPeek(stack_ops);
                StackPop(stack_ops);
                FreeOp(tofree);
                FreeOp(i); 
				break;
            }
			else if(StackIsEmpty(stack_ops) || 
			(OperLut[*i].prec > OperLut[*(action_t *)StackPeek(stack_ops)].prec)||
			(OperLut[*i].prec == OperLut[*(action_t *)StackPeek(stack_ops)].prec
			&& OperLut[*i].assoc == RIGHTTOLEFT) ||
             (*i == OPEN))
			{
				state = OpPushAndCheck(stack_ops, i);
				break;
			}
			else
			{	
				if(Calculate(stack_ops, stack_nums) != STAT_SUCCESS)
				{
					return ERROR;
				}
				(*i)--;
			}

        }
		
	}
	(*expression)++;

	return state;
}




static state_t errorState(char **expression, stack_t *stack_ops, stack_t *stack_nums)
{

    if ((*expression[0] == '(') || *expression[0] == ')')
    {
        return OPERS;
    }
    else
    {

        fprintf(stderr, "Illegal input\n");
        return ERROR;
    }
}


/*******************cleanup************************/
static void cleanUp(stack_t *stack_ops, stack_t *stack_nums)
{
    double *num_to_free = NULL;
    action_t *op_to_free = NULL;

    while(!StackIsEmpty(stack_nums))
    {
        num_to_free = (double*)StackPeek(stack_nums);
        StackPop(stack_nums);
        FreeNum(num_to_free);
    }

    while(!StackIsEmpty(stack_ops))
    {
        op_to_free = (action_t*)StackPeek(stack_ops);
        StackPop(stack_ops);
        FreeOp(op_to_free);
    }

	StackDestroy(stack_nums);
	StackDestroy(stack_ops);
}




/*******************calculate************************/
static status_t Calculate(stack_t *stack_ops, stack_t *stack_nums)
{
	double *num2 = NULL;
	double *num1 = NULL;
	action_t *oper = NULL;
	int stat = 0;
	status_t status = STAT_SUCCESS;

	num2 = (double *)StackPeek(stack_nums);
	StackPop(stack_nums);
	num1 = (double *)StackPeek(stack_nums);
	StackPop(stack_nums);
	oper = (action_t *)StackPeek(stack_ops);
	StackPop(stack_ops);
	status = OperLut[*oper].Actionfuncs(num1, num2);
	
	stat = StackPush(stack_nums, num1);
    if(stat == 0)
	{   
		fprintf(stderr, "push failed\n");
		return STAT_FAIL;
	}

    FreeOp(oper);
    FreeNum(num2);
	
	return status;
}


/******************** removespaces ************************/
static void RemoveSpaces(char **expression)
{
    for(*expression; *expression[0] == ' ';  (*expression)++)
    {}
}

/********************ops action funcs ************************/
static status_t Add(double *num1, double *num2)
{
	*num1 += *num2;

	return STAT_SUCCESS;
}


static status_t Subtract(double *num1, double *num2)
{
	*num1 -= *num2;

	return STAT_SUCCESS;
}

static status_t Multiply(double *num1, double *num2)
{
	*num1 *= *num2;

	return STAT_SUCCESS;
}

static status_t Divide(double *num1, double *num2)
{
	*num1 /= *num2;

	if(*num2 == 0)
	{
		return STAT_FAIL;
	}

	return STAT_SUCCESS;
}

static status_t Pow(double *num1, double *num2)
{
	*num1 = pow(*num1,*num2);

	return STAT_SUCCESS;
}


/******************** more functions ************************/

static void FreeNum(double *num)
{
    free(num);
    num = NULL;
}

static void FreeOp(action_t *op)
{
    free(op);
    op = NULL;
}


static state_t NumPushAndCheck(stack_t *stack, double *num)
{
    int status = StackPush(stack, num);
    if(status == 0) 
    {   
        fprintf(stderr, "push failed\n"); 
        return ERROR;
    }
    return OPERS;
}

static state_t OpPushAndCheck(stack_t *stack, action_t *op)
{
    int status = StackPush(stack, op);
    if(status == 0)
    {   
        fprintf(stderr, "push failed\n");
        return ERROR;
    }
    return NUMS;
}