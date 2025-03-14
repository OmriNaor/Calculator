/*******************************************************************************
	* File: calculator.c
	*
	* Author:
	*   Omri Naor
	*
	* Reviewed by:
	*   - <insert the reviewer here>
	*
	* Reviewed date:
	*   - <insert the review date here>
	*
*******************************************************************************/

#include <stdlib.h> /* For strtod */
#include <math.h> /* For pow */
#include "stack.h" /* Stack */
#include "calculator.h" /* API */

#define DUMMY 39 /* ' */

typedef struct stacks stacks_t;
typedef struct transition transition_t;

/* Function pointer types for math and handler functions */
typedef double (*math_func_t)(double, double);
typedef char* (*handler_func_t)(char* input, stacks_t* stacks);

/* States in the finite state machine */
typedef enum
{
    WAITING_OPERATOR_STATE,
    WAITING_OPERANDS_STATE,
	FINISH_STATE
} states_t;

/* Struct to hold stack pointers for operands and operators */
struct stacks
{
	stack_t* operands_stack;
	stack_t* operators_stack;
};

/* Transition table for state machine: 
		maps current state and input to next state and handler */
struct transition
{
	handler_func_t handler; /* Function to handle the current input */
	states_t next_state; /* Next state after processing input */
};


/**************************** FORWARD DECLARATION ****************************/

static double Add(double num1, double num2);
static double Sub(double num1, double num2);
static double Mul(double num1, double num2);
static double Divide(double num1, double num2);
static double Pow(double base, double power);

static char* SyntaxError(char* input, stacks_t* stacks);
static char* SkipSpace(char* input, stacks_t* stacks);
static char* HandleOperator(char* input, stacks_t* stacks);
static char* HandleOperand(char* input, stacks_t* stacks);
static char* OperatorCalculation(char* input, stacks_t* stacks);
static char* HandleFinish(char* input, stacks_t* stacks);
static char* ParanthesesCalculation(char* input, stacks_t* stacks);

static void InitMathLUT();
static void InitStatesLUT();
static void InitPrioritiesLUT();

static calc_status_t InitMain(stacks_t* stacks, states_t* state);
static int InitStacks(stacks_t* stacks);
static void DestroyStacks(stacks_t* stacks);

/**************************** GLOBAL VARIABLES & LUT ****************************/

transition_t states_LUT[2][256] = {NULL};  /* State transition lookup table */
math_func_t math_LUT[256] = {NULL};        /* Math function lookup table */
int priorities_LUT[256] = {0};             /* Operator precedence lookup table */

static calc_status_t status;
									
/******************************* API FUNCTIONS *******************************/

calc_status_t Calculate(double* result, const char* input)
{
	states_t state;
	stacks_t stacks;
	int current_char_location;

	status = InitMain(&stacks, &state);  /* Initialize stacks and state machine */

	/* Process each character of the input until the finish state is reached */
	while (FINISH_STATE != state && SUCCESS == status)
	{
		current_char_location = (int) *input;
		input = states_LUT[state][current_char_location].handler((char*) input, &stacks);
		state = states_LUT[state][current_char_location].next_state;
	}

	/* If no errors, finish the calculation and return result */
	if (SUCCESS == status)
	{
		HandleFinish((char*) input, &stacks);
		*result = *(double*) Peek(stacks.operands_stack);
	}

	DestroyStacks(&stacks);  /* Clean up allocated memory for stacks */

	return (status); 	
}

/***************************** STATIC FUNCTIONS ******************************/



		/******************** MATH FUNCTIONS ********************/

static double Add(double num1, double num2) { return (num1 + num2); }
static double Sub(double num1, double num2){ return (num1 - num2); }
static double Mul(double num1, double num2){ return (num1 * num2); }
static double Pow(double base, double power){ return (pow(base, power)); }

/* Invalid operation handler */
static double Invalid(double num1, double num2)
{ 
	status = INVALID_SYNTAX;
	(void) num1;
	(void) num2;
	
	return (0);
}

static double Divide(double num1, double num2)
{
	if (0 == num2)
	{
		status = DIV_BY_ZERO;		
		return (0);
	}
	
	return (num1 / num2);
}

		/******************** LUT FUNCTIONS ********************/


static char* HandleNegativeNumber(char* input, stacks_t* stacks)
{
	double res = 0;
	char* remainder = NULL;

	/* Move past the '-' sign */
	++input;

	/* Parse the negative number */
	res = -strtod(input, &remainder);

	Push(stacks->operands_stack, &res);

	return (remainder);
}
	
static char* SkipSpace(char* input, stacks_t* stacks)
{
	(void) stacks;
	return (++input);
}

static char* SyntaxError(char* input, stacks_t* stacks)
{
	(void) input;
	(void) stacks;
	
	status = INVALID_SYNTAX;
	
	return (input);
}

static char* HandleOperator(char* input, stacks_t* stacks)
{
	Push(stacks->operators_stack, input);

	return (++input);
}


static char* HandleOperand(char* input, stacks_t* stacks)
{
	char* remainder = NULL;
	double res = strtod(input, &remainder);
	
	Push(stacks->operands_stack, &res);

	return (remainder);
}


static char* OperatorCalculation(char* input, stacks_t* stacks)
{
	double first_num = 0, second_num = 0, res = 0;
	char operator;
	
	/* Check if operator precedence allows for calculation */
	if (priorities_LUT[(int)*(char*)Peek(stacks->operators_stack)] >= priorities_LUT[(int)*input])
	{
		second_num = *(double*) Peek(stacks->operands_stack);
		Pop(stacks->operands_stack);
		
		first_num = *(double*) Peek(stacks->operands_stack);
		Pop(stacks->operands_stack);
		
		operator = *(char*) Peek(stacks->operators_stack);
		Pop(stacks->operators_stack);
		
		res = math_LUT[(int) operator](first_num, second_num); /* Perform the operation */
		Push(stacks->operands_stack, &res); /* Push result back to operand stack */	
	}
	
	/* If operator precedence allows, handle operator */
	if (priorities_LUT[(int)*input] > 0)
	{
			input = HandleOperator(input, stacks);
	}
	
	return (input);
}

static char* HandleFinish(char* input, stacks_t* stacks)
{
	while (1 != Size(stacks->operators_stack))
	{
		input = OperatorCalculation(input, stacks); /* Perform remaining calculations */
	}
	
	return (input); /* Return input for final state transition */
}

static char* ParanthesesCalculation(char* input, stacks_t* stacks)
{
	char operator = *(char*) Peek(stacks->operators_stack);
	while ('(' != operator && DUMMY != (int) operator)
	{
		/* Perform calculations within parentheses */
		OperatorCalculation(input, stacks); 
		operator = *(char*) Peek(stacks->operators_stack);
	}
	
	status = (int) operator - DUMMY; /* Set status based on closing parenthesis */
	
	Pop(stacks->operators_stack); /* Pop the '(' from the stack */
	
	return (++input);
}

		/******************** INIT FUNCTIONS ********************/
		
static calc_status_t InitMain(stacks_t* stacks, states_t* state)
{
	static int inits_flag = 0;
	char char_dummy = (char) DUMMY;
	double double_dummy = (double) DUMMY;
	*state = WAITING_OPERANDS_STATE;
	
	if (1 == InitStacks(stacks))
	{
		return (MEMORY_FAILURE);
	}
	
	if (0 == inits_flag)
	{
		inits_flag = 1;
		InitMathLUT();
		InitPrioritiesLUT();
		InitStatesLUT();
	}
	
	Push(stacks->operators_stack, &char_dummy);
	Push(stacks->operands_stack, &double_dummy);
	
	return (SUCCESS);
}

static void InitMathLUT()
{
	size_t i = 0;
	for (i = 0 ; i < 256 ; ++i) 
	{
        math_LUT[i] = Invalid; 
    }
    
	math_LUT['+'] = Add;
	math_LUT['-'] = Sub;
	math_LUT['*'] = Mul;
	math_LUT['/'] = Divide;
	math_LUT['^'] = Pow;
}

static void InitStatesLUT()
{	
	transition_t error_transition = {SyntaxError, FINISH_STATE};
	transition_t handle_operand_transition = {HandleOperand, WAITING_OPERATOR_STATE};
	transition_t handle_operator_transition = {HandleOperator, WAITING_OPERANDS_STATE};
	transition_t handle_space_operand = {SkipSpace, WAITING_OPERANDS_STATE};
	transition_t handle_space_operator = {SkipSpace, WAITING_OPERATOR_STATE};
	transition_t handle_negative_number = {HandleNegativeNumber, WAITING_OPERATOR_STATE};
	
	transition_t handle_operator_calculation = {OperatorCalculation, WAITING_OPERANDS_STATE};
	transition_t handle_parantheses_claculation = {ParanthesesCalculation, WAITING_OPERATOR_STATE};
	transition_t handle_finish = {HandleFinish, FINISH_STATE};
	
	size_t i = 0;
	
	
	for (i = 0 ; i < 256 ; ++i) 
	{
        states_LUT[WAITING_OPERATOR_STATE][i] = error_transition;
        states_LUT[WAITING_OPERANDS_STATE][i] = error_transition;
    }
    
    for (i = 0 ; i <= 9 ; ++i)
    {
    	states_LUT[WAITING_OPERANDS_STATE][i + '0'] = handle_operand_transition;
    }
	
	
	states_LUT[WAITING_OPERANDS_STATE]['('] = handle_operator_transition;

	states_LUT[WAITING_OPERANDS_STATE][' '] = handle_space_operand;    
	states_LUT[WAITING_OPERATOR_STATE][' '] = handle_space_operator;

	states_LUT[WAITING_OPERATOR_STATE]['+'] = handle_operator_calculation;
	states_LUT[WAITING_OPERATOR_STATE]['-'] = handle_operator_calculation;
	states_LUT[WAITING_OPERANDS_STATE]['-'] = handle_negative_number;
	states_LUT[WAITING_OPERATOR_STATE]['*'] = handle_operator_calculation;
	states_LUT[WAITING_OPERATOR_STATE]['/'] = handle_operator_calculation;
	states_LUT[WAITING_OPERATOR_STATE]['^'] = handle_operator_calculation;

	states_LUT[WAITING_OPERATOR_STATE][')'] = handle_parantheses_claculation;

	states_LUT[WAITING_OPERATOR_STATE]['\0'] = handle_finish;
	states_LUT[WAITING_OPERATOR_STATE]['\n'] = handle_finish;
	
}


static void InitPrioritiesLUT()
{
	size_t i = 0;
	
	for (i = 0 ; i < 256 ; ++i)
	{
		priorities_LUT[i] = 0; /* Default operator precedence is 0 */
	}
	
	/* Addition and subtraction have lowest precedence */
	priorities_LUT['+'] = 1;
	priorities_LUT['-'] = 1;
	
	/* Multiplication and division have higher precedence */
	priorities_LUT['*'] = 2;
	priorities_LUT['/'] = 2;
	
	/* Exponentiation has the highest precedence */
	priorities_LUT['^'] = 3;
	
	/* Dummy value for end-of-input */
	priorities_LUT[DUMMY] = -1;
}

static int InitStacks(stacks_t* stacks)
{
	stacks->operands_stack = Create(100, sizeof(double));
	if (NULL == stacks->operands_stack)
	{
		return (1);
	}
	
	stacks->operators_stack = Create(100, sizeof(char));
	if (NULL == stacks->operators_stack)
	{
		Destroy(stacks->operands_stack);
		return (1);
	}
	
	return (0);
}

static void DestroyStacks(stacks_t* stacks)
{
	Destroy(stacks->operands_stack);
	Destroy(stacks->operators_stack);
}


