/************************̰����***********************/
/**********************2019-02-24*********************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <cmath>
#include <windows.h>


/*** ��궨λ ***/
HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
COORD coord;

void locate(int x, int y)
{
	coord.X = y;
	coord.Y = x;
	SetConsoleCursorPosition(hout, coord);
};

/*** ���ع�� ***/
void hide()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(hout, &cursor_info);
}

/*** ��������� ***/
double random(double start, double end)
{
	return start + (end - start)*rand() / (RAND_MAX + 1.0);
}

/*** �����ͼ�ĳ����ߵ����꣬���ȣ�����ʳ���λ�� ***/
int height, width;
int newHeight, newWidth;

struct node
{
	int x, y;
}snake[1000];

int snake_length, dir;
node food;
int direct[4][2] = { { -1,0 },{ 1,0 },{ 0,-1 },{ 0,1 } };

/*** ���ǽ ***/
void print_wall(int widthStart, int widthEnd, int heightStart, int heightEnd)
{
	std::cout << " ";
	for (int i = widthStart; i <= widthEnd; i++)
		std::cout << "-";
	std::cout << std::endl;
	for (int j = heightStart; j <= heightEnd - 1; j++)
	{
		std::cout << "|";
		for (int i = widthStart; i <= widthEnd; i++) std::cout << " ";
		std::cout << "|" << std::endl;
	}
	std::cout << " ";
	for (int i = widthStart; i <= widthEnd; i++)
	{
		std::cout << "-";
	}
}

/*** �״�����ߣ�����snake[0]����ͷ ***/
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

/*** �ж��Ƿ�ײǽ������ײ ***/
bool is_correct()
{
	if (snake[0].x == 0 || snake[0].y == 0 || snake[0].x == height + 1 || snake[0].y == width + 1) return false;
	for (int i = 1; i <= snake_length - 1; i++)
	{
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) return false;
	}
	return true;
}

/*** ������ɲ����ʳ��λ�� ***/
bool print_food()
{
	srand((unsigned)time(0));
	bool e;
	while (1)
	{
		e = true;
		int i = (int)random(0, height) + 1, j = (int)random(0, width) + 1;
		food.x = i; food.y = j;
		for (int k = 0; k <= snake_length - 1; k++)
		{
			if (snake[k].x == food.x && snake[k].y == food.y)
			{
				e = false; break;
			}
		}
		if (e) break;
	}
	locate(food.x, food.y);
	std::cout << "$";
	return true;
}

/*** �ߵ�ǰ�� ***/
bool go_ahead()
{
	node temp;
	bool e = false;
	temp = snake[snake_length - 1];
	for (int i = snake_length - 1; i >= 1; i--)
	{	
		snake[i] = snake[i - 1];
	}
	snake[0].x += direct[dir][0];
	snake[0].y += direct[dir][1];
	locate(snake[1].x, snake[1].y);
	std::cout << "*";

	/*** �Ե���ʳ�� ***/
	if (snake[0].x == food.x && snake[0].y == food.y)
	{
		snake_length++;
		e = true;
		snake[snake_length - 1] = temp;
	}

	/*** �����ʱ��״̬ ***/
	if (!e)
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

	/*** �����ײ ***/
	if (!is_correct())
	{
		system("cls");
		std::cout << "You lose!" << std::endl << "Length: " << snake_length << std::endl;
		return false;
	}
	return true;
}

/*** ������ ***/
int main()
{
	std::cout << "--------------------̰����---------------------" << std::endl;
	std::cout << "��������������,��ʾ��ͼ��С.Ҫ�󳤿����С��10." << std::endl;
	std::cout << "��ע�ⴰ�ڴ�С,���ⷢ����λ.���齫���ڵ�Ϊ���." << std::endl;
	std::cout << "��ѡ���Ѷ�.����1-10������1����,1���,10������" << std::endl;
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

	/*** ����ȫ����ʼ���������߳���λ�ã����� ***/
	snake_length = 5;
	clock_t a, b;
	char ch;
	double hard_len;
	for (int i = 0; i <= 4; i++)
	{
		snake[i].x = 1;
		snake[i].y = 5 - i;
	}
	dir = 3;
	/*** �����ʼ��ͼ������ʳ�� ***/
	system("cls");
	hide();
	print_wall(0, width, 0, height);
	print_food();
	print_snake();
	locate(height + 2, 0);
	std::cout << "Now length: ";
	/*** ��ʼ��Ϸ ***/
	while (1)
	{
		/*** �Ѷ��泤�����Ӷ���� ***/
		hard_len = (double)snake_length / (double)(height * width);

		/*** ����ʱ�䣬��λ��ms ***/
		a = clock();
		while (1)
		{
			b = clock();
			if (b - a >= (int)(400 - 30 * hard) * (1 - sqrt(hard_len))) break;
		}

		/*** ���ܼ���������������ң����Դ˸ı䷽�� ***/
		if (_kbhit())
		{
			ch = _getch();
			if (ch == -32)
			{
				ch = _getch();
				switch (ch)
				{
				case 72:
					if (dir == 2 || dir == 3)
						dir = 0;
					break;
				case 80:
					if (dir == 2 || dir == 3)
						dir = 1;
					break;
				case 75:
					if (dir == 0 || dir == 1)
						dir = 2;
					break;
				case 77:
					if (dir == 0 || dir == 1)
						dir = 3;
					break;
				}
			}
		}
		/*** ǰ�� ***/
		if (!go_ahead()) break;
		/*** ����������ʱ���� ***/
		locate(height + 2, 12);
		std::cout << snake_length << std::endl;
		std::cout << "stage: " << hard << std::endl;
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
