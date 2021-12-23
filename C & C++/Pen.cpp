#include <iostream>
using namespace std;

int main () 
{
int command[7] = {1,2,3,4,5,6,9};
int controller;
int pen=0;

int floor[20][20] = {0};
char direction = 'R';
int forward;
int currentX=0;
int currentY=0;

	while(1)
	{

		cin >> controller;

		if (controller == command[0]) //PEN UP 1
			pen = 0;

		else if (controller == command[1]) //PEN DOWN 2
			pen = 1;
		
		else if (controller == command[2]) //TURN RIGHT 3
		{
			if (direction == 'R') // change to DOWN
				direction = 'D';
			else if (direction == 'L') // change to UP
				direction = 'U';
			else if (direction == 'U') // change to RIGHT
				direction = 'R';
			else if (direction == 'D') // change to LEFT
				direction = 'L';
		}

		else if (controller == command[3]) //TURN LEFT 4
		{
			if (direction == 'R') // change to UP
				direction = 'U';
			else if (direction == 'L') // change to DOWN
				direction = 'D';
			else if (direction == 'U') // change to LEFT
				direction = 'L';
			else if (direction == 'D') // change to RIGHT
				direction = 'R';
		}

		else if (controller == command[4]) //MOVE FORWARD 5
		{
			cin >> forward;

				if (direction == 'R') // GOES RIGHT
				{
					int i;
						for (i = currentY; i < currentY+forward;)
						{
							if (pen == 1)
							{
									floor[currentX][i]=1;
									i++;
							}

							else if (pen == 0)
							{
								i++;
							}
						}
					currentY = i -1;
				}

				else if (direction == 'D') // GOES DOWN
				{	
					int j;
					for (j = currentX; j < forward + currentX; )
					{	
							if (pen == 1)
							{
									floor[j][currentY]=1;
									j++;
							}

							else if (pen == 0)
							{
								j++;
							}
					}
					currentX = j -1;
				}

				else if (direction == 'L') // GOES LEFT
				{
					int k;
					int tempY = currentY;
					for (int k = tempY; k > tempY - forward;)
					{
						if (pen == 1)
							{
									floor[currentX][k]=1;
									k--;
							}

							else if (pen == 0)
							{
								k--;
							}
					}
					currentY = tempY +1 -forward;
				}

				else if (direction == 'U') // GOES UP
				{
					int n;
					int tempX = currentX;
					for (int n = tempX; n > tempX - forward;)
					{
						if (pen == 1)
							{
									floor[n][currentY]=1;
									n--;
							}

							else if (pen == 0)
							{
								n--;
							}
					}
					currentX = tempX +1 -forward;
				}
		}

		else if (controller == command[5]) //DISPLAY 6
		{

			for (int i = 0; i < 20; i++)
			{
				for (int j = 0; j < 20; j++)
				{
					if (floor[i][j] == 1)
					{
						cout << '*';
					}
					else if (floor[i][j] == 0)
					{
						cout << ' ';
					}
				}
			cout << endl;
			}
		}

		else if (controller == command[6]) //EXIT 9
			break;

		else
			cout << "You entered an invalid command." << endl;
	}
	return 0;
}
