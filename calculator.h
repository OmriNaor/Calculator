#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

/*******************************************************************************
	* File: calculator.h
	*
	* Author:
	*   Omri Naor
	*
	* Purpose:
	*   This header file defines the API for the calculator program, including
	*   function prototypes, error statuses, and type definitions used for
	*   evaluating mathematical expressions in infix notation.
	*
*******************************************************************************/

/**************************** ERROR CODES ************************************/

/* Enum to represent the status of the calculation */
typedef enum
{
    INVALID_SYNTAX,  /* Invalid mathematical syntax encountered */
    SUCCESS,         /* Calculation successful */
    DIV_BY_ZERO,     /* Division by zero error */
    OUT_OF_BOUNDS,   /* Input exceeds allowed bounds or limits */
    MEMORY_FAILURE   /* Memory allocation failure */
} calc_status_t;


/**************************** FUNCTION PROTOTYPES ****************************/

/**
 * @brief Calculate the result of a mathematical expression.
 * 
 * This function parses and evaluates a mathematical expression given as a string,
 * and returns the result. The expression is evaluated using stacks and operator
 * precedence is respected. If there is an error, the appropriate error status is set.
 * 
 * @param result Pointer to a double to store the result of the calculation.
 * @param input  The input string representing the mathematical expression to evaluate.
 * 
 * @return calc_status_t Status code indicating the status result of the calculation.
 */
calc_status_t Calculate(double* result, const char* input);

#endif /* __CALCULATOR_H__ */

