#include <stdio.h> 

int array[100][15];

void PRINT(int array[][6], int counter)
 { int n;
 for(n=0;n<counter;n++)
	array[n][4]=array[n][0] + array[n][2]; 
	array[n][5]=array[n][1] + array[n][3]; 
	array[n][6]=array[n][4] * array[n][5]; // R index
	array[n][7]; //intersection
	array[n][8];// boundingbox
	array[n][10]+= (array[n][4] * array[n][5]);
	array[n][9]==array[n][10] - array[n][7]; //Net area
 }
 
int main () {

   char param, com, minus;
   int x,y,h,w, counter=0, n;

while (scanf("%c", &param)!= EOF){
		do{

 	if (param == 'R' || 'r' || 'S'|| 's'|| 'P'||'p'){
    if(param == 'R' || param == 'r'){
    scanf("%d %d %d %d",&x,&y,&w,&h);
     for(n=0;n<counter;n++){
    x=array[n][0];
    y=array[n][1];
    w=array[n][2];
    h=array[n][3];}
   break;}
     
    else  if(param == 'S' || param == 's')
    {scanf("%d %d %d",&x,&y,&w);
     for(n=0;n<counter;n++){
    x=array[n][0];
    y=array[n][1];
    w=array[n][2];}
    break;}
    
    else  if(param == 'P' || param == 'p'){
    while (scanf(" %c%c",&minus, &com)!= EOF){
	if(minus == '-'){
	
 	if (com == 'D' || 'd' || 'R'|| 'r'|| 'N'||'n' ||'I' ||'i' ||'B' ||'b' ){
	
	if(com== 'D' ||com == 'd')
    {PRINT(array, counter); 
    printf("-------------\n");
    
	 printf("[%d]", counter);
	
       printf("%2d",array[0][0]);
       printf("%2d",array[0][1]);
       printf("%2d",array[0][4]);
       printf("%2d",array[0][5]);
        printf("\n-------------\n");
       break;}
    else  if(com== 'R' || com == 'r')
    {
    PRINT(array, counter);
     for(n=0;n<counter;n++)
    printf("Area of Rectangle [%d] = %d" ,n, array[n][6]);
    break;}
    else  if(com == 'N' || com == 'n') {
    PRINT(array, counter);
     for(n=0;n<counter;n++)
    printf("Net Rectangle Area = %d",array[n][9]); break;}
    else  if(com== 'I' || com == 'i')
    {printf("Intersection Area = %d",array[n][7] ); break;}
    else  if(com == 'B' || com == 'b')
    {printf("BBC = %d", array[n][8]);break;}
    }
	
	if (com != 'D' || 'd' || 'R'|| 'r'|| 'N' ||'n'|| 'i'|| 'I'|| 'b' ||'B');
    {printf("Invalid command\n" );
    break;}}
      
	if(minus != '-')
	{printf("invalid print command\n"); break;}}	
break;}}
    	
    	if(param == 'Q' || param == 'q')
    	{break;}
    	
    	if (param != 'R' || 'r' || 'S'|| 's'|| 'P' ||'p');{
    	printf("Invalid command\n" );
    break;}}
	
	
     while(param =getchar()!= EOF); 
     getchar();
     if(param == 'Q' || param == 'q')   
     {break;}}
   return 0;}
