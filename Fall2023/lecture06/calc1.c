/* calc with if-else 
 * to compile: gcc calc1.c -o calc1
 * to run: ./calc1
*/

#include <stdio.h>

int main()
{
    /* declare variables */
    float operand1, operand2;
    char operator;
    
    /* get input */
    printf("Enter expression: ");
    scanf("%f %c %f", &operand1, &operator, &operand2);

    /* compute */
    if ( operator == '+' ) 
         printf("%f + %f = %f\n", operand1, operand2, operand1+operand2);
    else if ( operator == '-' ) 
         printf("%f - %f = %f\n", operand1, operand2, operand1-operand2);
    else if ( operator == '*' ) 
         printf("%f * %f = %f\n", operand1, operand2, operand1*operand2);
    else if ( operator == '/' ) 
         printf("%f / %f = %f\n", operand1, operand2, operand1/operand2);
    else
         printf("Unknown operator %c\n", operator);


    return 0;
}
