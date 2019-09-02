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
	Game();
	void spaceCheck();
	void append();

	//oriSwipe() requires tempM[4] but no return 
	//It oprates on global variable finalM[4]
	void oriSwipe();
	void show();
	void l_swipe();
	void r_swipe();
	void u_swipe();
	void d_swipe();
	bool isSwipeValid();
	bool checkIsDead();
	void update();
	bool swipe(int type);
};
