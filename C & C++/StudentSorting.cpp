///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* 																					  /
/		Program : Students, Their Midterms and Average of the classes 												  /
/		Requirements of program:																					  /
/	-Use linked list. -> No limited input size.																		  /
/	-Create four classroom named 1, 2, 3, 4.																		  /
/	-In the insertion sort students according to their midterm grades in a decreasing order. 						  /
/	-While taking the average midterms of classes delete the students who have the lowest midterms 					  /
/	 until the number of the student numbers are equalized.															  /
/	-Write this average into classMidtermAverage variable and print them on the screen as:							  /
/																													  /
/			<classID> <classMidtermAverage> 																		  /
/			...																										  /
/	-Students who begin with StudentID 66 are in class 1, students starting with 77 in class 2, 					  /
/	 students starting with 88 are in class 3, and students starting with 99 are in class 4.						  /
/	-write two functions: void printAll(nodeClass *head)(I) void printClassList(nodeClass *head, int classId)(II).	  /
/		I- Print Student List and Class List 																		  /
/	    II- Print Desired Class printClassList 																		  /
/	-use given structures 																							  / 													
/	-end input with -1 																								 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;


//STRUCTURES
struct nodeClass
{
	int classID;
	double classMidtermAverage;
	struct nodeClass *next;
	struct nodeStudent *studentPtr;
};

struct nodeStudent
{
	int studentID;
	int midterm;
	struct nodeStudent *next;
};
//STRUCTURES-END

//FUNCTIONS
void printAll(nodeClass *head);
void printClassList(nodeClass *head, int classID);
void insertion(nodeStudent **head1, nodeStudent **head2, int ID, int mid);
void midtermAverage(nodeStudent *shead1, nodeStudent *shead2);
int findMin(int c1, int c2, int c3, int c4);
//FUNCTIONS-END

//DECLERATIONS
int counter1 = 0, counter2 = 0, counter3 = 0, counter4 = 0;
int c1 = 0, c2 =0, c3=0, c4=0;
int inputCounter = 0;
int minimum = 0;
int minimum12, minimum34;
double average1 = 0.0, average2 = 0.0, average3 = 0.0, average4 = 0.0;
//DECLERATION-END

//HEADS & POINTERS
nodeStudent *head1 = NULL;
nodeStudent *head2 = NULL;
nodeClass *head = NULL;
nodeStudent *studentPtr;
nodeStudent *temp2;
nodeClass node;
//HEADS & POINTERS-END

int main()
{

	int mid = 0;
	int ID;

	do
	{
	 	cin >> ID;
		
		if (ID == -1)
			break;
		
		cin >> mid;
		
		if (ID / 1000 == 99)
			counter4++;
		else if (ID / 1000 == 88)
			counter3++;
		else if (ID / 1000 == 77)
			counter2++;
		else if (ID  / 1000 == 66)
			counter1++;
		
		insertion(&head1, &head2, ID, mid);
		inputCounter++;
	}

	while(1);

	c1 = counter1;
	c2 = counter2;
	c3 = counter3;
	c4 = counter4;

	findMin(c1,c2,c3,c4);

		cout << "FOR THE EQUALIZATION OF STUDENTS IN THE CLASSES" << endl;
		cout << "FROM THE LOWEST TO HIGHEST MIDTERM GRADES" << endl << "STUDENTS HAS BEEN REMOVED." << endl;
		cout << endl << endl;
	
	printAll(head);
	
	cout << endl;

	cout << "YOU CALLED PRINT CLASS LIST FUNTCIONS!" << endl;
	
		cout<<endl << endl;
		cout<<"Class 4" << endl;
		printClassList(head, 4);
		cout << endl;
		
		cout<<"Class 1" << endl;
		printClassList(head, 1);
		cout<<endl;
		
		cout<<"Class 2" << endl;
		printClassList(head, 2);
		cout << endl;
			
		cout<<"Class 3" << endl;
		printClassList(head, 3);
		cout << endl;

	cout << "END OF PRINT CLASS LIST FUNCTIONS!" << endl;

	return 0;
}

void insertion(nodeStudent **head1, nodeStudent **head2, int ID, int mid)
{
	if (*head2 == NULL || mid >= (*head2)->midterm)
	{
		studentPtr = (nodeStudent*)malloc(sizeof(nodeStudent));
		temp2 = (nodeStudent*)malloc(sizeof(nodeStudent));

		studentPtr->studentID = ID;
		studentPtr->next = *head1;
		*head1 = studentPtr;
		temp2->midterm = mid;
		temp2->next = *head2;
		*head2 = temp2;
	}

	else if (studentPtr==NULL)
		cout << "There is a problem have been occured while entering inputs. Please try again." << endl;

	else if (*head2 != NULL || mid < (*head2)->midterm)
	{
		studentPtr = *head1;
		temp2 = *head2;
		do
		{
			if (temp2->midterm > mid && (temp2->next == NULL || temp2->next->midterm <= mid))
			{
				nodeStudent *temp1 = (nodeStudent*)malloc(sizeof(nodeStudent));
				nodeStudent *temp3 = (nodeStudent*)malloc(sizeof(nodeStudent));

				temp1->studentID = ID;
				temp1->next = studentPtr->next;
				studentPtr->next = temp1;
				temp3->midterm = mid;
				temp3->next = temp2->next;
				temp2->next = temp3;
				
			return;
			}

			studentPtr = studentPtr->next;
			temp2 = temp2->next;
		}
		while (studentPtr != NULL);
	}
}

int findMin(int c1, int c2, int c3, int c4)
{
	if (c1<c2)
		minimum12 = c1;
	else
		minimum12 = c2;

	if (c3 <c4)
		minimum34 = c3;
	else 
		minimum34 = c4;

	if (minimum12 < minimum34)
		minimum = minimum12;
	else
		minimum=minimum34;

return minimum;
}

void printAll(nodeClass *head)
{
	cout << "YOU CALLED PRINT ALL FUNCTION!" << endl;

	cout <<endl <<endl<<"Average of Classes:" << endl;

	midtermAverage(head1, head2);
	cout<<endl << endl;
	
		cout<<"Class 1" << endl;
		printClassList(head, 1);
		cout << endl;
		
		cout<<"Class 2" << endl;
		printClassList(head, 2);
		cout<<endl;
		
		cout<<"Class 3" << endl;
		printClassList(head, 3);
		cout << endl;
		
		cout<<"Class 4" << endl;
		printClassList(head, 4);
		cout << endl;
	
	cout << "END OF PRINT ALL FUNCTION!" << endl;
}

void midtermAverage(nodeStudent *shead1, nodeStudent *shead2)
{
	int counter1 = 0, counter2 = 0, counter3 = 0, counter4 = 0;
	int t=0;

	while (t < inputCounter)
	{
		if (counter4 != minimum&& shead1 != NULL && shead1->studentID / 1000 == 99)
		{
			average4 += shead2->midterm;
			shead1 = shead1->next;
			shead2 = shead2->next;
			counter4++;
		}

		else if (counter4 == minimum&& shead1 != NULL && shead1->studentID / 1000 == 99)
		{
			shead1 = shead1->next;
			shead2 = shead2->next;
		}
		else if (counter3 != minimum&& shead1 != NULL && shead1->studentID / 1000 == 88)
		{
			average3 += shead2->midterm;
			shead1 = shead1->next;
			shead2 = shead2->next;
			counter3++;
		}
		else if (counter3 == minimum&& shead1 != NULL && shead1->studentID / 1000 == 88)
		{
			shead1 = shead1->next;
			shead2 = shead2->next;
		}
		else if (counter2 != minimum&& shead1 != NULL && shead1->studentID / 1000 == 77)
		{
			average2 += shead2->midterm;
			shead1 = shead1->next;
			shead2 = shead2->next;
			counter2++;
		}
		else if (counter2 == minimum&& shead1 != NULL && shead1->studentID / 1000 == 77)
		{
			shead1 = shead1->next;
			shead2 = shead2->next;
		}
		else if (counter1 != minimum&& shead1 != NULL && shead1->studentID / 1000 == 66)
		{
			average1 += shead2->midterm;
			shead1 = shead1->next;
			shead2 = shead2->next;
			counter1++;
		}
		else if (counter1 == minimum&& shead1 != NULL && shead1->studentID / 1000 == 66)
		{
			shead1 = shead1->next;
			shead2 = shead2->next;
		}

	t++;
	}

	if (minimum!= 0)
	{
		cout << endl;
		cout << endl << "1. " << fixed << setprecision(1) <<average1 / (double) minimum;
		cout << endl << "2. " << fixed << setprecision(1) << average2 / (double) minimum;
		cout << endl << "3. " << fixed << setprecision(1) << average3 / (double) minimum;
		cout << endl << "4. " << fixed << setprecision(1) << average4 / (double) minimum;
		cout << endl;
	}

	else if (minimum!= 0 && average1 == 0.0)
		cout << "1. 0.0" << endl;

	else if (minimum!= 0 && average2 == 0.0)
		cout << "2. 0.0" << endl;

	else if (minimum!= 0 && average3 == 0.0)
		cout << "3. 0.0" << endl;

	else if (minimum!= 0 && average4 == 0.0)
		cout << "4. 0.0" << endl;

	else if (minimum== 0)
	{
		cout << "1. 0.0" << endl;
		cout << "2. 0.0" << endl;
		cout << "3. 0.0" << endl;
		cout << "4. 0.0" << endl;
	}
}

void printClassList(nodeClass *head, int classID)
{
	int listCounter = 0;
	int t=0;
	
		nodeStudent *shead1=head1;
		nodeStudent *shead2=head2;

	while (t < inputCounter)
	{
		if (shead1 != NULL || shead2 != NULL)
		{
			if (classID == 4 && shead1->studentID / 1000 == 99)
			{
				listCounter++;
				
				if (listCounter <=minimum)
					cout << shead1->studentID << " " << shead2->midterm << endl;
				
				if (minimum==0)
				{
					cout << "THIS CLASS IS EMPTY BECAUSE OF EQUALIZATION." << endl;
					break;
				}
			}
		
			else if (classID == 3 && shead1->studentID / 1000 == 88)
			{
				listCounter++;
			
				if (listCounter <=minimum)
					cout << shead1->studentID << " " << shead2->midterm << endl;
					
				if (minimum==0)
				{
					cout << "THIS CLASS IS EMPTY BECAUSE OF EQUALIZATION." << endl;
					break;
				}
			}

			else if (classID == 2 && shead1->studentID / 1000 == 77)
			{
				listCounter++;
		
				if (listCounter <=minimum)
					cout << shead1->studentID << " " << shead2->midterm << endl;
					
				if (minimum==0)
				{
					cout << "THIS CLASS IS EMPTY BECAUSE OF EQUALIZATION." << endl;
					break;
				}
			}
				
			else if (classID == 1 && shead1->studentID / 1000 == 66)
			{	
				listCounter++;
			
				if (listCounter <=minimum)
					cout << shead1->studentID << " " << shead2->midterm << endl;

				if (minimum==0)
				{
					cout << "THIS CLASS IS EMPTY BECAUSE OF EQUALIZATION." << endl;
					break;
				}
			}
		}

		shead1 = shead1->next;
		shead2 = shead2->next;		
		t++;
	}
	cout << endl;
}
