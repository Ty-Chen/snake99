#pragma once
#define MIN_GAP		  5
#define FOOD_NUM	  10
#define INIT_LEN	  5
#define ROBOT_NUM     5
#define NEXT_WALL     10
#define SECOND_FACTOR 0.3

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

typedef struct node
{
	int x, y;
}node;

typedef struct wall
{
	int xStart;
	int xEnd;
	int yStart;
	int yEnd;
}wall;

typedef struct robot
{
	int  dir;
	int  len;
	node snake[1000];
}robot;


int  snake_length, dir;
wall initArea, newArea, allArea[10];
node snake[1000];
std::vector<node>  food;
std::vector<robot> robotSnake;

int  stage = 1;
int  energy = 0;
int  robotNum = 0;
bool combo = false;
bool fastMode = false;

int direct[4][2] =
{
	{ 0, -1 }, //��
{ 0, 1 },   //��
{ -1, 0 }, //��
{ 1, 0 },  //��
};

/* ���ǽ ��ǽ������.���ң� */
void print_wall(wall area, bool real);

/* �״�����ߣ�����snake[0]����ͷ */
void print_snake(node *snake, int snake_length);

/* ��ʼ�������� */
void init_robot();

/* Ϊ������ѡ����һ����ǰ������ */
void robotDir(node *snake);

/* ������ǰ�� */
bool robotGo(node *snake);

/* �ж��Ƿ�ײǽ������ײ */
bool is_correct();

/* �ж��Ƿ�Զ� */
void is_danger();

/* ���������Ȧ */
wall new_wall(wall area);

/* ������ɲ����ʳ��λ�� */
bool create_food(wall area);

void print_food();

/* �ߵ�ǰ�� */
bool go_ahead();

