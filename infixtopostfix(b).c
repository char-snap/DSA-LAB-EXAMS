/*Infix to postfix conversion and evaluation*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#define size 20

struct stack1
{
    char items[size];
    int top;
};
typedef struct stack1 STK1;

struct stack2
{
    float items[size];
    int top;
};
typedef struct stack2 STK2;

void Push1(STK1 *, char);
char Pop1(STK1 *);
int IsOperand(char);
void Push2(STK2 *, float);
float Pop2(STK2 *);
void InfixToPostfix(char[], char[]);
int StackPriority(char);
void Evaluate(char []);
float Compute(float, float, char);

void main()
{
    char infix[20], postfix[20];
    int choice;
    
    for(;;)
    {
        printf("\nEnter your choice:\n1:Infix to postfix conversion\n2:Postfix evaluation\n3:Exit\n");
        scanf("%d",&choice);
        
        switch(choice)
        {
            case 1: printf("Enter the infix expression: ");
                    scanf("%s",infix);
                    InfixToPostfix(infix,postfix);
                    printf("Infix expression is : %s\nPostfix expression is : %s\n",infix,postfix);
                    break;
            case 2: Evaluate(postfix); break;
            default: exit(0);
        }
    }
}

void Push1(STK1 *ps, char c)
{
    if(ps->top == size-1)
    {
        printf("Stack is full!!\n");
        return;
    }
    ps->top++;
    ps->items[ps->top] = c;
} 

char Pop1(STK1 *ps)
{
    char c;
    if(ps->top == -1)
    {
        printf("Stack is empty!!\n");
        return '\0';
    }
    c = ps->items[ps->top];
    ps->top--;
    return c;
}

int IsOperand(char c)
{
    switch(c)
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        case '$':
        case '(':
        case ')': return 0;
        default: return 1;
    }
}

int InputPriority(char opr)
{
    switch(opr)
    {
        case '+':
        case '-': return 1;
        case '*': 
        case '/': return 3;
        case '^':
        case '$': return 7;
        case '(': return 9;
        case ')': return 0;
    }
}

int StackPriority(char opr)
{
    switch(opr)
    {
        case '+':
        case '-': return 2;
        case '*':
        case '/': return 4;
        case '^':
        case '$': return 6;
        case '(': return 0;
    }
}

void InfixToPostfix(char in[], char pos[])
{
    STK1 operatorSTK;
    operatorSTK.top = -1;
    char c;
    int i=0, j=0;
    while((c = in[i++]) != '\0')
    {
        if(IsOperand(c))
            pos[j++] = c;
        else
        {
            while(operatorSTK.top != -1 && StackPriority(operatorSTK.items[operatorSTK.top]) > InputPriority(c))
            {
                if(c == ')')
                {
                    while(operatorSTK.items[operatorSTK.top] != '(')
                        pos[j++] = Pop1(&operatorSTK);
                    Pop1(&operatorSTK);
                    break;
                }
                pos[j++] = Pop1(&operatorSTK);
            }
            if(c != ')')
                Push1(&operatorSTK, c);
        }
    }
    while(operatorSTK.top != -1)
        pos[j++] = Pop1(&operatorSTK);
    pos[j] = '\0';
}

void Push2(STK2 *ps, float c)
{
    if(ps->top == size-1)
    {
        printf("Stack is full!!\n");
        return;
    }
    ps->top++;
    ps->items[ps->top] = c;
}

float Pop2(STK2 *ps)
{
    float c;
    if(ps->top == -1)
    {
        printf("stack is empty!!\n");
        return 0;
    }
    c = ps->items[ps->top];
    ps->top--;
    return c;
}

void Evaluate(char pos[])
{
    STK2 operandSTK;
    STK1 operatorSTK;
    char c;
    float operand;
    float op1, op2, res;
    int j=0;
    operandSTK.top = -1;
    while((c = pos[j++]) != '\0')//Scanning the expression
    {
        if(IsOperand(c))
        {
            if(isalpha(c))
            {
                printf("Enter the value for operand %c: ",c);
                scanf("%f",&operand);
                Push2(&operandSTK, operand);
            }
            else
                Push2(&operandSTK, c-'0');
        }
        else
        {
            op2 = Pop2(&operandSTK);
            op1 = Pop2(&operandSTK);
            res = Compute(op1, op2, c);
            Push2(&operandSTK, res);
        }
    }
    res = Pop2(&operandSTK);
    if(operandSTK.top != -1 || operatorSTK.top != -1)
        printf("Invalid expression!!\n");
    else
        printf("Value of the expression is %f\n", res);//End of evaluation
}

float Compute(float op1, float op2, char opr)
{
    switch(opr)
    {
        case '+': return(op1 + op2);
        case '-': return(op1 - op2);
        case '*': return(op1 * op2);
        case '/': if(op2 == 0)
                  {
                      printf("Oops!! Cannot divide by zero!!\n");
                      return 0;
                  }
                  return(op1/op2);
        case '^':
        case '$': return pow(op1, op2);
        default: printf("Invalid expression!!\n");
    }
}