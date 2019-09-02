#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "Game.h"
#ifndef DEBUG
//#define DEBUG
#endif

const int UP = 1;
const int LEFT = 2;
const int DOWN = 3;
const int RIGHT = 4;

//C++
//#include <iostream>
//using namespace std;

int main()
{
	Game Game1;
	//Game1.init();
	int i = 0;
	Game1.spaceCheck();
	Game1.append();
	Game1.show();//init
	char choice, ch2;
	for (i = 0; i < 100000; i++)
	{
		choice = _getch();
		switch (choice)//2 4 6 8 Keys Controller
		{
		case '8':
		case 'w':
			Game1.swipe(UP); break;
		case '4':
		case 'a':
			Game1.swipe(LEFT); break;
		case '6':
		case 'd':
			Game1.swipe(RIGHT); break;
		case '2':
		case 's':
			Game1.swipe(DOWN); break;
		case 0xffffffe0://Direction Keys Press
			ch2 = _getch();
			switch (ch2) 
			{
			case 0x48:
			    Game1.swipe(UP); break;			
			case 0x4b:
				Game1.swipe(LEFT); break;
			case 0x4d:
				Game1.swipe(RIGHT); break;
			case 0x50:
				Game1.swipe(DOWN);  break;
			default:
#ifdef DEBUG
				printf(" 0x%x", choice);
#endif
				break;
			}
		default:
#ifdef DEBUG
			printf(" 0x%x", choice);
#endif
			break;
		}
		printf("\n");
	}
	printf("Hello, World!");
	return 0;
}