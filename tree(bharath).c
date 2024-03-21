#include<stdio.h>
#include<stdlib.h>
struct node
{
  int info;
  struct node *LL,*RL;
  };
  typedef struct node *NODE;
  NODE Construct(NODE);
  void Display(NODE);
 NODE Search(NODE, int, NODE*);
 void Inorder(NODE);
  void Preorder(NODE);
void Postorder(NODE);
NODE Delete(NODE);
NODE Minimum(NODE);
NODE Maximum(NODE);
int height(NODE);
int count(NODE);
int countleaf(NODE);
int countnonleaf(NODE);
int max(NODE ,NODE );
  void main()
  {
    int ch,x,key;
    NODE Root = NULL, NS=NULL, PN=NULL,M=NULL ;
    for(;;)
      {
	printf("enter choice:\n1: Construction\n2:Display\n3:Search\n4:Delete\n5:Minimum\n6:Maximum\n7:countnodes\n8:count leaf\n9:countnonleaf\n10:Height\n");
	scanf("%d", &ch);
	 switch(ch)
	 {
	   case 1:  Root =Construct(Root);  break;
	    case 2:  Display(Root);  break;
	   case 3:if(Root==NULL)
	   {
	       printf("Tree is empty\n");
	       break;
	   }
	       printf("enter the key of node to be searched\n");
		     scanf("%d", &key);
		     if(Root->info == key)
		      printf("Searching node info = %d and No parent for the root n",Root->info);
		     else
		     {
		     NS=Search(Root,key, &PN);
		     if(NS==NULL)
		       printf("Node doens't exist\n");
		     else
		      printf("Searching node info = %d and its parent is:%d \n",NS->info, PN->info);
		      }
		     break;
	      case 4: Root =Delete(Root); Display(Root); break;
	      case 5:if(Root==NULL)
	   {
	       printf("Tree is empty\n");
	       break;
	   }
	          M=Minimum(Root);printf("Minimum=%d\n",M->info);break;

        case 6:if(Root==NULL)
	   {
	       printf("Tree is empty\n");
	       break;
	   }
            M=Maximum(Root);printf("Maximum=%d\n",M->info);break;
        case 7:x=count(Root);
                printf("Number of nodes:%d\n",x);
                break;
        case 8:x=countleaf(Root);
                printf("Number of leaf:%d\n",x);
                break;
        case 9:x=countnonleaf(Root);
                printf("Number of non leaf:%d\n",x);
                break;
        case 10:x=height(Root);
                printf("Height=%d\n",x-1);
                break;
	    default: exit(0);
	 }
      }
  }

  NODE Construct(NODE R)
  {
     NODE NN, TP, PN;
     int ch;
     for(;;)
     {
       printf("enter 1 to continue inserting nodes, otherwise -1\n");
       scanf("%d", &ch);
       if(ch!=-1)
       {

	  NN = (NODE) malloc(sizeof(struct node));
	  printf("enter info:");
	  scanf("%d", &NN->info);
	  NN->LL=NN->RL=NULL;
	    if(R==NULL)
           R=NN;
else{
		TP = R;
		PN = NULL;
	while(TP!=NULL)
	{
	PN = TP;
	if(NN->info<TP->info)
		TP = TP->LL;
	else
	  TP = TP->RL;
	}

     if(NN->info<PN->info)
      PN->LL = NN;
      else
      PN->RL = NN;
   }
  }
  else break;
 }
   return R;
  }

 void Display(NODE R)
 {
    if(R==NULL)
    {
      printf("Tree empty\n");
      return;
    }
    printf("\nInorder Traversal is: ");
    Inorder(R);
    printf("\nPreorder Traversal is: ");
    Preorder(R);
    printf("\nPostorder Traversal is: ");
    Postorder(R);
}
void Inorder(NODE R)
{
  if(R==NULL) return;
  Inorder(R->LL);
  printf("%d  ", R->info);
  Inorder(R->RL);
}
void Preorder(NODE R)
{
  if(R==NULL) return;
   printf("%d  ", R->info);
  Preorder(R->LL);
  Preorder(R->RL);
}
void Postorder(NODE R)
{
  if(R==NULL) return;
  Postorder(R->LL);
  Postorder(R->RL);
  printf("%d  ", R->info);
}


 NODE Search(NODE R,int key,  NODE *PN)
 { NODE NS=NULL;
   if(R->info==key)
   {
     NS = R;
    }
   if(NS==NULL)

  {

   *PN = R;
   if(key<R->info)
     NS = Search(R->LL, key,PN);
   else

    NS = Search(R->RL, key, PN);
  }
  return NS;
 }

NODE Delete(NODE R)
 {  int key;
   NODE  ND=NULL, PN=NULL, IS, ISP;
   NODE TP;
   if(R==NULL)
    return NULL;
   printf("enter key of the node to be deleted:\n");
   scanf("%d", &key);
   if(R->info==key && R->LL==NULL && R->RL==NULL)
    {
      printf("deleted: %d\n", R->info);
      free(R);
      return NULL;

   }
   ND = Search(R, key, &PN);
   if(R->info==key)
   {
    printf("deleted: %d\n", R->info);
        if(ND->LL!=NULL && ND->RL==NULL || ND->LL==NULL && ND->RL!=NULL)
   {
     if(ND->RL==NULL)
      TP = ND->LL;
	else
      TP = ND->RL;
      printf("deleted:%d\n", ND->info);
       free(ND);
       return TP;
 }
 else goto label;
       return R;
   }
   if(ND==NULL)
   {
      printf("Node doesn't exist\n");
      return R;
   }

   printf("node to be deleted is %d and ites parent is:%d\n", ND->info, PN->info);
   if(ND->LL==NULL && ND->RL==NULL)
   {
     if(ND==PN->LL)
       PN->LL=NULL;
     else
       PN->RL=NULL;
       printf("deleted:%d\n", ND->info);
       free(ND);
     return R;
   }
   else
   if(ND->LL!=NULL && ND->RL==NULL || ND->LL==NULL && ND->RL!=NULL)
   {
     if(ND->RL==NULL)
      TP = ND->LL;
	else
      TP = ND->RL;
       if(ND==PN->RL)
	  PN->RL= TP;
       else
	    PN->LL=TP;

      printf("deleted:%d\n", ND->info);
       free(ND);
       return R;
 }
 else
 label:{
   IS=ND->RL;
    ISP = ND;
   while(IS->LL !=NULL)
   {
     ISP = IS;
     IS = IS->LL;
   }
   printf("deleted:%d \n",ND->info);
   ND->info = IS->info;
   if(IS->LL==NULL && IS->RL==NULL)
   {
     if( IS == ISP->LL)
	 ISP->LL = NULL;
     else
	  ISP->RL=NULL;
   }
   else
   {
     if( IS == ISP->LL)
	 ISP->LL = IS->RL;
     else
	  ISP->RL=IS->RL;
   }
   free(IS);
    return R;
 }
 }
NODE Maximum(NODE R)
{
 NODE RN = R;
 while(RN->RL!=NULL)
 RN=RN->RL;
 return RN;
}
NODE Minimum(NODE R)
{
 NODE LN = R;
 while(LN->LL!=NULL)
 LN=LN->LL;
 return LN;
}
int countnonleaf(NODE R)
{
    int count=0;
    if(R==NULL)
        return 0;
    if(R->LL!=NULL || R->RL!=NULL)
        count++;
    return count+countnonleaf(R->LL)+countnonleaf(R->RL);
}
int count(NODE R)
{
     int cnt=0;
    if(R==NULL)
        return 0;
    return (1+count(R->LL)+count(R->RL));
}
int countleaf(NODE R)
{
     int count=0;
    if(R==NULL)
        return 0;
    if(R->LL==NULL && R->RL==NULL)
        count++;
    return count+countleaf(R->LL)+countleaf(R->RL);
}
int height(NODE R)
{
if(R == NULL)
return 0;
return (1+max(height(R->LL),height(R->RL)));
}
int max(NODE R,NODE L)
{
    return((L>R)?L:R);
}