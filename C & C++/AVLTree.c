#include <stdio.h>
#include <stdlib.h>
#define max(X, Y)  ((X) > (Y) ? (X) : (Y))

struct node
{	
	int data;
	int balance;
	struct node* parent;
	struct node* left;
	struct node* right;	
}*root;

//FUNCTION DEFINITIONS
struct node* newnode(struct node*ptr, int item); //create node
int height(struct node* node); //calculate height
int getHeight(struct node* root); //return current height 
int balance(struct node* root); //balance
void balance_order(struct node* root); //get balance 
void insert(struct node** root, int k); //insert nodes and if it isn't ok call rotate
void rotate(struct node** root, struct node* p, struct node* temp); // LL-LR-RR-RL rotations of avl
void display(struct node* root); //min to max display
void displayAsTree( struct node* root); //create levels
void displayLevel(struct node* root, int level); //show parents and children

struct node* newnode(struct node*ptr, int item)
{
	ptr = (struct node *)malloc(sizeof(struct node));
	ptr->data = item;
	ptr->balance = 0;
	ptr->left = NULL;
	ptr->right = NULL;
	ptr->parent = NULL;
	
	return ptr;
}

void display(struct node* root) 
{	
	if(root != NULL) 
	{
		display(root->left);
		printf("%d\n", root->data);
		display(root->right);	
	}
	else 
		return;
}

void displayAsTree(struct node* root) 
{
    int i = 0;
    while (i <= height(root))
	{  	
    	displayLevel(root, i);
    	printf("\n");
		i++;
	}    
}

void displayLevel(struct node* root, int level)
{
	
    if (root == NULL)
        return;
    if (level == 1)
	{    		
    	if(root->parent == NULL)
		{   
			printf("%d ", root->data); 		
    		printf("(%d B)", root->balance);
    		return;
		}
		else
		{
			if(root == root->parent->left)
			{	
				printf("%d ", root->data);
				printf("(%d L)", root->parent->data);
				printf(" (%d B) ", root->balance);					
			}
				
    		if(root == root->parent->right)
    		{ 	
				printf("%d ", root->data);
				printf("(%d R)", root->parent->data);
				printf(" (%d B) ", root->balance);
			}
		}
	}
     
    else if (level > 1)
	{
        displayLevel(root->left, level-1);
        displayLevel(root->right, level-1);
    }    
}

int height(struct node* node)
{
	int leftHeight;
	int rightHeight;
	int result;
	
	if (node==NULL)
        return 0;
        
    else if(node != NULL)
    {    
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        result = leftHeight > rightHeight ? leftHeight+1 : rightHeight+1;
        return result;
    }
}

int getHeight(struct node* root)
{	
	int height;
	
	if(root == NULL)	
		return 0;
	if(root != NULL)
		height = max(getHeight(root->left),getHeight(root->right));
	return height+1;	
}

int balance(struct node* root)
{	
	int leftHeight;
	int rightHeight;
	int noodBalance;
	
	if(root == NULL)
		return 0;
	
	else if(root != NULL)
	{
		leftHeight = getHeight(root->left);
		rightHeight = getHeight(root->right);
		noodBalance = leftHeight - rightHeight;
		root->balance = noodBalance;
	}
	return (root->balance);
}

void balance_order(struct node* root)
{	
	if(root == NULL) 
		return;
	else if (root != NULL)
	{
		balance_order(root->left);
		balance(root);
		balance_order(root->right);
	}	
}

void insert(struct node** root, int item)
{	
	struct node* ptr;	
	struct node* nodeptr; 
	struct node* parentptr;
	
	ptr=newnode(ptr, item);
	
	if(*root == NULL) 
		*root = ptr;
	
	else
	{		
		parentptr = NULL;
		nodeptr = *root;
		
		while(nodeptr != NULL)
		{			
			parentptr = nodeptr;
			if(item < nodeptr->data) 
				nodeptr = nodeptr->left;
			else 
				nodeptr = nodeptr->right;			
		}
		
		if(item < parentptr->data)
		{			
			parentptr->left = ptr;
			ptr->parent = parentptr;
		}
		
		else
		{			
			parentptr->right = ptr;
			ptr->parent = parentptr;			
		}		
	
	balance_order(*root);	
	struct node* temp = ptr->parent;
	
	while(temp)
	{		
		int b = balance(temp);
		if(b >= 2 || b <= -2)
		{		
			rotate(root,temp,ptr);
		}	
		temp = temp->parent;	
	}
	
	balance_order(*root);	
	}
}

void rotate(struct node** root, struct node* parentPtr, struct node* temp)
{
	if(parentPtr->data < temp->data) 
	{		
		struct node* c = parentPtr->right;
		
		if(c->data < temp->data) //RR
		{					
			struct node* pp = parentPtr->parent;
			struct node* c = parentPtr->right;
			struct node* cl = c->left;
		
			if(!pp)
			{		
				*root = c;
				c->parent = NULL;
			}
		
			else
			{		
				c->parent = pp;
				if(c->data < pp->data) pp->left = c;
				else pp->right = c;
			}
		
			c->left = parentPtr;
			parentPtr->parent = c;
			parentPtr->right = cl;
		}

		else if(c->data > temp->data) //RL
		{					
			struct node* pp = parentPtr->parent;
			struct node* c = parentPtr->right;
			struct node* cr = c->right;
		
			if (pp)
			{		
				temp->parent = pp;
				if(temp->data < pp->data) pp->left = temp;
				else pp->right = temp;
			}
		
			else
			{		
				*root = temp;
				temp->parent = NULL;
			}
		
			temp->left = parentPtr;
			parentPtr->parent = temp;
			temp->right = c;
			c->parent = temp;
			parentPtr->right = NULL;
			c->left = NULL;	
		}
	}

	else if(parentPtr->data > temp->data) //LR
	{			
		struct node* c = parentPtr->left;

		if(c->data < temp->data)
		{
			struct node* pp = parentPtr->parent;
			struct node* c = parentPtr->left;
			struct node* nl = temp->left;
			struct node* nr = temp->right;
			
			if(!pp)
			{		
				*root = temp;
				temp->parent = NULL;	
			}

			else
			{		
				temp->parent = pp;
				if(temp->data < pp->data)	pp->left = temp;
				else pp->right = temp;		
			}
			
			temp->right = parentPtr;
			parentPtr->parent = temp;
			temp->left = c;
			c->parent = temp;
			parentPtr->left = nl;
			c->right = nr;
		}
		
		else if(c->data > temp->data) //LL
		{				
			struct node* pp = parentPtr->parent;
			struct node* c = parentPtr->left;
			struct node* cr = c->right;
		
			if(!pp)
			{		
				*root = c;
				c->parent = NULL;
			}
		
			else
			{		
				c->parent = pp;
				if(c->data < pp->data) pp->left = c;
				else pp->right = c;	
			}
		
			c->right = parentPtr;
			parentPtr->parent = c;
			parentPtr->left = cr;
		}		
	}	
}

int main()
{
	int data;
	
	while(scanf("%d", &data)!= EOF)
	{		
		if(data == -1) 
			break;
		else
			insert(&root,data);		
	}
	
	display(root);
	displayAsTree(root);
	return 0;
}
