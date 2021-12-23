#include <iostream>
#define MAX 100000

using namespace std;
  
int heapArray[MAX], size;

void display (int heapArray[], int rootLocation, int size)
{
    int leftChild = rootLocation * 2 + 1;
    int rightChild = rootLocation * 2 + 2;

    if(rootLocation > size) return;
		
	display(heapArray, leftChild, size);
	cout << heapArray[rootLocation] << endl;
	display(heapArray, rightChild, size);
}
 
void insert (int data, int location)
{
    int parentNode;
    
    while (location > 0)
    {
        parentNode = (location - 1) / 2;
        
        if (data <= heapArray[parentNode])
        {
            heapArray[location] = data;
            return;
        }
        
        heapArray[location] = heapArray[parentNode];
        location = parentNode;
    }  
    
    heapArray[0] = data;
}

int main()
{
    int data;
    size = 0;
    
    while(1)
    {
    	cin >> data;  
		 	
		if(data == -1) break;
		
    	else
    	{
    		insert(data, size);
            size++;
		}   
	}	
	
	display(heapArray, 0, size-1);	
}
