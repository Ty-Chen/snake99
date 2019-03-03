/************************贪吃蛇***********************/
/**********************2019-02-24*********************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <cmath>
#include <windows.h>


/* 光标定位 */
HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
COORD coord;

void locate(int x, int y)
{
	coord.X = y;
	coord.Y = x;
	SetConsoleCursorPosition(hout, coord);
};

/* 隐藏光标 */
void hide()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(hout, &cursor_info);
}

/* 生成随机数 */
double random(double start, double end)
{
	return start + (end - start)*rand() / (RAND_MAX + 1.0);
}

/* 定义地图的初始长宽、缩圈长宽，蛇的坐标，长度，方向，食物的位置 */

struct node
{
	int x, y;
}snake[1000];

struct wall
{
	int xStart;
	int xEnd;
	int yStart;
	int yEnd;
};

wall initArea, newArea, allArea[10];

int snake_length, dir;
int energy = 0;
int stage = 1;
node food[10];
bool combo = false;
int direct[4][2] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

/* 输出墙 */
void print_wall(wall area)
{
	std::cout << " ";
	for (int i = area.xStart; i <= area.xEnd; i++)
	{
		std::cout << "-";
	}
	std::cout << std::endl;

	for (int j = area.yStart; j <= area.yEnd - 1; j++)
	{
		std::cout << "|";
		for (int i = area.xStart; i <= area.xEnd; i++) std::cout << " ";
		std::cout << "|" << std::endl;
	}

	std::cout << " ";
	for (int i = area.xStart; i <= area.xEnd; i++)
	{
		std::cout << "-";
	}
}

/* 首次输出蛇，其中snake[0]代表头 */
void print_snake()
{
	locate(snake[0].x, snake[0].y);
	std::cout << "@";
	for (int i = 1; i <= snake_length - 1; i++)
	{
		locate(snake[i].x, snake[i].y);
		std::cout << "*";
	}
}

/* 判断是否撞墙或者自撞 */

bool is_correct()
{
	for (int i = 0; i < stage; i++)
	{ 
		if (snake[0].x == allArea[i].yStart || snake[0].y == allArea[i].xStart 
			|| snake[0].x == allArea[i].yEnd + 1 || snake[0].y == allArea[i].xEnd + 1)
		{
			return false;
		}
	}
	for (int i = 1; i <= snake_length - 1; i++)
	{
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
		{
			return false;
		}
	}

	return true;
}

/* 随机生成并输出食物位置 */
bool print_food()
{
	srand((unsigned)time(0));
	bool ok;
	while (1)
	{
		ok = true;
		int i = (int)random(newArea.yStart, newArea.yEnd) + 1, j = (int)random(newArea.xStart, newArea.xEnd) + 1;
		food[0].x = i; food[0].y = j;
		for (int k = 0; k <= snake_length - 1; k++)
		{
			if (snake[k].x == food[0].x && snake[k].y == food[0].y)
			{
				ok = false;
				break;
			}
		}
		if (ok)
		{
			break;
		}
	}
	locate(food[0].x, food[0].y);
	std::cout << "$";
	return true;
}

/* 蛇的前进 */
bool go_ahead()
{
	node temp;
	bool eat = false;
	temp = snake[snake_length - 1];
	for (int i = snake_length - 1; i >= 1; i--)
	{	
		snake[i] = snake[i - 1];
	}
	snake[0].x += direct[dir][0];
	snake[0].y += direct[dir][1];
	locate(snake[1].x, snake[1].y);
	std::cout << "*";

	/* 吃到了食物 */
	if (snake[0].x == food[0].x && snake[0].y == food[0].y)
	{
		snake_length++;
		eat = true;
		snake[snake_length - 1] = temp;
		if (combo)
		{
			energy++;
		}
	}

	/* 输出此时蛇状态 */
	if (!eat)
	{
		locate(temp.x, temp.y);
		std::cout << " ";
	}
	else
	{
		print_food();
	}

	locate(snake[0].x, snake[0].y);
	std::cout << "@";

	/* 如果自撞 */
	if (!is_correct())
	{
		system("cls");
		std::cout << "You lose!" << std::endl << "Length: " << snake_length << std::endl;
		return false;
	}
	return true;
}

/* 主函数 */
int main()
{
	int height, width;

	std::cout << "--------------------贪吃蛇---------------------" << std::endl;
	std::cout << "请输入两个数,表示地图高和款.要求长宽均不小于10." << std::endl;
	std::cout << "请注意窗口大小,以免发生错位.建议将窗口调为最大." << std::endl;
	std::cout << "再选择难度.请在1-10中输入1个数,1最简单,10则最难" << std::endl; 
	std::cout << "突然变向获取食物可以得到能量奖励用于加速突破障碍" << std::endl;
	std::cout << "然后进入游戏画面,以方向键控制方向.祝你游戏愉快!" << std::endl;
	std::cout << "-----------------------------------------------" << std::endl;
	std::cin >> height >> width;

	if (height < 10 || width < 10 || height > 200 || width > 200)
	{
		std::cout << "ERROR" << std::endl;
		system("pause");
		return 0;
	}

	int hard;
	std::cin >> hard;

	if (hard <= 0 || hard > 10)
	{
		std::cout << "ERROR" << std::endl;
		system("pause");
		return 0;
	}

Again:

	/* 数据全部初始化，包括蛇长，位置，方向 */
	char	ch;
	double  hard_len;
	clock_t lastClock;
	clock_t moveClockA, moveClockB;

	stage			= 1;
	energy			= 0;
	snake_length	= 5;
	initArea.xEnd   = width;
	initArea.yEnd   = height;
	initArea.xStart = 0;
	initArea.yStart = 0;

	newArea = initArea;
	allArea[stage - 1] = newArea;

	for (int i = 0; i <= 4; i++)
	{
		snake[i].x = 1;
		snake[i].y = 5 - i;
	}
	dir = 3;

	/* 输出初始地图，蛇与食物 */
	system("cls");
	hide();
	print_wall(newArea);
	print_food();
	print_snake();
	locate(initArea.yEnd + 2, 0);
	std::cout << "Now length: ";

	lastClock = clock();

	/* 开始游戏 */
	while (1)
	{
		/* 难度随长度增加而提高 */
		hard_len = (double)snake_length / (double)(height * width);

		/* 调节时间，单位是ms */
		moveClockA = clock();
		while (1)
		{
			moveClockB = clock();
			if (moveClockB - moveClockA >= (int)(400 - 30 * hard) * (1 - sqrt(hard_len))) 
			{ 
				break;			
			}
		}

		/* 接受键盘输入的上下左右，并以此改变方向 */
		if (_kbhit())
		{
			ch = _getch();
			if (ch == -32)
			{
				ch = _getch();
				switch (ch)
				{
				//上
				case 72:
					if (dir == 2 || dir == 3)
					{
						dir = 0;
						combo = true;
					}
					break;
				//下
				case 80:
					if (dir == 2 || dir == 3)
					{
						dir = 1;
						combo = true;
					}
					break;
				//左
				case 75:
					if (dir == 0 || dir == 1)
					{
						dir = 2;
						combo = true;
					}
					break;
				//右
				case 77:
					if (dir == 0 || dir == 1)
					{
						dir = 3;
						combo = true;
					}
					break;
				}
			}
		}

		/* 前进 */
		if (!go_ahead())
		{
			break;
		}

		combo = false;

		/* 在最后输出此时长度, 能量值， 游戏阶段 */
		locate(height + 2, 12);
		std::cout << snake_length << std::endl;
		std::cout << "energy : " << energy << std::endl;
		std::cout << "stage : " << stage << std::endl;
	}

	//system("pause");

	char cmd;
	std::cout << "Do you want play again?(Y(y)/N(n))" << std::endl;
	std::cin >> cmd;
	if (cmd == 'y' || cmd == 'Y')
	{
		goto Again;
	}
	return 0;
}
