/************************̰����***********************/
/**********************2019-02-24*********************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <cmath>
#include <windows.h>

#define FOOD_NUM 5
#define INIT_LEN 5

/* ��궨λ */
HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
COORD coord;

void locate(int x, int y)
{
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(hout, coord);
};

/* ���ع�� */
void hide()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(hout, &cursor_info);
}

/* ��������� */
double random(double start, double end)
{
	return start + (end - start)*rand() / (RAND_MAX + 1.0);
}

/* �����ͼ�ĳ�ʼ������Ȧ�����ߵ����꣬���ȣ�����ʳ���λ�� */

struct node
{
	int x, y;
}snake[1000];

typedef struct wall
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

int direct[4][2] = 
{	
	{ 0, -1 }, //��
	{ 0, 1 },   //��
	{ -1, 0 }, //��
	{ 1, 0 },  //��
};

/* ���ǽ ��ǽ������.���ң� */
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

/* �״�����ߣ�����snake[0]����ͷ */
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

/* �ж��Ƿ�ײǽ������ײ */
bool is_correct()
{
	for (int i = 0; i < stage; i++)
	{ 
		if (snake[0].x == allArea[i].xStart || snake[0].y == allArea[i].yStart 
			|| snake[0].x == allArea[i].xEnd + 1 || snake[0].y == allArea[i].yEnd + 1)
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

/* �ж��Ƿ�Զ� */
void is_danger()
{

}

/* ���������Ȧ */
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

/* ������ɲ����ʳ��λ�� */
bool create_food(wall area)
{
	bool ok;

	srand((unsigned)time(0));

	for (int i = 0; i < FOOD_NUM; i++)
	{ 
		while (1)
		{
			ok = true;
			int x = (int)random(area.xStart, area.xEnd) + 1, y = (int)random(area.yStart, area.yEnd) + 1;
			food[i].x = x; food[i].y = y;
			for (int k = 0; k <= snake_length - 1; k++)
			{
				if (snake[k].x == food[i].x && snake[k].y == food[i].y)
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
		locate(food[i].x, food[i].y);
		std::cout << "$";
	}

	return true;
}

void print_food()
{
	for (int i = 0; i < FOOD_NUM; i++)
	{
		locate(food[i].x, food[i].y);
		std::cout << "$";
	}
}

/* �ߵ�ǰ�� */
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

	/* �Ե���ʳ�� */
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

	/* �����ʱ��״̬ */
	if (!eat)
	{
		locate(temp.x, temp.y);
		std::cout << " ";
	}
	/*
	else
	{
		print_food(newArea);
	}
	*/

	locate(snake[0].x, snake[0].y);
	std::cout << "@";

	/* �����ײ */
	if (!is_correct())
	{
		system("cls");
		std::cout << "You lose!" << std::endl << "Length: " << snake_length << std::endl;
		return false;
	}
	return true;
}

/* ������ */
int main()
{
	int height, width;

	std::cout << "--------------------̰����---------------------" << std::endl;
	std::cout << "������������,��ʾ��ͼ�ߺͿ�.Ҫ�󳤿����С��10." << std::endl;
	std::cout << "��ע�ⴰ�ڴ�С,���ⷢ����λ.���齫���ڵ�Ϊ���." << std::endl;
	std::cout << "��ѡ���Ѷ�.����1-10������1����,1���,10������" << std::endl; 
	std::cout << "ͻȻ�����ȡʳ����Եõ������������ڼ���ͻ���ϰ�" << std::endl;
	std::cout << "Ȼ�������Ϸ����,�Է�������Ʒ���.ף����Ϸ���!" << std::endl;
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

	/* ����ȫ����ʼ���������߳���λ�ã����� */
	double		second = 20;
	char	ch;
	wall	newWall;
	bool	areaChange;
	clock_t lastClock;
	clock_t moveClockA, moveClockB;

	stage			= 1;
	energy			= 0;
	areaChange		= false;
	snake_length	= INIT_LEN;
	initArea.xEnd   = width;
	initArea.yEnd   = height;
	initArea.xStart = 0;
	initArea.yStart = 0;

	newArea = initArea;
	allArea[stage - 1] = newArea;

	for (int i = 0; i < snake_length; i++)
	{
		snake[i].x = snake_length - i;
		snake[i].y = 1;
	}
	dir = 3;

	/* �����ʼ��ͼ������ʳ�� */
	system("cls");
	hide();
	print_wall(newArea, true);
	create_food(newArea);
	print_snake();

	lastClock = clock();

	/* ��ʼ��Ϸ */
	while (1)
	{
		/* �Ѷ��泤�����Ӷ���� 
		double hard_len = (double)snake_length / (double)(height * width);
		*/

		/* ����ʱ�䣬��λ��ms */
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
			/* ����ʱ */
			locate(allArea[0].xEnd + 3, 1);
			std::cout << "new wall will appear in " << int (second - 10) << " seconds                ";
			second -= 0.3;
		}
		else if (second > 0)
		{
			if (!areaChange)
			{
				areaChange = true;

				/* ˢ�������Ȧ����ӡ */
				newWall = new_wall(newArea);
				//system("cls");
				print_wall(newWall, false);
				print_food();
			}

			/* ����ʱ */
			locate(allArea[0].xEnd + 3, 1);
			std::cout << "outer area will be dangerous in " << int (second) << " seconds";
			second -= 0.3;
		}
		else
		{
			second = 20;
			stage++;
			areaChange = false;

			print_wall(newWall, true);
			print_food();

			/* ����newArea */
			newArea = newWall;
			allArea[stage - 1] = newArea;
		}

		/* �жϵ�ǰ�Ƿ�Զ����Զ��򳤶ȼ��� */
		is_danger();

		/* ���ܼ���������������ң����Դ˸ı䷽�� */
		if (_kbhit())
		{
			ch = _getch();
			if (ch == -32)
			{
				ch = _getch();
				switch (ch)
				{
				//��
				case 72:
					if (dir == 2 || dir == 3)
					{
						dir = 0;
						combo = true;
					}
					break;
				//��
				case 80:
					if (dir == 2 || dir == 3)
					{
						dir = 1;
						combo = true;
					}
					break;
				//��
				case 75:
					if (dir == 0 || dir == 1)
					{
						dir = 2;
						combo = true;
					}
					break;
				//��
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

		/* ǰ�� */
		if (!go_ahead())
		{
			break;
		}

		combo = false;

		/* ����������ʱ����, ����ֵ�� ��Ϸ�׶� */
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
