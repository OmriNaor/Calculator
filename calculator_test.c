#include <stdio.h>
#include "calculator.h"

#define GREEN "\x1b[1;32m"
#define RED "\x1b[1;31m"
#define UNFORMAT "\x1b[1;0m"

void TestValidSyntax();
void TestEdgeCases();
void TestInvalidSyntax();

int main(void)
{
	printf("\n\n---- 🙏️ Testing Valid Syntax 🙏️ ----\n");
    TestValidSyntax();
    printf("\n---- 🙏️ Testing Edge Cases 🙏️ ----\n");
    TestEdgeCases();
    printf("\n---- 🙏️ Testing Invalid Syntax 🙏️ ----\n");
    TestInvalidSyntax();
    printf("\n\nDon't forget to check valgrind! 🤭️\n\n");
	
    return (0);
}

/********************** Valid Syntax Tests **********************/

void TestValidSyntax()
{
    double result;
    int status;

    /* Test 1: Simple addition */
    printf("TestValidSyntax 1: 10 + 2 = ");
    status = Calculate(&result, "10+2");
    if (status == SUCCESS && result == 12.0) 
    {
        printf(GREEN "Passed\n" UNFORMAT);
    } 
    else 
    {
        printf(RED "Failed. Expected Result: 12.0, Received: %f, Status: %d\n" UNFORMAT, result, status);
    }

    /* Test 2: Simple subtraction */
    printf("TestValidSyntax 2: 15 - 3 = ");
    status = Calculate(&result, "15-3");
    if (status == SUCCESS && result == 12.0) 
    {
        printf(GREEN "Passed\n" UNFORMAT);
    } 
    else 
    {
        printf(RED "Failed. Expected Result: 12.0, Received: %f, Status: %d\n" UNFORMAT, result, status);
    }

    /* Test 3: Multiplication */
    printf("TestValidSyntax 3: 6 * 3 = ");
    status = Calculate(&result, "6*3");
    if (status == SUCCESS && result == 18.0) 
    {
        printf(GREEN "Passed\n" UNFORMAT);
    } 
    else 
    {
        printf(RED "Failed. Expected Result: 18.0, Received: %f, Status: %d\n" UNFORMAT, result, status);
    }

    /* Test 4: Division */
    printf("TestValidSyntax 4: 20 / 4 = ");
    status = Calculate(&result, "20/4");
    if (status == SUCCESS && result == 5.0) 
    {
        printf(GREEN "Passed\n" UNFORMAT);
    } 
    else 
    {
        printf(RED "Failed. Expected Result: 5.0, Received: %f, Status: %d\n" UNFORMAT, result, status);
    }

    /* Test 5: Parentheses */
    printf("TestValidSyntax 5: 2 * (3 + 4) = ");
    status = Calculate(&result, "2*(3+4)");
    if (status == SUCCESS && result == 14.0) 
    {
        printf(GREEN "Passed\n" UNFORMAT);
    } 
    else 
    {
        printf(RED "Failed. Expected Result: 14.0, Received: %f, Status: %d\n" UNFORMAT, result, status);
    }

    /* Test 6: Order of operations (multiplication before addition) */
    printf("TestValidSyntax 6: 2 + 3 * 4 = ");
    status = Calculate(&result, "2+3*4");
    if (status == SUCCESS && result == 14.0) 
    {
        printf(GREEN "Passed\n" UNFORMAT);
    } 
    else 
    {
        printf(RED "Failed. Expected Result: 14.0, Received: %f, Status: %d\n" UNFORMAT, result, status);
    }

    /* Test 7: Complex expression with multiple operations */
    printf("TestValidSyntax 7: (3 + 5) * (2 - 4) + 9 / 3 = ");
    status = Calculate(&result, "(3+5)*(2-4)+9/3");
    if (status == SUCCESS && result == -13.0) 
    {
        printf(GREEN "Passed\n" UNFORMAT);
    } 
    else 
    {
        printf(RED "Failed. Expected Result: -13.0, Received: %f, Status: %d\n" UNFORMAT, result, status);
    }
}

/********************** Edge Case Tests **********************/

void TestEdgeCases()
{
    double result;
    int status;

    /* Test 1: Division by zero */
    printf("TestEdgeCases 1: 5 / 0 = ");
    status = Calculate(&result, "5/0");
    if (status == DIV_BY_ZERO) 
    {
        printf(GREEN "Passed\n" UNFORMAT);
    } 
    else 
    {
        printf(RED "Failed. Expected Status: %d, Received: %d\n" UNFORMAT, DIV_BY_ZERO, status);
    }

    /* Test 2: Complex expression with parentheses and zero */
    printf("TestEdgeCases 2: (3 + 5) * (0) = ");
    status = Calculate(&result, "(3+5)*0");
    if (status == SUCCESS && result == 0.0) 
    {
        printf(GREEN "Passed\n" UNFORMAT);
    } 
    else 
    {
        printf(RED "Failed. Expected Result: 0.0, Received: %f, Status: %d\n" UNFORMAT, result, status);
    }

    /* Test 3: Negative numbers */
    printf("TestEdgeCases 3: -5 + 3 = ");
    status = Calculate(&result, "-5+3");
    if (status == SUCCESS && result == -2.0) 
    {
        printf(GREEN "Passed\n" UNFORMAT);
    } 
    else 
    {
        printf(RED "Failed. Expected Result: -2.0, Received: %f, Status: %d\n" UNFORMAT, result, status);
    }

    /* Test 4: Very large number */
    printf("TestEdgeCases 4: 1e10 + 1e10 = ");
    status = Calculate(&result, "1e10+1e10");
    if (status == SUCCESS && result == 2e10) 
    {
        printf(GREEN "Passed\n" UNFORMAT);
    } 
    else 
    {
        printf(RED "Failed. Expected Result: 2e10, Received: %f, Status: %d\n" UNFORMAT, result, status);
    }
    
    /* Test 5: Negative number at the beginning */
    printf("TestEdgeCases 5: -10 * 2 = ");
    status = Calculate(&result, "-10*2");
    if (status == SUCCESS && result == -20.0) 
    {
        printf(GREEN "Passed\n" UNFORMAT);
    } 
    else 
    {
        printf(RED "Failed. Expected Result: -20.0, Received: %f, Status: %d\n" UNFORMAT, result, status);
    }

    /* Test 6: Negative number inside parentheses */
    printf("TestEdgeCases 6: (-5) + 7 = ");
    status = Calculate(&result, "(-5)+7");
    if (status == SUCCESS && result == 2.0) 
    {
        printf(GREEN "Passed\n" UNFORMAT);
    } 
    else 
    {
        printf(RED "Failed. Expected Result: 2.0, Received: %f, Status: %d\n" UNFORMAT, result, status);
    }

    /* Test 7: Negative number after an operator */
    printf("TestEdgeCases 7: 3 * -4 = ");
    status = Calculate(&result, "3*-4");
    if (status == SUCCESS && result == -12.0) 
    {
        printf(GREEN "Passed\n" UNFORMAT);
    } 
    else 
    {
        printf(RED "Failed. Expected Result: -12.0, Received: %f, Status: %d\n" UNFORMAT, result, status);
    }

    /* Test 8: Nested parentheses with negatives */
    printf("TestEdgeCases 8: (-2) * (-3) = ");
    status = Calculate(&result, "(-2)*(-3)");
    if (status == SUCCESS && result == 6.0) 
    {
        printf(GREEN "Passed\n" UNFORMAT);
    } 
    else 
    {
        printf(RED "Failed. Expected Result: 6.0, Received: %f, Status: %d\n" UNFORMAT, result, status);
    }

    /* Test 9: Negative result */
    printf("TestEdgeCases 9: 5 - 10 = ");
    status = Calculate(&result, "5-10");
    if (status == SUCCESS && result == -5.0) 
    {
        printf(GREEN "Passed\n" UNFORMAT);
    } 
    else 
    {
        printf(RED "Failed. Expected Result: -5.0, Received: %f, Status: %d\n" UNFORMAT, result, status);
    }
    
    /* Test 10: Double negative without parentheses */
    printf("TestEdgeCases 10: --5 = ");
    status = Calculate(&result, "--5");
    if (status == SUCCESS && result == 5.0) 
    {
        printf(GREEN "Passed\n" UNFORMAT);
    } 
    else 
    {
        printf(RED "Failed. Expected Result: 5.0, Received: %f, Status: %d\n" UNFORMAT, result, status);
    }

}

/********************** Invalid Syntax Tests **********************/

void TestInvalidSyntax()
{
    double result;
    int status;

    /* Test 1: Missing operand */
    printf("TestInvalidSyntax 1: 5 + = ");
    status = Calculate(&result, "5+");
    if (status == INVALID_SYNTAX) 
    {
        printf(GREEN "Passed\n" UNFORMAT);
    } 
    else 
    {
        printf(RED "Failed. Expected Status: %d, Received: %d\n" UNFORMAT, INVALID_SYNTAX, status);
    }

    /* Test 2: Extra operator without operand */
    printf("TestInvalidSyntax 2: 5 * + 2 = ");
    status = Calculate(&result, "5*+2");
    if (status == INVALID_SYNTAX) 
    {
        printf(GREEN "Passed\n" UNFORMAT);
    } 
    else 
    {
        printf(RED "Failed. Expected Status: %d, Received: %d\n" UNFORMAT, INVALID_SYNTAX, status);
    }

    /* Test 3: Unmatched parentheses */
    printf("TestInvalidSyntax 3: (3 + 5 = ");
    status = Calculate(&result, "(3+5");
    if (status == INVALID_SYNTAX) 
    {
        printf(GREEN "Passed\n" UNFORMAT);
    } 
    else 
    {
        printf(RED "Failed. Expected Status: %d, Received: %d\n" UNFORMAT, INVALID_SYNTAX, status);
    }

    /* Test 4: Multiple operators together */
    printf("TestInvalidSyntax 4: 5 ++ 2 = ");
    status = Calculate(&result, "5++2");
    if (status == INVALID_SYNTAX) 
    {
        printf(GREEN "Passed\n" UNFORMAT);
    } 
    else 
    {
        printf(RED "Failed. Expected Status: %d, Received: %d\n" UNFORMAT, INVALID_SYNTAX, status);
    }

    /* Test 5: Empty input */
    printf("TestInvalidSyntax 5: empty input = ");
    status = Calculate(&result, "");
    if (status == INVALID_SYNTAX) 
    {
        printf(GREEN "Passed\n" UNFORMAT);
    } 
    else 
    {
        printf(RED "Failed. Expected Status: %d, Received: %d\n" UNFORMAT, INVALID_SYNTAX, status);
    }


    /* Test 6: Negative sign misplaced */
    printf("TestInvalidSyntax 6: 5 - * 3 = ");
    status = Calculate(&result, "5-*3");
    if (status == INVALID_SYNTAX) 
    {
        printf(GREEN "Passed\n" UNFORMAT);
    } 
    else 
    {
        printf(RED "Failed. Expected Status: %d, Received: %d\n" UNFORMAT, INVALID_SYNTAX, status);
    }
}

