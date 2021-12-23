#include <iostream>
#include <queue>
#include <cstdlib>
using namespace std;

//Color definition of Red Black Tree
enum Color {RED, BLACK};
 
//structure of Red-Black Tree
struct node
{
    int data;
    int color;
    
    struct node *left = NULL;
    struct node *right = NULL;
    struct node *parent = NULL;
}*root;

//function definitions
    struct node* newnode(struct node*ptr, int &item);
    void insert(int &n);
    void colorize(struct node *&root, struct node *&ptr);
    void rotateLeft(struct node *&root, struct node *&ptr);
    void rotateRight(struct node *&root, struct node *&ptr);
    void displayAll(struct node* root, int level);
    void inorderDisplay(struct node *root);
    int height(struct node* node);
    struct node* insertRec(struct node* root, struct node *ptr);

//same with hw6
struct node* newnode(struct node* ptr, int &item)
{
    ptr = (struct node *)malloc(sizeof(struct node));
    ptr->data = item;
    ptr->left = NULL;
    ptr->right = NULL;
    ptr->parent = NULL;
    
    return ptr;
}

//same with hw6
void insert (int &data)
{
    struct node* ptr;
    ptr = newnode(ptr, data);
    root = insertRec(root, ptr);
    colorize(root, ptr);
}   

void colorize(struct node *&root, struct node *&ptr)
{
    struct node *parentPtr = NULL;
    struct node *grandparentPtr = NULL;
 
    while ((ptr != root) && (ptr->color != BLACK) && (ptr->parent->color == RED))
    {
        parentPtr = ptr->parent;
        grandparentPtr = ptr->parent->parent;

        if (parentPtr == grandparentPtr->left)
        {
            struct node *unclePtr = grandparentPtr->right;
 
            if (unclePtr != NULL && unclePtr->color == RED)
            {
                grandparentPtr->color = RED;
                parentPtr->color = BLACK;
                unclePtr->color = BLACK;
                ptr = grandparentPtr;
            }
 
            else
            {
                if (ptr == parentPtr->right)
                {
                    rotateLeft(root, parentPtr);
                    ptr = parentPtr;
                    parentPtr = ptr->parent;
                }
                
                else
                {
                    rotateRight(root, grandparentPtr);
                
                    bool temp = 0;
                    temp = parentPtr->color;
                    parentPtr->color= grandparentPtr->color;
                    grandparentPtr->color = temp;
               
                    ptr = parentPtr;    
                }
            }
        }

        else
        {
            struct node *unclePtr = grandparentPtr->left;
 
            if ((unclePtr != NULL) && (unclePtr->color == RED))
            {
                grandparentPtr->color = RED;
                parentPtr->color = BLACK;
                unclePtr->color = BLACK;
                ptr = grandparentPtr;
            }
            
            else
            {
                if (ptr == parentPtr->left)
                {
                    rotateRight(root, parentPtr);
                    ptr = parentPtr;
                    parentPtr = ptr->parent;
                }
 
                rotateLeft(root, grandparentPtr);
                
                bool temp2 = 0;
                temp2 = parentPtr->color;
                parentPtr->color= grandparentPtr->color;
                grandparentPtr->color = temp2;
                
                ptr = parentPtr;
            }
        }
    }
    root->color = BLACK;
}

void rotateLeft(struct node *&root, struct node *&ptr)
{
    struct node *pt_right = ptr->right;
 
    ptr->right = pt_right->left;
 
    if (ptr->right != NULL)
        ptr->right->parent = ptr;
 
    pt_right->parent = ptr->parent;
 
    if (ptr->parent == NULL)
        root = pt_right;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = pt_right;
    else
        ptr->parent->right = pt_right;
 
    pt_right->left = ptr;
    ptr->parent = pt_right;
}

void rotateRight(struct node *&root, struct node *&ptr)
{
    struct node *ptrLeft = ptr->left;
 
    ptr->left = ptrLeft->right;
 
    if (ptr->left != NULL)
        ptr->left->parent = ptr;
 
    ptrLeft->parent = ptr->parent;
 
    if (ptr->parent == NULL)
        root = ptrLeft;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = ptrLeft;
    else
        ptr->parent->right = ptrLeft;
 
    ptrLeft->right = ptr;
    ptr->parent = ptrLeft;
}

//*almost* same with hw6
void displayAll(struct node* root, int level)
{   
    if (root == NULL)
        return;
        
    if (level == 1)
    {   
        cout << root->data << " "; 
        
        if(root->parent == NULL)
        {   
            if(root->color == RED) 
                cout << "R ";
            else if (root->color == BLACK) 
                cout << "B ";       
            return;
        }
        
        else
        {   
            if(root == root->parent->left)
            {   
                if(root->color == RED) 
                    cout << "R ";       
                else if (root->color == BLACK) 
                    cout << "B ";
                
                cout<< "(" << root->parent->data <<  " L) ";                            
            }
                
            if(root == root->parent->right)
            {  
                if(root->color == RED) 
                    cout << "R ";
                else if (root->color == BLACK) 
                    cout << "B ";

                cout << "(" << root->parent->data <<  " R) ";    
            }
        }
    }
     
    else if (level > 1)
    {
        displayAll(root->left, level-1);
        displayAll(root->right, level-1);
    }    
}

//same with hw6
void inorderDisplay(struct node *root)
{
    if (root == NULL)
        return;
 
    inorderDisplay(root->left);    
    cout << root->data << endl;    
    inorderDisplay(root->right);
}

//same with hw6
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

//same with hw6
struct node* insertRec(struct node* root, struct node *ptr)
{
    if (root == NULL)
       return ptr;

    if (ptr->data < root->data)
    {
        root->left  = insertRec(root->left, ptr);
        root->left->parent = root;
    }
    else if (ptr->data > root->data)
    {
        root->right = insertRec(root->right, ptr);
        root->right->parent = root;
    }
    return root;
}

//same with hw6
int main()
{
    root = NULL;
    int data;
    
    while(1)
    {   
        cin >> data;
        if(data == -1) 
            break;
        else
            insert(data);       
    }
 
    inorderDisplay(root);

    for(int i = 0; i <= height(root); i++)
    {   
        displayAll(root, i);
        cout << endl;
    }  
 
    return 0;
}
