#pragma once
#define MIN_GAP		  5
#define FOOD_NUM	  10
#define INIT_LEN	  5
#define ROBOT_NUM     5
#define NEXT_WALL     10
#define SECOND_FACTOR 0.3

/* 光标定位 */
HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
COORD coord;

void locate(int x, int y)
{
	coord.X = x;
	coord.Y = y;
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
	{ 0, -1 }, //下
{ 0, 1 },   //上
{ -1, 0 }, //左
{ 1, 0 },  //右
};

/* 输出墙 虚墙上下用.左右： */
void print_wall(wall area, bool real);

/* 首次输出蛇，其中snake[0]代表头 */
void print_snake(node *snake, int snake_length);

/* 初始化机器人 */
void init_robot();

/* 为机器人选择下一步的前进方向 */
void robotDir(node *snake);

/* 机器人前进 */
bool robotGo(node *snake);

/* 判断是否撞墙或者自撞 */
bool is_correct();

/* 判断是否吃毒 */
void is_danger();

/* 随机生成新圈 */
wall new_wall(wall area);

/* 随机生成并输出食物位置 */
bool create_food(wall area);

void print_food();

/* 蛇的前进 */
bool go_ahead();

