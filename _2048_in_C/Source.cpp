#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "Game.h"
#ifndef DEBUG
#define DEBUG
#endif

//C++
//#include <iostream>
//using namespace std;

int main()
{
	Game Game1;
	Game1.init();
	int i = 0;
	Game1.spaceCheck();
	Game1.append();
	Game1.show();
	char choice, ch2;
	for (i = 0; i < 100000; i++)
	{
		choice = _getch();
		switch (choice)//2 4 6 8 Keys Controller
		{
		case '8':
			Game1.u_swipe(); system("cls"); Game1.spaceCheck(); Game1.append(); Game1.show(); break;
		case '4':
			Game1.l_swipe(); system("cls"); Game1.spaceCheck(); Game1.append(); Game1.show(); break;
		case '6':
			Game1.r_swipe(); system("cls"); Game1.spaceCheck(); Game1.append(); Game1.show(); break;
		case '2':
			Game1.d_swipe(); system("cls"); Game1.spaceCheck(); Game1.append(); Game1.show(); break;
		case 0xffffffe0://Direction Keys Press
			ch2 = _getch();
			switch (ch2) 
			{
			case 0x48:
				Game1.u_swipe(); system("cls"); Game1.spaceCheck(); Game1.append(); Game1.show(); break;
			case 0x4b:
				Game1.l_swipe(); system("cls"); Game1.spaceCheck(); Game1.append(); Game1.show(); break;
			case 0x4d:
				Game1.r_swipe(); system("cls"); Game1.spaceCheck(); Game1.append(); Game1.show(); break;
			case 0x50:
				Game1.d_swipe(); system("cls"); Game1.spaceCheck(); Game1.append(); Game1.show(); break;
			default:
#ifdef DEBUG
				printf("%x", choice);
#endif
				break;
			}
		default:
#ifdef DEBUG
			printf("%x", choice);
#endif
			break;
		}
		printf("\n");
	}
	printf("Hello, World!");
	return 0;
}