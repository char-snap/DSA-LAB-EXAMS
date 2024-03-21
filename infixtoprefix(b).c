/*Infix to prefix conversion and evaluation*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
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

struct stack3
{
    char items[size][20];
    int top;
};
typedef struct stack3 STK3;

void Push1(STK1 *, char);
void Push2(STK2 *, float);
void Push3(STK3 *, char[]);
char Pop1(STK1 *);
float Pop2(STK2 *);
char *Pop3(STK3 *);
int IsOperand(char);
int InputPriority(char);
int StackPriority(char);
void InfixToPrefix(char[], char[]);
void Evaluate(char []);
float Compute(float, float, char);
void PartialExpression(STK1 *, STK3 *);

void main()
{
    char infix[20], prefix[20];
    int choice;
    
    for(;;)
    {
        printf("\nEnter your choice:\n1:Infix to prefix conversion\n2:Prefix expression evaluation\n3:Exit\n");
        scanf("%d",&choice);
        
        switch(choice)
        {
            case 1: printf("Enter the infix expression: ");
                    scanf("%s",infix);
                    InfixToPrefix(infix,prefix);
                    printf("Infix expression is : %s\nPrefix expression is : %s\n",infix,prefix);
                    break;
            case 2: Evaluate(prefix); break;
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

void Push3(STK3 *ps, char items[])
{
    if(ps->top == size-1)
    {
        printf("Stack is full!!\n");
        return;
    }
    ps->top++;
    strcpy(ps->items[ps->top], items);
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

char *Pop3(STK3 *ps)
{
    char *item;
    if(ps->top == -1)
    {
        printf("Stack is empty!!\n");
        return item;
    }
    item = ps->items[ps->top];
    ps->top--;
    return item;
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

void InfixToPrefix(char in[], char pre[])
{
    STK1 operatorSTK;
    operatorSTK.top = -1;
    STK3 prefixSTK;
    prefixSTK.top = -1;
    char c, *op1, *op2, temp[2];
    int i=0;
    while((c = in[i++]) != '\0')
    {
        if(IsOperand(c))
        {
            temp[0] = c;
            temp[1] = '\0';
            Push3(&prefixSTK, temp);
        }
        else
        {
            while(operatorSTK.top != -1 && StackPriority(operatorSTK.items[operatorSTK.top]) > InputPriority(c))
            {
                if(c == ')')
                {
                    while(operatorSTK.items[operatorSTK.top] != '(')
                        PartialExpression(&operatorSTK, &prefixSTK);
                    Pop1(&operatorSTK);
                    break;
                }
                PartialExpression(&operatorSTK, &prefixSTK);
            }
            if(c != ')')
                Push1(&operatorSTK, c);
        }
    }
    while(operatorSTK.top != -1)
        PartialExpression(&operatorSTK, &prefixSTK);
    strcpy(pre, Pop3(&prefixSTK));
    if(prefixSTK.top != -1)
        printf("Invalid prefix expression!!(More number of operands than operator)\n");
}

void Evaluate(char pre[])
{
    STK2 evaluateSTK;
    evaluateSTK.top = -1;
    char c;
    float operand;
    float op1, op2, res;
    int i = strlen(pre)-1;
    while(i >= 0)//Scanning the expression
    {
        c = pre[i];
        if(IsOperand(pre[i]))
        {
            if(isalpha(pre[i]))
            {
                printf("Enter the value for operand %c: ",c);
                scanf("%f",&operand);
                Push2(&evaluateSTK, operand);
            }
            else
                Push2(&evaluateSTK, c-'0');
        }
        else
        {
            op1 = Pop2(&evaluateSTK);
            op2 = Pop2(&evaluateSTK);
            res = Compute(op1, op2, c);
            Push2(&evaluateSTK, res);
        }
        i--;
    }
    res = Pop2(&evaluateSTK);
    if(evaluateSTK.top == -1 && op2 != 0)
        printf("Value of the expression is %f\n",res);
    else
        printf("Invalid prefix expression\n");//End of evaluation
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
                  else 
                    return(op1/op2);
        case '^':
        case '$': return pow(op1, op2);
        default: printf("Invalid expression!!\n");
    }
}

void PartialExpression(STK1 *s1, STK3 *s2)
{
    char temp[2];
    char opr, *op1, *op2, pre[20];
    opr = Pop1(s1);
    temp[0] = opr;
    temp[1] = '\0';
    op2 = Pop3(s2);
    op1 = Pop3(s2);
    strcpy(pre, temp);
    strcat(pre, op1);
    strcat(pre, op2);
    Push3(s2, pre);
}