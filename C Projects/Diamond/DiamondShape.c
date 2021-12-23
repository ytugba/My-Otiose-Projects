#include <stdio.h>
 
void bor_dia (int); //border and diamond function definition
 
int main () 

{ //main 

int x;
 
   scanf("%d", &x);
   printf("Diamond size: %d\n", x);
   	bor_dia(x); // function call
   printf("Done!\n");
	
return 0;

} //main-end
 
void bor_dia (int x) 

{//function
   
   static int asterix = -1;
   int i,j, blank;
 
     if (x <= 0)
     {
     return;
     }
	//upper triangle for diamond
	blank= x-1;
	asterix= 1;
	
	for(i=0;i<= 2*x; i++)
	
	printf("-");
	printf("\n");

	for(j=0; j< x; j++)

		{//| for

	printf("|");
		
		for(i=0; i<blank; i++)
		printf(" ");
		for(i=0; i<asterix; i++)
		printf("*");
		for(i=0; i<blank; i++)
		printf(" ");
	
	printf("|\n");
	
	//bottom triangle for diamond

	blank --;
	asterix += 2;

        	}//| for-end

	for(j=0;j< x; j++)

		{//| for2

	blank ++;
	asterix -=2;

	printf("|");

		for(i=0; i<blank; i++)
		printf(" ");
		for(i=0; i<asterix; i++)
		printf("*");
		for(i=0; i<blank; i++)
		printf(" ");
		printf("|\n");

		}// for2-end

	for(i=0; i<2*x+1; i++)

			printf("-");
			printf("\n");

			scanf("%d", &x);
			printf("Diamond size: %d\n", x);
		
			bor_dia(x--);

}//function-end
