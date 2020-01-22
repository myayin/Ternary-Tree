#include<stdlib.h>
#include<stdio.h>
#include <stdio.h> 
#include <dirent.h> 
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<locale.h>
#include <dirent.h> 

struct tree {
int data;
struct tree * right, * left, * middle;
};
typedef struct tree node;

void insert(node ** tree, int val)
{
    node *temp = NULL;
    if(!(*tree))
    {
        temp = (node *)malloc(sizeof(node));
        temp->left = temp->right =temp->middle= NULL;
        temp->data = val;
        *tree = temp;
        return;
    }

    if(val < (*tree)->data)
    {
        insert(&(*tree)->left, val);
    }
    else if(val > (*tree)->data&&val<=((*tree)->data)*(*tree)->data)
    {
        insert(&(*tree)->middle, val);
    }
     else if(val > ((*tree)->data)*((*tree)->data))
    {
        insert(&(*tree)->right, val);
    }
}

void insert2(node * tree, node *tree2)
{
if (tree2)	{

    
	insert(&(tree),tree2->data);
	insert2(tree,tree2->middle);
	insert2(tree,tree2->right);
	insert2(tree,tree2->left);
}
	
	
}
void print_postorder(node * tree)
{
    if (tree)
    {
        print_postorder(tree->left);
         print_postorder(tree->middle);
        print_postorder(tree->right);
        printf("%d\n",tree->data);
        
    }
}

void deltree(node * tree)
{
    if (tree)
    {
        deltree(tree->left);
        deltree(tree->right);
        free(tree);
    }
}
 node* Delete( node *root, int data) {
  if (root == NULL) {
     return NULL;
  }
  if (data < root->data) {  // data is in the left sub tree.
      root->left = Delete(root->left, data);
  } else if (data > (root->data)*(root->data)) { // data is in the right sub tree.
      root->right = Delete(root->right, data);
  } 
  else if (data > root->data&&data<=(root->data)*(root->data)) { // data is in the right sub tree.
      root->middle = Delete(root->middle, data);
  }
	  else {
     // case 1: no children
     if (root->left == NULL && root->right == NULL&&root->middle == NULL) {
        delete(root); // wipe out the memory, in C, use free function
        root = NULL;
     }
     // case 2: one child (right)
     else if (root->left == NULL&&root->middle == NULL) {
        node *temp = root; // save current node as a backup
        root = root->right;
        delete temp;
     }
     // case 3: one child (left)
     else if (root->right == NULL&&root->middle == NULL) {
       node *temp = root; // save current node as a backup
       if(root->left)
        root = root->left;
        delete temp;
     }
    else if (root->right == NULL&&root->left == NULL) {
       node *temp = root; // save current node as a backup
        root = root->middle;
        delete temp;
     }
     // case 4: two children
      else if (root->right == NULL&&root->left != NULL&&root->middle != NULL) {
       node *temp = root; // save current node as a backup
        root = root->middle;
        root->left=temp->left;
        root->middle=NULL;
        root->right=NULL;
        delete temp;
     }
       else if (root->right != NULL&&root->left == NULL&&root->middle != NULL) {
       node *temp = root; // save current node as a backup
        root = root->right;
        root->left=temp->middle;
        root->middle=NULL;
        root->right=NULL;
        delete temp;
     }
     else if (root->right != NULL&&root->left != NULL&&root->middle == NULL) {
       node *temp = root; // save current node as a backup
        root = root->right;
        root->left=temp->left;
        root->middle=NULL;
        root->right=NULL;
        delete temp;
     }
     // case 4: three children
      else if (root->right != NULL&&root->left != NULL&&root->middle != NULL) {
       node *temp = root; // save current node as a backup
        root = root->middle;
       node *temp2=temp->left;
       node *temp3=temp->right;
       
       insert2(root->left,temp->left);
       if(temp->right->data<=(root->data)*(root->data))
       {
       insert2(root->middle,temp->right);	
	   }
	    if(temp->right->data>(root->data)*(root->data))
       {
       insert2(root->right,temp->right);	
	   }
        delete temp;
        
     }
     
    
  }
  return root; // parent node can update reference
}

node* search(node ** tree, int val,int *depth,int * parent,int * childL, int * childM,int * childR)
{
	 
    if(!(*tree))
    {
        return NULL;
    }

    if(val < (*tree)->data)
    { if((*tree)->left->data==val){
    		(*parent)=(*tree)->data;}
	  (*depth)++;
        search(&(*tree)->left, val,&(*depth),&(*parent),&(*childL),&(*childM),&(*childR));
      
    }
    else if(val > (*tree)->data&&val<=(*tree)->data*(*tree)->data)
    {if((*tree)->middle->data==val){
    		(*parent)=(*tree)->data;}
    		
		
	 (*depth)++;
       search(&(*tree)->middle, val,&(*depth),&(*parent),&(*childL),&(*childM),&(*childR));
        
    }
     else if(val > ((*tree)->data)*((*tree)->data))
    {  if((*tree)->right->data==val){
    		(*parent)=(*tree)->data;}
	(*depth)++;
        search(&(*tree)->right, val,&(*depth),&(*parent),&(*childL),&(*childM),&(*childR));
        
    }
    else if(val == (*tree)->data)
    {if((*tree)->left){
    	(*childL)=(*tree)->left->data;
	}
	if((*tree)->middle){
    	(*childM)=(*tree)->middle->data;
	}
		if((*tree)->right){
    	(*childR)=(*tree)->right->data;
	}
    
        return *tree;
    }
   
}

int main()
{
	FILE *file;
    node *root;
    node *tmp;
    //int i;

    root = NULL;
   file= fopen("input.txt", "r"); 
   int number;

while(!feof(file)){
	fscanf(file,"%d",&number);
    insert(&root, number);}


    /* Printing nodes of tree */
  
    printf("Post Order Display\n");
    print_postorder(root);
   int num;
  printf("%s","Please enter  integer for removing");
   scanf("%d",&num);
   root = Delete(root, num);
   
  printf("Post Order Display\n");
   print_postorder(root);

    /* Search node into tree */
 
  int searchedWord;
  printf("%s","Please enter integer  for searching ");
   scanf("%d",&searchedWord);
   int depth=0;
   int parent=0;
int childL=0;
int childM=0;
int childR=0;
    /* Search node into tree */
   tmp = search(&root, searchedWord, &depth,&parent,&childL,&childM,&childR);
  
   
    if (tmp)
   {
        printf("Searched node=%d\n", tmp->data);
         printf("%s%d\n","depth is",depth);
   printf("%s%d\n","parent of child",parent);
   printf("%s\t%s\t%s\n"," Left Child","Middle Child" ,"Right Child");
   printf("%d\t\t%d\t\t%d\n",childL,childM ,childR);
    }
    else
    {
        printf("Data Not found in tree.\n");
    }

   
}
