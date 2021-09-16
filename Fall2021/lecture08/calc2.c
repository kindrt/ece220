/* calc with switch 
 * to compile: gcc calc2.c -o calc2
 * to run: ./calc2
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
    switch (operator)
    {
        case '+':  
         printf("%f + %f = %f\n", operand1, operand2, operand1+operand2);
         break;
        case '-': 
         printf("%f - %f = %f\n", operand1, operand2, operand1-operand2);
         break;
        case '*': 
         printf("%f * %f = %f\n", operand1, operand2, operand1*operand2);
         break;
        case '/': 
         printf("%f / %f = %f\n", operand1, operand2, operand1/operand2);
         break;
        default:
         printf("Unknown operator %c\n", operator);
     }

    return 0;
}
