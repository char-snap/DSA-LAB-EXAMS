#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
    struct node *prev;
} NODE;

typedef struct List
{
    int count;
    struct node *head;
} LIST;

NODE *createnode(int val)
{
    NODE *n = (NODE *)malloc(sizeof(NODE));
    if (n == NULL)
    {
        printf("Memory allocation failed:");
        return NULL;
    }
    n->data = val;
    n->next = NULL;
    n->prev = NULL;

    return n;
}

void display(LIST *list)
{

    if (list->head == NULL)
    {
        printf("List is empty");
        return;
    }
    NODE *cur = list->head;
    do
    {
        printf("%d->", cur->data);
        cur = cur->next;
    } while (cur != list->head);
}

void insertbyorder(LIST *list, int val)
{
    NODE *n = createnode(val);
    if (list->head == NULL)
    {
        list->head = n;
        n->next = n;
        n->prev = n;
    }
    else if (val <= list->head->data)
    {
        n->next = list->head;
        n->prev = list->head->prev;
        list->head->prev->next = n;
        list->head->prev = n;
        list->head = n;
        list->count++;
    }
    else
    {
        NODE *cur = list->head;
        while (cur->next != list->head && cur->next->data < val)
            cur = cur->next;

        n->next = cur->next;
        n->prev = cur;
        cur->next->prev = n;
        cur->next = n;
        list->count++;
    }
}

void deletebykey(LIST *list, int key)
{
    if (list->head == NULL)
    {
        printf("List is empty");
        return;
    }

    NODE *cur = list->head;
    NODE *temp = NULL;
    if (cur->data == key)
    {
        if (list->count == 1)
        {
            free(list->head);
            list->head = NULL;
            return;
        }
        else
        {
            NODE *temp = list->head;
            list->head->prev->next = list->head->next;
            list->head->next->prev = list->head->prev;
            list->head = list->head->next;
            free(temp);
            return;
        }
    }

    do
    {
        if (cur->data == key)
        {
            temp = cur;
            cur->prev->next = cur->next;
            cur->next->prev = cur->prev;
            free(temp);
            return;
        }
        cur = cur->next;

    } while (cur != list->head);

    printf("%d not found", key);
}





void deletebypos(LIST *list, int pos)
{   if(pos<1 || pos>list->count)
    {
        printf("Invalid position");
        return;
    }
    if (list->head == NULL)
    {
        printf("List is empty");
        return;
    }

    NODE *cur = list->head;
    NODE *temp = NULL;
    if (pos==1)
    {
        if (list->count == 1)
        {
            free(list->head);
            list->head = NULL;
            return;
        }
        else
        {
            NODE *temp = list->head;
            list->head->prev->next = list->head->next;
            list->head->next->prev = list->head->prev;
            list->head = list->head->next;
            free(temp);
            return;
        }
    }

    else
    {
        for(int i=1;i<pos;i++)
        { cur = cur->next;
           
        }
         temp = cur;
            cur->prev->next = cur->next;
            cur->next->prev = cur->prev;
            free(temp);
            return;
       

    } 

   
}

void searchbypos(LIST *list, int pos)
{
    if (pos < 1 || pos > list->count+1)
    {
        printf("Invalid position");
        return;
    }
    NODE *cur = list->head;
    for (int i = 1; i < pos; i++)
    {
        cur = cur->next;
    }
    printf("%d", cur->data);
}



void main()
{
    int val, position, key;
    LIST *list = (LIST *)malloc(sizeof(LIST));
    list->head = NULL;
    list->count = 0;

    for (;;)
    {
        int choice;
        printf("Enter the choice:");
        scanf("%d", &choice);
        switch (choice)
        {

        case 1:
            printf("Enter the value to insert:\n");
            scanf("%d", &val);
            insertbyorder(list, val);
            display(list);
            break;

        case 2:
            printf("Enter key to delete");
            scanf("%d", &key);
            deletebykey(list, key);
            display(list);break;

        case 3:
            printf("Enter position to delete");
            scanf("%d", &position);
            deletebypos(list, position);
            display(list);break;

        case 4:
            printf("Enter position to search");
            scanf("%d", &position);
            searchbypos(list, position);
            break;
            

        }
    }
}