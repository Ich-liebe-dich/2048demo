// ConsoleApplication25.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <graphics.h>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <conio.h>
using namespace std;

#define Row 4
#define Col 4
int flag = 1;//用于追踪数组中的数字是否仍可以相加，合并
int _move = 0;//操作数字
int max = 2048;
int score = 0;
int a[Row][Col] = { 0 };//存放游戏中的数字
int t[4] = { 0 };//辅助数组
int b[2] = { 2,4 };//用于产生随机数
COLORREF color[12] =
{
	RGB(252,252,201),RGB(234,140,140),RGB(236,217,138),
	RGB(189,236,138),RGB(189,236,138),RGB(139,235,233),
	RGB(141,175,233),RGB(176,142,232),RGB(232,142,223),
	RGB(231,143,168),RGB(104,108,255),RGB(243,104,255)
};
int onetoone[12] = { 0,2,4,8,16,32,64,128,256,512,1024,2048 };
LPCTSTR onetoonestr[12] = { _T("0"),_T("2"),_T("4"),_T("8"),_T("16"),_T("32"),_T("64"),_T("128"),_T("256"),_T("512"),_T("1024"),_T("2048") };
LPCTSTR list[4] = { _T("       开 始 游 戏"),_T("          帮 助"),_T("          关 于"),_T("      退 出 游 戏") };
int Font[4][4] =
{ 50,36,57,305 ,
 50,25,50,305 ,
 34,18,48,313 ,
 30,14,47,315 };//保存字体大小与初始坐标

int strAt(const int[], int, int);
int digit(int);
int isEmpty();//检测是否任有空位，有返回1

void Init();//画出游戏界面
void DrawRect();//画出方块
void Rand(int &, int &);//随机产生2或4
void nextRect(int, int);//产生新方块

void play();

void Delete0(int[], int n);
void Add(int[], int n);
void MoveUp();
void MoveDown();
void MoveLeft();
void MoveRight();

void help();
void asfor();
int Interface1();
void f()
{
	for (int x = 59; x <= 371; x += 156)
	{
		solidroundrect(x, 720, x + 50, 720 + 25, 5, 5);
	}
}

void control(int);

int main()
{
	initgraph(480, 750);
	
	while (1)
	{
		control(Interface1());
	}
	closegraph();
}

int strAt(const int a[], int len, int index)
{
	for (int i = 0; i < len; i++)
	{
		if (a[i] == index)
		{
			return i;
		}
	}
	return 0;
}

int digit(int a)
{
	int count = 0;
	while (a)
	{
		a /= 10;
		count++;
	}
	return count;
}

int isEmpty()
{
	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++)
		{
			if (a[i][j] == 0)
				return 1;
		}
	}
	return 0;
}

void Init()
{
	flag = 1;//用于追踪数组中的数字是否仍可以相加，合并
	_move = 0;//操作数字
	score = 0;
	max = 0;
	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++)
		{
			a[i][j] = 0;
		}
	}
	for (int i = 0; i < 4; i++)
		t[i] = 0;
	
	
	setfillcolor(RGB(250, 250, 0));
	setbkcolor(WHITE);
	cleardevice();
	setbkmode(TRANSPARENT);

	solidroundrect(15, 20, 15 + 150, 20 + 150, 5, 5);
	settextcolor(WHITE);
	settextstyle(55, 0, _T("黑体"));
	outtextxy(35, 60, _T("2048"));

	

	for (int i = 180; i <= 330; i += 150)
	{
		setfillcolor(RGB(255, 128, 255));
		solidroundrect(i, 20, i + 135, 20 + 50, 5, 5);
	}
	settextstyle(25, 0, _T("黑体"));
	outtextxy(180, 20, _T("分数"));
	outtextxy(330, 20, _T("步数"));

	setfillcolor(RGB(240, 235, 213));
	solidroundrect(15, 270, 15 + 450, 270 + 450, 10, 10);
	setfillcolor(color[0]);
	for (int x = 25; x <= 355; x += 110)
	{
		for (int y = 280; y <= 620; y += 110)
		{
			solidroundrect(x, y, x + 100, y + 100, 3, 3);
		}
	}
}

void DrawRect()
{
	for (int i = 180; i <= 330; i += 150)
	{
		setfillcolor(RGB(255, 128, 255));
		solidroundrect(i, 20, i + 135, 20 + 50, 5, 5);
	}
	settextstyle(25, 0, _T("黑体"));
	outtextxy(180, 20, _T("分数"));
	outtextxy(330, 20, _T("步数"));
	TCHAR temp[10];
	_stprintf(temp, _T("%d"), score);
	settextstyle(25, 0, _T("黑体"));
	outtextxy(180, 45, temp);
	_stprintf(temp, _T("%d"), _move);
	outtextxy(330, 45, temp);
	for (int _i = 0; _i < 4; _i++)
	{
		for (int _j = 0; _j < 4; _j++)
		{
			if (a[_i][_j] == 0)
			{
				setfillcolor(color[0]);
				solidroundrect(25 + 110 * _j, 280 + 110 * _i, 125 + 110 * _j, 380 + 110 * _i, 3, 3);
			}
			else
			{
				int temp = strAt(onetoone, 12, a[_i][_j]);
				setfillcolor(color[temp]);
				solidroundrect(25 + 110 * _j, 280 + 110 * _i, 125 + 110 * _j, 380 + 110 * _i, 3, 3);
				int index = digit(a[_i][_j]) - 1;
				settextstyle(Font[index][0], Font[index][1], _T("黑体"));
				outtextxy(Font[index][2] + 110 * _j, Font[index][3] + 110 * _i, onetoonestr[temp]);
			}
		}
	}

}
void Rand(int &i, int &j)
{
	_move++;
	while (1)
	{
		i = rand() % 4;
		j = rand() % 4;
		if (a[i][j] == 0)
			return;
	}
}
void nextRect(int i, int j)
{
	int temp = strAt(onetoone, 12, a[i][j]);
	setfillcolor(color[temp]);
	solidroundrect(25 + 110 * j, 280 + 110 * i, 125 + 110 * j, 380 + 110 * i, 3, 3);
	int index = digit(a[i][j]) - 1;
	settextstyle(Font[index][0], Font[index][1], _T("黑体"));
	outtextxy(Font[index][2] + 110 * j, Font[index][3] + 110 * i, onetoonestr[temp]);
}
void play()
{
	srand((unsigned)time(NULL));
	int Life = 1; max = 0;
	Init();
	char choose = 'w';
	int k = 1;
	while (Life&&max < 2048)
	{
		DrawRect();
		int i, j;

		while (k)
		{
			Rand(i, j);
			a[i][j] = b[rand() % 2];
			nextRect(i, j);
			k = 0;
		}

		if (flag)
		{
			Rand(i, j);
			a[i][j] = b[rand() % 2];
			Sleep(500);
			nextRect(i, j);
			flag = 0;
		}

		choose = _getch();
		switch (choose)
		{
		case 'w':
		{
			MoveUp();
			break;
		}
		case 's':
		{
			MoveDown();
			break;
		}
		case 'a':
		{
			MoveLeft();
			break;
		}
		case 'd':
		{
			MoveRight();
			break;
		}
		default:
			break;
		}
		Life = isEmpty();
		if ((flag == 0) && (Life == 0))
		{
			break;
		}
	}
	if (max >= 2048)
	{
		setfillcolor(RGB(35, 235, 185));

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				score += a[i][j];
				a[i][j] = 0;
				DrawRect();
				Sleep(300);
			}
		}
		settextcolor(RGB(128, 128, 255));
		solidrectangle(15, 180, 15 + 450, 180 + 80);
		settextstyle(50, 0, _T("黑体"));
		outtextxy(15, 190, _T("最终得分："));
		TCHAR temp[10];
		_stprintf(temp, _T("%d"), score);
		outtextxy(240, 190, temp);
		outtextxy(250, 350, _T("按任意键返回主菜单..."));
		_getch();
	}
	else
	{
		
		setfillcolor(RGB(35, 235, 185));
		
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				score += a[i][j];
				a[i][j] = 0;
				DrawRect();
				Sleep(300);		
			}
		}
		settextcolor(RGB(128,128,255));
		solidrectangle(15, 180, 15 + 450, 180+80);
		settextstyle(50, 0, _T("黑体"));
		outtextxy(15, 190, _T("最终得分："));
		TCHAR temp[10];
		_stprintf(temp, _T("%d"), score);
		outtextxy(240, 190, temp);
		outtextxy(0, 350, _T(" 按任意键返回主菜单"));
		_getch();
	}
}
int Interface1()
{
	setbkmode(TRANSPARENT);
	setbkcolor(color[11]);
	cleardevice();

	setfillcolor(RGB(250, 250, 0));
	solidroundrect(210, 231, 210 + 60, 231 + 60, 10, 10);
	settextcolor(RGB(148,235,158));
	settextstyle(30, 0, _T("黑体"));
	outtextxy(210, 246, _T("2048"));

	setfillcolor(RGB(0,255,255));
	for (int i = 0; i <= 3; i++)
	{
		solidrectangle(180, 321 + 45 * i, 180 + 120, 321 + 45 * i + 20);
	}
	settextcolor(GREEN);
	settextstyle(20, 0, _T("微软雅黑"));
	for (int i = 0; i < 4; i++)
	{
		outtextxy(180, 321 + 45 * i, list[i]);
	}
	settextcolor(WHITE);
	RECT r = { 50, 480, 50+410,100 + 480 };
	drawtext(_T("\n\n抵制不良游戏，拒绝盗版游戏。注意自我保护，谨防受骗上当。\n适度游戏益脑，沉迷游戏伤身。合理安排时间，享受健康生活。\n            App v2.5.0        Ich/liebe/dich        2019.2.15"), &r, DT_WORDBREAK);
	MOUSEMSG m;
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			int tem = 321;
			int temp = 351;
			for (int i = 0; i < 4; i++)
			{
				if (m.x >= 180 && m.x <= 300 && m.y >= tem && m.y <= temp)
					return i;
				tem += 45;
				temp += 45;
			}

		}
	}
}
void Delete0(int t[], int n)
{
	int i, j = 0;
	for (i = 0; i < n; i++)
	{
		if (t[i] == 0)
		{
			for (j = i + 1; j < n; j++)
			{
				if (t[j] != 0)
				{
					flag = 1;
					break;
				}
			}
			t[i] = t[j];
			t[j] = 0;
		}
		if (j >= 3) break;
	}
}
void Add(int t[], int n)
{
	Delete0(t, n);
	for (int i = 0; i < Row - 1; i++)
	{
		if (t[i] && (t[i] == t[i + 1]))
		{
			t[i] *= 2;
			score += t[i];
			flag = 1;
			t[i + 1] = 0;
		}
	}
	Delete0(t, n);
}
void MoveUp()
{
	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++)
		{
			t[j] = a[j][i];
		}

		Add(t, Row);

		for (int j = 0; j < Col; j++)
		{
			a[j][i] = t[j];
		}
	}
}
void MoveDown()
{
	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++)
		{
			t[3 - j] = a[j][i];
		}

		Add(t, Row);

		for (int j = 0; j < Col; j++)
		{
			a[j][i] = t[3 - j];
		}
	}
}
void MoveLeft()
{
	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++)
		{
			t[j] = a[i][j];
		}

		Add(t, Row);

		for (int j = 0; j < Col; j++)
		{
			a[i][j] = t[j];
		}
	}
}
void MoveRight()
{
	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++)
		{
			t[3 - j] = a[i][j];
		}

		Add(t, Row);

		for (int j = 0; j < Col; j++)
		{
			a[i][j] = t[3 - j];
		}
	}
}
void help()
{
	cleardevice();

	RECT r = { 0, 135, 480,135 + 480 };
	drawtext(_T("游戏简介：\n2048游戏共有16个格子，初始时会有两个格子上安放数字，每次可以选择上下左右其中一个方向去滑动，每滑动一次，所有的数字方块都会往滑动的方向靠拢外，系统也会在空白的地方随即出现一个数字方块，相同数字的方块在靠拢、相撞时会相加。系统给予的数字方块不是2就是4，玩家要想办法在这小小的16格范围中凑出“2048”这个数字方块。\n操作说明：\nwsad：上下左右，请切换成英文输入法进行游戏。\n点击鼠标返回..."), &r, DT_WORDBREAK);
	MOUSEMSG m;
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			return;
		}
	}
}
void asfor()
{
	cleardevice();

	RECT r = { 0, 135, 480,135 + 480 };
	drawtext(_T("1.游戏名称：2048\n2.游戏分类：休闲益智\n3.版本号：V2.5.0\n4.开发者：Ich/liebe/dich\n\n点击鼠标返回..."), &r, DT_WORDBREAK);
	MOUSEMSG m;
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			return;
		}
	}
}
void control(int a)
{
	switch (a)
	{
	case 0:
		play();
		break;
	case 1:
		help();
		break;
	case 2:
		asfor();
		break;
	case 3:
		exit(0);
	}
}