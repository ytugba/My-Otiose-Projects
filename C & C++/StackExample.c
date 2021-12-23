#include <stdio.h>
#include <stdlib.h>

struct Customer {
	int customerID;
	int arrive;
	int process;
	int waiting;
	struct Customer* next;
}*front, *rear;

struct Employee
{
    int EmployeeID;
    struct Employee *next;
}*top;

void insertCustomers(int id, int ar, int pro);
void sendCustomer();
void insertEmployees(int emp);
void PopEmployees();
void display();
void workTimes();

int main()
{

	int i;
	int id,ar,pro;
	top = NULL;
        
        for ( i = 1; i <= 6; i++)
        	insertEmployees(i);
		
		while((scanf("%d%d%d",&id,&ar,&pro))!= EOF)
			insertCustomers(id, ar, pro);

		display();
}

void insertEmployees(int emp)
{
		struct Employee *temp = NULL;
    
    if (top == NULL)
    {
        top =malloc(sizeof(struct Employee));
        top->next = NULL;
        top->EmployeeID = emp;
    }

    else
    {
        temp =malloc(sizeof(struct Employee));
        temp->next = top;
        temp->EmployeeID = emp;
        top = temp;
    }
}

void PopEmployees()
{
		struct Employee *temp3 = NULL;

    temp3 = top;
    
    if (temp3 == NULL)
        return;
    
    else
        temp3 = temp3->next;
    
    free(top);
    top = temp3;
}

void insertCustomers(int id, int ar, int pro) 
{
		struct Customer* temp = malloc(sizeof(struct Customer));

	temp->customerID =id; 
	temp->arrive=ar;
	temp->process=pro;
	temp->next = NULL;
	
	if(front == NULL && rear == NULL)
	{
		front = rear = temp;
		return;
	}

	rear->next = temp;
	rear = temp;
}

void sendCustomer() 
{
		struct Customer* temp = front;
	if(front == NULL) 
		return;
	
	if(front == rear) 
		front = rear = NULL;
	
	else
		front = front->next;

	free(temp);
}

void display()
{

	    struct Customer *temp2 = NULL;
	    struct Employee *temp = NULL;
	    
	    int id6=0, id5=0, id4=0, id3=0, id2=0, id1=0;
    
    temp2 = front;
    temp = top;


    
    if (temp2 == NULL)
        return;

    while (temp2 != NULL)
    {
        printf("%d\t%d\t%d\t%d\t%d\n", temp2->customerID,temp->EmployeeID, temp2->arrive, temp2->arrive+temp2->process, temp2-> waiting);
        if (temp->EmployeeID == 6)
        	id6 += temp2->process;

        if (temp->EmployeeID == 5)
        	id5 += temp2->process;

        if (temp->EmployeeID == 4)
        	id4 += temp2->process;

        if (temp->EmployeeID == 3)
        	id3 += temp2->process;

        if (temp->EmployeeID == 2)
        	id2 += temp2->process;

        if (temp->EmployeeID == 1)
        	id1 += temp2->process;

               temp2 = temp2->next;
    }

    workTimes(id6, id5, id4, id3, id2, id1); 
}


void workTimes(int id6,int id5,int id4,int id3,int id2,int id1) 
{
	printf("\n");
		printf("6\t%d\n", id6);
		printf("5\t%d\n", id5);
		printf("4\t%d\n", id4);
		printf("3\t%d\n", id3);
		printf("2\t%d\n", id2);
		printf("1\t%d\n", id1);
}
