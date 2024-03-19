#include <stdio.h>
#include<stdlib.h>

struct node
{
    int info;
    struct node *RL;
    struct node *LL;
};

typedef struct node *NODE;

NODE createNode();
void InsertFront(NODE);
void Display(NODE);
void InsertRear(NODE);
void DeleteFront(NODE);
void DeleteRear(NODE);
NODE SearchByKey(NODE);
NODE SearchByPosition(NODE);
void InsertByPosition(NODE);
void InsertByOrder(NODE);
void DeleteByKey(NODE);
void DeleteByPosition(NODE);
void Reverse(NODE);
void Sort(NODE);
void Copy(NODE,NODE);

void main()
{
    NODE Header = (NODE)malloc(sizeof(struct node));
    NODE CopyHeader = (NODE)malloc(sizeof(struct node));
    NODE NS;
    int choice;
    Header->info = 0;
    Header->LL = Header->RL = Header;
    CopyHeader->info = 0;
    CopyHeader->RL = CopyHeader->LL = CopyHeader;
    
    for(;;)
    {
        printf("\nEnter your choice:\n1:Insert by front\n2:Display\n3:Insert by rear\n4:Delete by front\n5:Delete by rear\n6:Search by key\n7:Search by position\n8:Insert by position\n9:Insert by order\n10:Delete by key\n11:Delete by position\n12:Reverse\n13:Sort\n14:Copy\n");
        scanf("%d",&choice);
        
        switch(choice)
        {
            case 1: InsertFront(Header); Display(Header); break;
            case 2: Display(Header); break;
            case 3: InsertRear(Header); Display(Header); break;
            case 4: DeleteFront(Header); Display(Header); break;
            case 5: DeleteRear(Header); Display(Header); break;
            case 6: if(Header->info == 0)
                    {
                        printf("List is empty!!\n");
                        break;
                    }
                    NS = SearchByKey(Header);
                    if(NS == NULL)
                    {
                        printf("Key element does not exist!!\n");
                    }
                    else
                        printf("The key element %d is found\n",NS->info);
                    break;
            case 7: NS = SearchByPosition(Header);
                    if(NS == NULL)
                        printf("List is empty!!\n");
                    else
                        printf("Element present at the entered position is %d\n",NS->info);
                    break;
            case 8: InsertByPosition(Header); Display(Header); break;
            case 9: InsertByOrder(Header); Display(Header); break;
            case 10: DeleteByKey(Header); Display(Header); break;
            case 11: DeleteByPosition(Header); Display(Header); break;
            case 12: Reverse(Header); Display(Header); break;
            case 13: Sort(Header); Display(Header); break;
            case 14: Copy(Header,CopyHeader); Display(CopyHeader); break;
            default: exit(0);
        }
    }
}

NODE createNode()
{
    NODE NN = (NODE)malloc(sizeof(struct node));
    printf("Enter the data: ");
    scanf("%d",&NN->info);
    NN->RL = NN->LL = NN;
}

void InsertFront(NODE H)
{
    NODE NN = createNode();
    NN->RL = H->RL;
    NN->LL = H;
    H->RL = NN;
    NN->RL->LL = NN;
    H->info++;
}

void Display(NODE H)
{
    NODE TP;
    if(H->info == 0)
    {
        printf("List is empty!!\n");
        return;
    }
    TP = H->RL;
    printf("Entered elements are: \n");
    while(TP != H)
    {
        printf("%d\t",TP->info);
        TP = TP->RL;
    }
}

void InsertRear(NODE H)
{
    NODE NN = createNode();
    NN->RL = H;
    NN->LL = H->LL;
    H->LL = NN;
    NN->LL->RL = NN;
    H->info ++;
}

void DeleteFront(NODE H)
{
    NODE FN;
    if(H->info == 0)
    {
        printf("List is empty!!\n");
        return;
    }
    FN = H->RL;
    H->RL = FN->RL;
    FN->RL->LL = H;
    H->info--;
    printf("Deleted element is %d\n",FN->info);
    free(FN);
}

void DeleteRear(NODE H)
{
    NODE LN;
    if(H->info == 0)
    {
        printf("List is empty!!\n");
        return ;
    }
    LN = H->LL;
    H->LL = LN->LL;
    LN->LL->RL = H;
    H->info --;
    printf("Deleted element is %d\n",LN->info);
    free(LN);
}

NODE SearchByKey(NODE H)
{
    NODE TP;
    int key;
   
    printf("Enter the key element: ");
    scanf("%d",&key);
    TP = H->RL;
    while(TP != H)
    {
        if(TP->info == key)
        {
            return TP;
        }
        TP = TP->RL;
    }
    return NULL;
}

NODE SearchByPosition(NODE H)
{
    NODE TP;
    int pos,count;
    if(H->info == 0)
    {
        return NULL;
    }
    do{
        printf("Enter a valid position between 1 and %d: ",H->info);
        scanf("%d",&pos);
    }while(pos<1 || pos>H->info);
    TP = H->RL;
    count = 1;
    while(count != pos)
    {
        TP = TP->RL;
        count++;
    }
    return TP;
}

void InsertByPosition(NODE H)
{
    NODE TP;
    int pos,count;
    NODE NN = createNode();
    do{
        printf("Enter a valid position between 1 and %d: ",H->info + 1);
        scanf("%d",&pos);
    }while(pos<1 || pos>H->info + 1);
    TP = H;
    count = 0;
    while(count < pos-1)
    {
        TP = TP->RL;
        count++;
    }
    NN->RL = TP->RL;
    NN->LL = TP;
    TP->RL = NN;
    NN->RL->LL = NN;
    H->info++;
}

void InsertByOrder(NODE H)
{
    NODE NN = createNode();
    NODE TP;
    TP = H->RL;
    while(TP != H && TP->info<NN->info)
    {
        TP = TP->RL;
    }
    NN->RL = TP;
    NN->LL = TP->LL;
    NN->LL->RL = NN;
    TP->LL = NN;
    H->info ++;
}

void DeleteByKey(NODE H)
{
    NODE TP;
    int key;
    if(H->info == 0)
    {
        printf("List is empty!!\n");
        return;
    }
    printf("Enter the key element: ");
    scanf("%d",&key);
    TP = H->RL;
    while(TP != H)
    {
        if(TP->info == key)
        {
            TP->LL->RL = TP->RL;
            TP->RL->LL = TP->LL;
            printf("Deleted element is %d\n",TP->info);
            free(TP);
            H->info--;
            return;
        }
        TP = TP->RL;
    }
    printf("Key is not found!!\n");
}

void DeleteByPosition(NODE H)
{
    NODE TP;
    int pos,count;
    if(H->info == 0)
    {
        printf("List is empty!!\n");
        return;
    }
    do{
        printf("Enter a valid position between 1 and %d: ",H->info);
        scanf("%d",&pos);
    }while(pos<1 || pos>H->info);
    count = 1;
    TP = H->RL;
    while(count != pos)
    {
        TP = TP->RL;
        count++;
    }
    TP->LL->RL = TP->RL;
    TP->RL->LL = TP->LL;
    printf("Deleted element is %d\n",TP->info);
    H->info --;
    free(TP);
}

void Reverse(NODE H)
{
    NODE FP,BP;
    int i,temp;
    FP = H->RL;
    BP = H->LL;
    for(i=1;i<=H->info/2;i++)
    {
        temp = FP->info;
        FP->info = BP->info;
        BP->info = temp;
        BP = BP->LL;
        FP = FP->RL;
    }
    printf("Reversed elements are: \n");
}

void Sort(NODE H)
{
    NODE TP;
    int i,j,temp;
    for(i=0;i<H->info - 1;i++)
    {
        TP = H->RL;
        for(j=0;j<H->info - 1-i;j++)
        {
            if(TP->info > TP->RL->info)
            {
                temp = TP->info;
                TP->info = TP->RL->info;
                TP->RL->info = temp;
            }
            TP = TP->RL;
        }
    }
}

void Copy(NODE H,NODE CH)
{
    NODE TP,NN;
    TP = H->RL;
    while(TP != H)
    {
        NN = (NODE)malloc(sizeof(struct node));
        NN->info = TP->info;
        NN->RL = CH;
        NN->LL = CH->LL;
        CH->LL = NN;
        NN->LL->RL = NN;
        CH->info ++;
        TP = TP->RL;
    }
    printf("Copied list:\n");
}