#pragma once
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
//#define DEBUG

class Game
{
protected:
	int M[4][4];//Main Matrix shown for players
	int nextM[4][4];//to judge whether swipe is valid
	int space[16][2];//to storage the status of space
	int finalM[4];//to storage after ori_swipe() data
	int tempM[4];//to send data to ori_swpie()
	int spaceLength = 0;//as the name says
	int score = 0;//as the name says

public:
	Game()
	{
		int i = 0;
		int j;
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				M[i][j] = 0;
				nextM[i][j] = 0;
			}
			tempM[i] = 0;
			finalM[i] = 0;
		}
	}
	void spaceCheck()
	{
		int i = 0;
		int j = 0;
		spaceLength = 0;
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (M[i][j] == 0)
				{
					space[spaceLength][0] = 100 + i;
					space[spaceLength][1] = 100 + j;
					spaceLength++;
				}
			}
		}
	}
    void append()
	{
		time_t t;
		srand((unsigned)time(&t));
		int rd = (rand() % 2 + 1) * 2;
		int i = 0;
		int j;
		int loc;
		if (spaceLength != 0)
		{
			loc = rand() % (spaceLength);
			i = space[loc][0] - 100;
			j = space[loc][1] - 100;
			M[i][j] = rd;
		}
	}

	//oriSwipe() requires tempM[4] but no return 
	//It oprates on global variable finalM[4]
	void oriSwipe()
	{
		//initialization
		int buff = 0;
		int i;
		int p = 0;
		for (i = 0; i < 4; i++)
		{
			finalM[i] = 0;
		}
#ifdef DEBUG
		printf("[DEBUG]  tempM=");
		for (i = 0; i < 4; i++)
		{
			printf(" %d", tempM[i]);
		}
		printf("\n");
#endif
		//Judgements
		for (i = 0; i < 4; i++)
		{
			if (buff == 0)
			{
				buff = tempM[i];
			}
			else if (buff == tempM[i])
			{
				finalM[p] = 2 * buff;
				p++;
				score += 2 * buff;
				buff = 0;
			}
			else if (tempM[i] == 0)
			{
				continue;
			}
			else
			{
				finalM[p] = buff;
				p++;
				buff = tempM[i];
			}
		}
		if (buff != 0)
		{
			finalM[p] = buff;
		}
#ifdef DEBUG
		printf("[DEBUG] finalM=");
		for (i = 0; i < 4; i++)
		{
			printf(" %d", finalM[i]);
		}
		printf("\n\n");
#endif
	}
	void show()
	{
		int i;
		int j;
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (M[i][j] == 0)
				{
					printf("- |");
				}
				else
				{
					printf("%d |", M[i][j]);
				}
			}
			printf("\n");
		}
		printf("score=%d", score);
	}
	void l_swipe()
	{
		int i, j;
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				tempM[j] = M[i][j];
			}
			oriSwipe();
			for (j = 0; j < 4; j++)
			{
				nextM[i][j] = finalM[j];
			}
		}
	}
	void r_swipe()
	{
		int i, j;
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				tempM[j] = M[i][3 - j];
			}
			oriSwipe();
			for (j = 0; j < 4; j++)
			{
				nextM[i][3 - j] = finalM[j];
			}
		}
	}
	void u_swipe()
	{
		int i, j;
		for (j = 0; j < 4; j++)
		{
			for (i = 0; i < 4; i++)
			{
				tempM[i] = M[i][j];
			}
			oriSwipe();
			for (i = 0; i < 4; i++)
			{
				nextM[i][j] = finalM[i];
			}
		}
	}
	void d_swipe()
	{
		int i, j;
		for (j = 0; j < 4; j++)
		{
			for (i = 0; i < 4; i++)
			{
				tempM[i] = M[3 - i][j];
			}
			oriSwipe();
			for (i = 0; i < 4; i++)
			{
				nextM[3 - i][j] = finalM[i];
			}
		}
	}
	bool isSwipeValid()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (M[i][j] != nextM[i][j])
				{
					//setDead(false);
					return true; 
				}
			}
		}
		//setDead(true);
		return false;
	}
	bool checkIsDead()
	{
		l_swipe();
		if (!isSwipeValid())
		{
			r_swipe();
			if (!isSwipeValid())
			{
				u_swipe();
				if (!isSwipeValid())
				{
					d_swipe();
					if (!isSwipeValid())
						return false;
				}
			}
		}
		return true;
	}
	void update()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				M[i][j] = nextM[i][j];
				nextM[i][j] = 0;
			}
		}
	}
	bool swipe(int type)//1Up 2Left 3Down 4Right
	{
		if (!checkIsDead()) {
			printf("Dead\n");
			return false;
		}
		switch(type)
		{
		case 1:
			u_swipe(); break;
		case 2:
			l_swipe(); break;
		case 3:
			d_swipe(); break;
		case 4:
			r_swipe(); break;
		default:
			return false;
		}//swipe
		
		if (!isSwipeValid()) { return false; }
#ifndef DEBUG
		system("cls");
#endif
		update();
		spaceCheck();
		append();
		show();
		return true;
	}
};
