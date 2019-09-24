#include "Game.h"

void Game::spaceCheck()
{
	int i = 0;
	int j = 0;
	Game::spaceLength = 0;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (M[i][j] == 0)
			{
				Game::space[Game::spaceLength][0] = 100 + i;
				Game::space[Game::spaceLength][1] = 100 + j;
				Game::spaceLength++;
			}
		}
	}
}
void Game::append()
{
	time_t t;
	srand((unsigned)time(&t));
	int rd = (rand() % 2 + 1) * 2;
	int i = 0;
	int j;
	int loc;
	if (Game::spaceLength != 0)
	{
		loc = rand() % (Game::spaceLength);
		i = Game::space[loc][0] - 100;
		j = Game::space[loc][1] - 100;
		Game::M[i][j] = rd;
	}
}

//oriSwipe() requires tempM[4] but no return 
//It oprates on global variable finalM[4]
void Game::oriSwipe()
{
	//initialization
	int buff = 0;
	int i;
	int p = 0;
	for (i = 0; i < 4; i++)
	{
		Game::finalM[i] = 0;
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
			buff = Game::tempM[i];
		}
		else if (buff == Game::tempM[i])
		{
			Game::finalM[p] = 2 * buff;
			p++;
			Game::score += 2 * buff;
			buff = 0;
		}
		else if (Game::tempM[i] == 0)
		{
			continue;
		}
		else
		{
			Game::finalM[p] = buff;
			p++;
			buff = Game::tempM[i];
		}
	}
	if (buff != 0)
	{
		Game::finalM[p] = buff;
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
void Game::show()
{
	int i;
	int j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (Game::M[i][j] == 0)
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
void Game::l_swipe()
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			Game::tempM[j] = Game::M[i][j];
		}
		Game::oriSwipe();
		for (j = 0; j < 4; j++)
		{
			Game::nextM[i][j] = Game::finalM[j];
		}
	}
}
void Game::r_swipe()
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			Game::tempM[j] = Game::M[i][3 - j];
		}
		Game::oriSwipe();
		for (j = 0; j < 4; j++)
		{
			Game::nextM[i][3 - j] = Game::finalM[j];
		}
	}
}
void Game::u_swipe()
{
	int i, j;
	for (j = 0; j < 4; j++)
	{
		for (i = 0; i < 4; i++)
		{
			Game::tempM[i] = Game::M[i][j];
		}
		Game::oriSwipe();
		for (i = 0; i < 4; i++)
		{
			Game::nextM[i][j] = Game::finalM[i];
		}
	}
}
void Game::d_swipe()
{
	int i, j;
	for (j = 0; j < 4; j++)
	{
		for (i = 0; i < 4; i++)
		{
			Game::tempM[i] = Game::M[3 - i][j];
		}
		Game::oriSwipe();
		for (i = 0; i < 4; i++)
		{
			Game::nextM[3 - i][j] = Game::finalM[i];
		}
	}
}
bool Game::isSwipeValid()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (Game::M[i][j] != Game::nextM[i][j])
			{
				//setDead(false);
				return true;
			}
		}
	}
	//setDead(true);
	return false;
}
bool Game::checkIsDead()
{
	Game::l_swipe();
	if (!Game::isSwipeValid())
	{
		Game::r_swipe();
		if (!Game::isSwipeValid())
		{
			Game::u_swipe();
			if (!Game::isSwipeValid())
			{
				Game::d_swipe();
				if (!Game::isSwipeValid())
					return false;
			}
		}
	}
	return true;
}
void Game::update()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Game::M[i][j] = Game::nextM[i][j];
			Game::nextM[i][j] = 0;
		}
	}
}
bool Game::swipe(int type)//1Up 2Left 3Down 4Right
{
	if (!Game::checkIsDead()) {
		printf("Dead\n");
		return false;
	}
	switch (type)
	{
	case 1:
		Game::u_swipe(); break;
	case 2:
		Game::l_swipe(); break;
	case 3:
		Game::d_swipe(); break;
	case 4:
		Game::r_swipe(); break;
	default:
		return false;
	}//swipe

	if (!Game::isSwipeValid()) { return false; }
#ifndef DEBUG
	system("cls");
#endif
	Game::update();
	Game::spaceCheck();
	Game::append();
	Game::show();
	return true;
}