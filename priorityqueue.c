//Priority queue with dynamic memory allocation/

#include<stdio.h>
#include<stdlib.h>
int size;

struct Queue
{
    int *items;
    int Front, Rear;
};
typedef struct Queue QUE;

void Insert(QUE *);
void DeleteMin(QUE *);
void Display(QUE *);
void QFront(QUE *);
void QRear(QUE *);

void main()
{
    QUE Q;
    int choice;
    Q.Front = 0;
    Q.Rear = -1;

    printf("Enter the size of the queue: ");
    scanf("%d",&size);
    Q.items = (int *)malloc(size*sizeof(int));

    for(;;)
    {
        printf("\nEnter your choice:\n1:Insert\n2:Delete by least priority\n3:Display\n4:Display first item of the queue\n5:Display last item of the queue\n");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1: Insert(&Q); Display(&Q); break;
            case 2: DeleteMin(&Q); Display(&Q); break;
            case 3: Display(&Q); break;
            case 4: QFront(&Q); break;
            case 5: QRear(&Q); break;
            default: exit(0);
        }
    }
}

void Insert(QUE *PQ)
{
    int item, choice;
    if(PQ->Rear == size-1)
    {
        printf("Queue overflow!! Insertion is not possible!! Do you want to go for reallocation??\n");
        printf("Enter your choice:\n1:Yes\n2:No\n");
        scanf("%d",&choice);
        if(choice == 1)
        {
            size = size*2;
            PQ->items = (int *)realloc(PQ->items,size*sizeof(int));
        }
        else
        {
            printf("No more insertion is possible!!\n");
            return;
        }

    }
    printf("Enter the item to be inserted: ");
    scanf("%d", &item);
    PQ->Rear++;
    *(PQ->items + PQ->Rear) = item;
}

void DeleteMin(QUE *PQ)
{
    int min, i, minindex;
    if(PQ->Front > PQ->Rear)
    {
        printf("Queue underflow!! Deletion is not possible!!\n");
        return;
    }
    min = *(PQ->items + PQ->Front);
    minindex = PQ->Front;
    for(i=1; i<=PQ->Rear; i++)
    {
        if(*(PQ->items + i) < min)
        {
            min = *(PQ->items + i);
            minindex = i;
        }
    }
     printf("Deleted element is %d\n",*(PQ->items +minindex));
    for(i=minindex; i<PQ->Rear; i++)
        *(PQ->items + i) = *(PQ->items + (i+1));
    PQ->Rear--;
}

void Display(QUE *PQ)
{
    int i;
    if(PQ->Front > PQ->Rear)
    {
        printf("Queue is empty!!\n");
        return;
    }
    printf("The entered queue is :\n");
    for(i=PQ->Front; i<=PQ->Rear; i++)
        printf("%d\t",*(PQ->items + i));
    printf("\n");
}

void QFront(QUE *PQ)
{
    if(PQ->Front > PQ->Rear)
    {
        printf("Queue is empty!!\n");
        return;
    }
    printf("Front most item of the queue is : %d\n",*(PQ->items + PQ->Front));
}

void QRear(QUE *PQ)
{
    if(PQ->Front >  PQ->Rear)
    {
        printf("Queue is empty!!\n");
         return;
    }
    printf("Last element of the queue is %d\n", *(PQ->items + PQ->Rear));
}