/*Circular Queue with dynamic memory allocation*/

#include<stdio.h>
#include<stdlib.h>
int size;

struct Queue
{
    int *items;
    int Front, Rear, count;
};
typedef struct Queue QUE;

void Insert(QUE *);
void Delete(QUE *);
void Display(QUE *);
void QFront(QUE *);
void QRear(QUE *);

void main()
{
    QUE Q;
    Q.Front = 0;
    Q.Rear = -1;
    Q.count = 0;
    int choice;
    
    printf("Enter the size of the queue: ");
    scanf("%d",&size);
    Q.items = (int *)malloc(size*sizeof(int));
    
    for(;;)
    {
        printf("\nEnter your choice:\n1:Insert\n2:Delete\n3:Display\n4:Display first item of the queue\n5:Display last item of the queue\n");
        scanf("%d", &choice);
        
        switch(choice)
        {
            case 1: Insert(&Q); Display(&Q); break;
            case 2: Delete(&Q); Display(&Q); break;
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
    if(PQ->count == size)
    {
        printf("Queue is full!! Do you want to go for reallocation??\n");
        printf("Enter your choice:\n1:Yes\n2:No\n");
        scanf("%d",&choice);
        if(choice == 1)
        {
            size = size*2;
            PQ->items = (int *)realloc(PQ->items,size*sizeof(int));
        }
        else
        {
            printf("Insertion is not possible!!\n");
            return;
        }
    }
    printf("Enter the item to be inserted: ");
    scanf("%d",&item);
    PQ->Rear = (PQ->Rear + 1) % size;
    *(PQ->items + PQ->Rear) = item;
    PQ->count++;
}

void Delete(QUE *PQ)
{
    if(PQ->count == 0)
    {
        printf("Queue is empty!!\n");
        return;
    }
    printf("Deleted element is %d\n",*(PQ->items + PQ->Front));
    PQ->Front = (PQ->Front + 1) % size;
    PQ->count--;
}

void Display(QUE *PQ)
{
    int i,j;
    if(PQ->count == 0)
    {
        printf("Queue is empty!!\n");
        return;
    }
    j = PQ->Front;
    printf("Entered elements are: \n");
    for(i=1; i<=PQ->count; i++)
    {
        printf("%d\t",*(PQ->items + j));
        j = (j+1) % size;
    }
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