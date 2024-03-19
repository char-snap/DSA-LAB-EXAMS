#include <stdio.h>
#include <stdlib.h>
#define SIZE 10
int N = 0;

void insertbyposition(int *p, int pos)
{
    int ele, i;
    if (N >= SIZE)
    {
        printf("Array is FUll");
        return;
    }
    if (pos < 1 || pos > N + 1)
    {
        printf("Invalid position");
        return;
    }
    printf("Enter the elemnt:");
    scanf("%d", &ele);

    for (i = N - 1; i >= pos - 1; i--)
    {
        *(p + i + 1) = *(p + i);
    }
    *(p + i + 1) = ele;
    N++;
}

void reverse(int *p)
{
    int i, temp;
    if (N == 0)
    {
        printf("Empty");
        return;
    }
    for (i = 0; i < N / 2; i++)
    {
        temp = *(p + (N - 1) - i);
        *(p + (N - 1) - i) = *(p + i);
        *(p + i) = temp;
    }
}

void insertbyorder(int *p)
{
    int i, ele;
    if (N >= SIZE)
    {
        return;
    }
    printf("Enter the elemnt :");
    scanf("%d", &ele);
    for (i = N - 1; i >= 0 && *(p + i) > ele; i--)
    {
        *(p + i + 1) = *(p + i);
    }
    *(p + i + 1) = ele;
    N++;
}

int searchbykey(int *p, int ele)
{
    if (N == 0)
    {
        printf("array is empty");
        return 0;
    }
    for (int i = 0; i < N; i++)
    {
        if (*(p + i) == ele)
        {
            printf("The element is %d", *(p + i));
            return 0;
        }
    }
    printf("invalid position\n");
}

void deletebypos(int *p, int pos)
{
    if (N == 0)
    {
        printf("array empty:");
        return;
    }
    if (pos < 1 || pos > N)
    {
        printf("Invalid position");
        return;
    }
    for (int i = pos - 1; i <= N; i++)
        *(p + i) = *(p + i + 1);
    N--;
}

void deletebykey(int *p, int key)
{
    int Si, pos;
    if (N == 0)
    {
        printf("empty");
        return;
    }
    Si = searchbykey(p, key);
    if (Si == -1)
    {
        printf("Key not found");
        return;
    }
    pos = Si + 1;
    deletebypos(p, pos);
    N--;
}

void display(int *p)
{
    if (N == 0)
    {
        printf("array is empty");
        return;
    }
    for (int i = 0; i < N; i++)
        printf("%d\t", *(p + i));
}

void main()
{
    int *p;
    int choice, ele, pos, key;

    p = (int *)malloc(SIZE * sizeof(int));

    printf("Enter the size of array:");
    scanf("%d", &N);
    printf("enter the array elemnts:");
    for (int i = 0; i < N; i++)
        scanf("%d", p + i);

    for (;;)
    {
        printf("Enter your choice:\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter the posi");
            scanf("%d", &pos);
            insertbyposition(p, pos);
            display(p);
            break;

        case 2:
            reverse(p);
            display(p);
            break;

        case 3:
            insertbyorder(p);
            display(p);
            break;

        case 4:
            printf("enter the elemnt to search");
            scanf("%d", &ele);
            pos = searchbykey(p, ele);
            /*if(pos!=-1)
            printf(" element is founf at pos %d",(pos+1));
            else
            printf("element not found");break;*/
            break;

        case 5:
            printf("Enter the pos:");
            scanf("%d", &pos);
            deletebypos(p, pos);
            display(p);
            break;

        case 6:
            printf("Enter the key");
            scanf("%d", &key);
            deletebykey(p, key);
            display(p);
        }
    }
}