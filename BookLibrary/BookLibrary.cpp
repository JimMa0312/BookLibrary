// BookLibrary.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <conio.h>
#include <string>
#include <fstream>
#include "Book.h"

#define CMD_COLS	80
#define CMD_LINES	25

using namespace std;

void	SetScreenGrid();	//设置屏幕显示的行数和列数
void	ClearScreen();		//清除屏幕
void	SetSysCaption(const char* pText);	//设置窗体标题栏
void	ShowWelcome();		//显示欢迎界面
void	ShowRootMenu();	//显示开始菜单
void	WaitView(int iCurPage);	//浏览数据时等待用户操作
void	WaitUser();		//等待用户操作
void	GuideInput();		//使用向导添加图书馆
int		GetSelect();		//获取用户菜单选择
long	GetFileLength(ifstream & ifs);//获取分拣长度
void	ViewData(int iSellPage);	//浏览所有图书记录
void	DeleteBookFromFile();		//在文件中产生图书信息
void	mainloop();					//主循环


int main()
{
    std::cout << "Hello World!\n"; 
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

void SetScreenGrid()
{
	char SysSetBuf[80];
	sprintf(SysSetBuf, "mode con col=%d lines=%d", CMD_COLS, CMD_LINES);
}
