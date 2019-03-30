/***********************snake99**********************/
/**********************2019-02-24********************/
/************************TyChen**********************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <cmath>
#include <windows.h>
#include <vector>
#include "snake.h"

/* 输出墙 虚墙上下用.左右： */
void print_wall(wall area, bool real)
{	
	const char *floor, *wall;

	locate(area.xStart, area.yStart);
	std::cout << " ";

	if (real)
	{ 
		wall  = "|";
		floor = "-";
	}
	else
	{
		wall  = ":";
		floor = ".";
	}

	for (int i = area.xStart; i <= area.xEnd; i++)
	{
		std::cout << floor;
	}

	for (int j = area.yStart; j <= area.yEnd - 1; j++)
	{
		locate(area.xStart, j + 1);
		std::cout << wall;
		for (int i = area.xStart; i <= area.xEnd; i++)
		{
			std::cout << " ";
		}
		std::cout << wall;
	}

	locate(area.xStart, area.yEnd + 1);
	std::cout << " ";
	for (int i = area.xStart; i <= area.xEnd; i++)
	{
		std::cout << floor;
	}
}

/* 首次输出蛇，其中snake[0]代表头 */
void print_snake(node *snake, int snake_length)
{
	locate(snake[0].x, snake[0].y);
	std::cout << "@";
	for (int i = 1; i <= snake_length - 1; i++)
	{
		locate(snake[i].x, snake[i].y);
		std::cout << "*";
	}
}

/* 初始化机器人 */
void init_robot()
{
	std::vector<robotSnake>::iterator iter;
	srand((unsigned)time(0));

	/* 随机初始化要保证不会相撞 */
	while (robotNum < ROBOT_NUM)
	{
		int x = (int)random(newArea.xStart + INIT_LEN, newArea.xEnd) + 1, y = (int)random(newArea.yStart, newArea.yEnd) + 1;

		if ( (x <= snake[0].x + INIT_LEN * 2) && y == 1)
		{
			continue;
		}

		for (iter = robots.begin(); iter < robots.end(); iter++)
		{
			if (y == iter->snake[0].y && 
				(x <= iter->snake[0].x + INIT_LEN * 2) &&
				(x >= iter->snake[INIT_LEN - 1].x - INIT_LEN))
			{
				continue;
			}
		}

		robotSnake tmp;

		tmp.dir = dir;
		tmp.len = INIT_LEN;
		tmp.snake[0].x = x;
		tmp.snake[0].y = y;
		
		for (int i = 1; i < INIT_LEN; i++)
		{
			tmp.snake[i].x = x - i;
			tmp.snake[i].y = y;
		}

		robots.push_back(tmp);
		print_snake(tmp.snake, tmp.len);
		robotNum++;
	}

	return;

}

/* 为机器人选择下一步的前进方向 */
void robotDir(robotSnake robot)
{
	/* 首先判断是否前进方向会碰撞蛇或墙壁，会的话转向/攻击/撞破 */
	int tmpX = robot.snake[0].x + direct[robot.dir][0];
	int tmpY = robot.snake[0].y + direct[robot.dir][1];
	for (int i = 0; i < stage; i++)
	{
		if (tmpX == allArea[i].xStart || tmpY == allArea[i].yStart
			|| tmpX == allArea[i].xEnd + 1 || tmpY == allArea[i].yEnd + 1)
		{
			if (!robot.fastMode)
			{
				
			}

		}
	}

	/* 然后判断当前是否在圈内，如果有缩圈则向圈内移动 */


	/* 接着判断当前圈内附近有没有食物，有的话向食物移动 */
	for (std::vector<node>::iterator iter = food.begin(); iter < food.end();)
	{
		if ((abs(robot.snake[0].x - iter->x) <= FOOD_ALLURE) &&
			(abs(robot.snake[0].y - iter->y) <= FOOD_ALLURE)
			)
		{
			int x = robot.snake[0].x - iter->x;
			int y = robot.snake[0].y - iter->y;

			if (x == 0 && y == 0)
			{

			}

			if (x < 0 && y < 0)
			{

			}
			else if (x < 0 && y > 0)
			{

			}
			else if (x > 0 && y > 0)
			{

			}
			else if (x > 0 && y < 0)
			{

			}
		}
	}


	/* 都没有则继续前进 */


}

/* 机器人前进 */
bool robotGo(node *snake)
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

	/*快速模式再前进一次*/
	if (fastMode)
	{
		locate(snake[snake_length - 2].x, snake[snake_length - 2].y);
		std::cout << " ";
		snake_length -= 1;
		for (int i = snake_length - 1; i >= 1; i--)
		{
			snake[i] = snake[i - 1];
		}
		snake[0].x += direct[dir][0];
		snake[0].y += direct[dir][1];
		locate(snake[1].x, snake[1].y);
		std::cout << "*";
	}

	/* 吃到了食物 */
	for (std::vector<node>::iterator iter = food.begin(); iter < food.end();)
	{
		if (snake[0].x == iter->x && snake[0].y == iter->y)
		{
			snake_length++;
			eat = true;
			snake[snake_length - 1] = temp;
			if (combo)
			{
				energy++;
			}
			iter = food.erase(iter);
		}
		else
		{
			iter++;
		}
	}

	/* 输出此时蛇状态 */
	if (!eat)
	{
		locate(temp.x, temp.y);
		std::cout << " ";
		if (fastMode)
		{
			locate(snake[snake_length].x, snake[snake_length].y);
			std::cout << " ";
		}
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

	if (fastMode)
	{
		fastMode = false;
	}

	return true;
}

/* 判断是否撞墙或者自撞 */
bool is_correct()
{
	for (int i = 0; i < stage; i++)
	{ 
		if (snake[0].x == allArea[i].xStart || snake[0].y == allArea[i].yStart 
			|| snake[0].x == allArea[i].xEnd + 1 || snake[0].y == allArea[i].yEnd + 1)
		{
			if (!fastMode)
			{
				return false;
			}

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

/* 判断是否吃毒 */
void is_danger()
{
	for (int i = 0; i < snake_length; i++)
	{
		if (snake[i].x < newArea.xStart || snake[i].x > newArea.xEnd
			|| snake[i].y < newArea.yStart || snake[i].y > newArea.yEnd
			)
		{
			locate(snake[snake_length - 1].x, snake[snake_length - 1].y);
			std::cout << " ";
			snake_length--;
			return;
		}
	}
}

/* 随机生成新圈 */
wall new_wall(wall area)
{
	srand((unsigned)time(0));

	double width = area.xEnd - area.xStart;
	double height = area.yEnd - area.yStart;
	int i = (int)random(area.yStart, area.yStart + height * 1 / 5) + 1;
	int j = (int)random(area.xStart, area.xStart + width * 1 / 5) + 1;

	wall newWall;

	newWall.xStart = j;
	newWall.yStart = i;
	newWall.xEnd   = j + width * 4 / 5;
	newWall.yEnd   = i + height * 4 / 5;

	return newWall;
}

/* 随机生成并输出食物位置 */
bool create_food(wall area)
{
	bool ok;
	node tmp;
	srand((unsigned)time(0));

	for (int i = 0; i < FOOD_NUM; i++)
	{ 
		while (1)
		{
			ok = true;
			int x = (int)random(area.xStart, area.xEnd) + 1, y = (int)random(area.yStart, area.yEnd) + 1;
			tmp.x = x;
			tmp.y = y;
			for (int k = 0; k <= snake_length - 1; k++)
			{
				if (snake[k].x == tmp.x && snake[k].y == tmp.y)
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

		food.push_back(tmp);
		locate(tmp.x, tmp.y);
		//std::cout << "$";
	}

	return true;
}

void print_food()
{
	for (std::vector<node>::iterator iter = food.begin(); iter < food.end(); iter++)
	{
		locate(iter->x, iter->y);
		std::cout << "$";
	}
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

	/*快速模式再前进一次*/
	if (fastMode)
	{
		locate(snake[snake_length - 2].x, snake[snake_length - 2].y);
		std::cout << " ";
		snake_length -= 1;
		for (int i = snake_length - 1; i >= 1; i--)
		{
			snake[i] = snake[i - 1];
		}
		snake[0].x += direct[dir][0];
		snake[0].y += direct[dir][1];
		locate(snake[1].x, snake[1].y);
		std::cout << "*";
	}

	/* 吃到了食物 */
	for (std::vector<node>::iterator iter = food.begin(); iter < food.end();)
	{ 
		if (snake[0].x == iter->x && snake[0].y == iter->y)
		{
			snake_length++;
			eat = true;
			snake[snake_length - 1] = temp;
			if (combo)
			{
				energy++;
			}
			iter = food.erase(iter);
		}
		else
		{
			iter++;
		}
	}

	/* 输出此时蛇状态 */
	if (!eat)
	{
		locate(temp.x, temp.y);
		std::cout << " ";
		if (fastMode)
		{
			locate(snake[snake_length].x, snake[snake_length].y);
			std::cout << " ";
		}
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

	if (fastMode)
	{
		fastMode = false;
	}

	return true;
}

/* 主函数 */
int main()
{
	int height, width;

	std::cout << "-----------------------------------------------" << std::endl;
	std::cout << "------------------- snake99 -------------------" << std::endl;
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
	int		cnt;
	char	ch;
	wall	newWall;
	bool	areaChange;
	double  second;
	clock_t lastClock;
	clock_t moveClockA, moveClockB;

	cnt				= 0;
	stage			= 1;
	energy			= 5;
	second			= 20;
	areaChange		= false;
	snake_length	= INIT_LEN;
	initArea.xEnd   = width;
	initArea.yEnd   = height;
	initArea.xStart = 0;
	initArea.yStart = 0;

	newArea = initArea;
	allArea[stage - 1] = newArea;

	//初始化蛇的位置：第一行最左
	for (int i = 0; i < snake_length; i++)
	{
		snake[i].x = snake_length - i;
		snake[i].y = 1;
	}
	dir = 3;

	/* 输出初始地图，蛇与食物 */
	system("cls");
	hide();
	print_wall(newArea, true);
	create_food(newArea);
	print_food();
	init_robot();	
	print_snake(snake, snake_length);

	lastClock = clock();

	/* 开始游戏 */
	while (1)
	{
		/* 难度随长度增加而提高 
		double hard_len = (double)snake_length / (double)(height * width);
		*/

		/* 调节时间，单位是ms */
		moveClockA = clock();
		while (1)
		{
			moveClockB = clock();
			//if (moveClockB - moveClockA >= (int)(400 - 30 * hard) * (1 - sqrt(hard_len))) 
			if (moveClockB - moveClockA >= (int)(500 - 30 * hard)) 
			{ 
				break;			
			}
		}

		if (second > 10)
		{ 
			/* 倒计时 */
			locate(allArea[0].xEnd + 3, 1);
			std::cout << "new wall will appear in " << int (second - 10) << " seconds                ";
			second -= SECOND_FACTOR;
		}
		else if (second > 0)
		{
			if (!areaChange)
			{
				areaChange = true;

				/* 刷新随机缩圈并打印 */
				newWall = new_wall(newArea);
				//system("cls");
				print_wall(newWall, false);
				print_snake(snake, snake_length);
				print_food();
			}

			/* 倒计时 */
			locate(allArea[0].xEnd + 3, 1);
			std::cout << "outer area will be dangerous in " << int (second) << " seconds";
			second -= SECOND_FACTOR;
		}
		else
		{
			second = 20;
			stage++;
			areaChange = false;

			print_wall(newWall, true);
			print_snake(snake, snake_length);
			print_food();

			/* 更新newArea */
			newArea = newWall;
			allArea[stage - 1] = newArea;
		}

		locate(width + 3, 2);
		std::cout << "                    ";

		/* 判断当前是否吃毒，吃毒则长度减少 */
		cnt++;
		if (cnt * SECOND_FACTOR > 1)
		{
			is_danger();
			cnt = 0;
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
			else if (ch == 32)
			{
				if (energy > 0)
				{
					fastMode = true;
					energy--;
					locate(width + 3, 2);
					std::cout << "get into fast mode";
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
		locate(0, height + 2);
		std::cout << "Now length: " << snake_length << std::endl;
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
