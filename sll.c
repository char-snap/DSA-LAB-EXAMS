#include <stdio.h>
#include <stdlib.h>

struct node
{
    int info;
    struct node *link;
};

typedef struct node *NODE;

NODE createNode();
void InsertFront(NODE);
void Display(NODE);
void InsertRear(NODE);
void DeleteFront(NODE);
void DeleteRear(NODE);
void SearchByKey(NODE);
void SearchByPosition(NODE);
void InsertByPosition(NODE);
void InsertByOrder(NODE);
void DeleteByPosition(NODE);
void DeleteByKey(NODE);
void Reverse(NODE);
void Sort(NODE);
void Copy(NODE, NODE);

void main()
{
    NODE Header, CopyHeader;
    int choice;
    Header = (NODE)malloc(sizeof(struct node));
    Header->info = 0;
    Header->link = Header;
    CopyHeader = (NODE)malloc(sizeof(struct node));
    CopyHeader->info = 0;
    CopyHeader->link = CopyHeader;

    for (;;)
    {
        printf("\nEnter your choice:\n1:Insert by front\n2:Display\n3:Insert by rear\n4:Delete by front\n5:Delete bt rear\n6:Search by key\n7:Search by position\n8:Insert by position\n9:Insert by order\n10:Delete by position\n11:Delete by key\n12:Reverse\n13:Sort\n14:Copy\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            InsertFront(Header);
            Display(Header);
            break;
        case 2:
            Display(Header);
            break;
        case 3:
            InsertRear(Header);
            Display(Header);
            break;
        case 4:
            DeleteFront(Header);
            Display(Header);
            break;
        case 5:
            DeleteRear(Header);
            Display(Header);
            break;
        case 6:
            SearchByKey(Header);
            break;
        case 7:
            SearchByPosition(Header);
            break;
        case 8:
            InsertByPosition(Header);
            Display(Header);
            break;
        case 9:
            InsertByOrder(Header);
            Display(Header);
            break;
        case 10:
            DeleteByPosition(Header);
            Display(Header);
            break;
        case 11:
            DeleteByKey(Header);
            Display(Header);
            break;
        case 12:
            Reverse(Header);
            Display(Header);
            break;
        case 13:
            Sort(Header);
            Display(Header);
            break;
        case 14:
            Copy(Header, CopyHeader);
            Display(CopyHeader);
            break;
        default:
            exit(0);
        }
    }
}

NODE createNode()
{
    NODE NN = (NODE)malloc(sizeof(struct node));
    printf("Enter the data: ");
    scanf("%d", &NN->info);
    NN->link = NN;
    return NN;
}

void InsertFront(NODE H)
{
    NODE NN = createNode();
    NN->link = H->link;
    H->link = NN;
    H->info++;
}

void Display(NODE H)
{
    NODE TP;
    if (H->info == 0)
    {
        printf("List is empty!!\n");
        return;
    }
    TP = H->link;
    printf("Entered elements are: \n");
    while (TP != H)
    {
        printf("%d\t", TP->info);
        TP = TP->link;
    }
}

void InsertRear(NODE H)
{
    NODE TP;
    NODE NN = createNode();
    TP = H->link;
    while (TP->link != H)
        TP = TP->link;
    NN->link = TP->link;
    TP->link = NN;
    H->info++;
}

void DeleteFront(NODE H)
{
    NODE FN;
    if (H->info == 0)
    {
        printf("List is empty!!\n");
        return;
    }
    FN = H->link;
    H->link = FN->link;
    printf("Deleted element is %d\n", FN->info);
    free(FN);
    H->info--;
}

void DeleteRear(NODE H)
{
    NODE LN, PL;
    if (H->info == 0)
    {
        printf("List is empty!!\n");
        return;
    }
    LN = H->link;
    PL = H;
    while (LN->link != H)
    {
        PL = LN;
        LN = LN->link;
    }
    PL->link = LN->link;
    printf("Deleted element is %d\n", LN->info);
    free(LN);
    H->info--;
}

void SearchByKey(NODE H)
{
    int key;
    NODE TP;
    if (H->info == 0)
    {
        printf("List is empty!!\n");
        return;
    }
    printf("Enter the key element: ");
    scanf("%d", &key);
    TP = H->link;
    while (TP != H)
    {
        if (TP->info == key)
        {
            printf("key element %d is found\n", TP->info);
            return;
        }
        TP = TP->link;
    }
    printf("Key element does not exist!!\n");
}

void SearchByPosition(NODE H)
{
    int pos, count = 1;
    NODE TP;
    if (H->info == 0)
    {
        printf("List is empty!!\n");
        return;
    }
    do
    {
        printf("Enter a valid position between 1 and %d: ", H->info);
        scanf("%d", &pos);
    } while (pos < 1 || pos > H->info);
    TP = H->link;
    while (count < pos)
    {
        TP = TP->link;
        count++;
    }
    printf("Element at position %d is %d\n", pos, TP->info);
}

void InsertByPosition(NODE H)
{
    int pos, count = 0;
    NODE NN = createNode();
    NODE TP;
    do
    {
        printf("Enter a valid position between 1 and %d: ", H->info + 1);
        scanf("%d", &pos);
    } while (pos < 1 || pos > H->info + 1);
    TP = H;
    while (count < pos - 1)
    {
        TP = TP->link;
        count++;
    }
    NN->link = TP->link;
    TP->link = NN;
    H->info++;
}

void InsertByOrder(NODE H)
{
    NODE NN = createNode();
    NODE TP, PN;
    TP = H->link;
    PN = H;
    while (TP != H && TP->info < NN->info)
    {
        PN = TP;
        TP = TP->link;
    }
    NN->link = TP;
    PN->link = NN;
    H->info++;
}

void DeleteByPosition(NODE H)
{
    NODE TP, ND;
    int pos, count = 0;
    if (H->info == 0)
    {
        printf("List is empty!!\n");
        return;
    }
    do
    {
        printf("Enter a valid position between 1 and %d: ", H->info);
        scanf("%d", &pos);
    } while (pos < 1 || pos > H->info);
    TP = H;
    while (count < pos - 1)
    {
        TP = TP->link;
        count++;
    }
    ND = TP->link;
    TP->link = ND->link;
    printf("Deleted element is %d\n", ND->info);
    free(ND);
    H->info--;
}

void DeleteByKey(NODE H)
{
    int key;
    NODE TP, PN;
    if (H->info == 0)
    {
        printf("List is empty!!\n");
        return;
    }
    printf("Enter the key element: ");
    scanf("%d", &key);
    TP = H->link;
    PN = H;
    while (TP != H)
    {
        if (TP->info == key)
        {
            PN->link = TP->link;
            printf("Deleted element is %d\n", TP->info);
            free(TP);
            H->info--;
            return;
        }
        PN = TP;
        TP = TP->link;
    }
    printf("Key element does not exist!!\n");
}

void Reverse(NODE H)
{
    NODE LN, TN, TP;
    if (H->info == 0)
    {
        printf("List is empty!!\n");
        return;
    }
    TN = H;
    TP = H->link;
    while (TP != H)
    {
        LN = TP;
        TP = TP->link;
        LN->link = TN;
        TN = LN;
    }
    H->link = LN;
}

void Sort(NODE H)
{
    int i, j, temp;
    NODE TP = H->link;
    for (i = 0; i < H->info - 1; i++)
    {
        TP = H->link;
        for (j = 0; j < H->info - 1 - i; j++)
        {
            if (TP->info > TP->link->info)
            {
                temp = TP->info;
                TP->info = TP->link->info;
                TP->link->info = temp;
            }
            TP = TP->link;
        }
    }
}

void Copy(NODE H, NODE CH)
{
    NODE TP, NN, PN;
    TP = H->link;
    PN = CH;
    while (TP != H)
    {
        NN = (NODE)malloc(sizeof(struct node));
        NN->info = TP->info;
        NN->link = PN;
        PN->link = NN;
        PN = NN;
        TP = TP->link;
        CH->info++;
    }
    PN->link = CH;
    printf("Copied list:\n");
}