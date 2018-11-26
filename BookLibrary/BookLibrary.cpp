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
void	SetSysCaption();
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
	SetScreenGrid();
	SetSysCaption("图书馆里系统");
	mainloop();
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
	sprintf_s(SysSetBuf, "mode con col=%d lines=%d", CMD_COLS, CMD_LINES);
	system(SysSetBuf);
}

void ClearScreen()
{
	system("cls");
}

void SetSysCaption()
{
	system("title Sample");
}

void SetSysCaption(const char * pText)
{
	char sysSetBuf[80];
	sprintf_s(sysSetBuf, "title %s", pText);

	system(sysSetBuf);
}

void ShowWelcome()
{
	for (int i = 0; i < 7; i++)
	{
		cout << endl;
	}
	cout << setw(40);
	cout << "**************" << endl;
	cout << setw(40);
	cout << "图书馆里系统" << endl;
	cout << setw(40);
	cout << "**************" << endl;
}

void ShowRootMenu()
{
	cout << setw(40);
	cout << "请选择功能" << endl;
	cout << endl;
	cout << setw(38);
	cout << "1 添加新书" << endl;
	cout << endl;
	cout << setw(38);
	cout << "2 浏览全部" << endl;
	cout << endl;
	cout << setw(38);
	cout << "3 删除图书" << endl;
}

void WaitView(int iCurPage)
{
	char buf[256];
	gets_s(buf);
	if (buf[0]=='q')
	{
		system("exit");
	}
	if (buf[0]=='m')
	{
		mainloop();
	}
	if (buf[0]=='n')
	{
		ViewData(iCurPage);
	}
}

void WaitUser()
{
	int iInputPage = 0;
	cout << "enter 返回主菜单 q 退出" << endl;
	char buf[256];
	gets_s(buf);
	if (buf[0]=='q')
	{
		system("exit");
	}
}

void GuideInput()
{
	char inName[NUM1];
	char inIsbn[NUM1];
	char inPrice[NUM2];
	char inAuthor[NUM2];

	cout << "输入书名" << endl;
	cin >> inName;
	cout << "输入ISBN" << endl;
	cin >> inIsbn;
	cout << "输入价格" << endl;
	cin >> inPrice;
	cout << "输入作者" << endl;
	cin >> inAuthor;

	Book book(inName, inIsbn, inPrice, inAuthor);
	book.VriteData();
	cout << "Write Finish" << endl;
	WaitUser();
}

int GetSelect()
{
	char buf[256];
	gets_s(buf);
	return atoi(buf);
}

long GetFileLength(ifstream & ifs)
{
	long tmppos;
	long respos;
	tmppos = ifs.tellg();
	ifs.seekg(0, ios::end);
	respos = ifs.tellg();
	ifs.seekg(tmppos, ios::beg);
	return respos;
}

void ViewData(int iSellPage=1)
{
	int iPage = 0;
	int iCurPage = 0;
	int iDataCount = 0;
	char inName[NUM1];
	char inIsbn[NUM1];
	char price[NUM2];
	char inAuthor[NUM2];

	bool bIndex = false;
	int iFileLength;
	iCurPage = iSellPage;
	ifstream ifile;
	ifile.open("book.dat", ios::binary);
	iFileLength = GetFileLength(ifile);
	iDataCount = iFileLength / (NUM1 + NUM1 + NUM2 + NUM2);

	if (iDataCount>=1)
	{
		bIndex = true;
	}

	iPage = iDataCount / 20 + 1;
	ClearScreen();

	cout << " 共有记录" << iDataCount << " ";
	cout << " 共有页数" << iPage << " ";
	cout << " 当前页数" << iCurPage << " ";
	cout << "n 显示下一页 m返回" << endl;
	cout << setw(5) << "Index";
	cout << setw(22) << "Name" << setw(22) << "Isbn";
	cout << setw(15) << "Price" << setw(15) << "Author";
	cout << endl;

	try
	{
		ifile.seekg((iCurPage - 1) * 20 * (NUM1 + NUM1 + NUM2 + NUM2), ios::beg);
		if (!ifile.fail())
		{
			for (int i = 1; i < 21; i++)
			{
				memset(inName, 0, 128);
				memset(inIsbn, 0, 123);
				memset(price, 0, 50);
				memset(inAuthor, 0, 50);

				if (bIndex)
				{
					cout << setw(3) << ((iCurPage - 1) * 20 + i);
				}
				ifile.read(inName, NUM1);
				cout << setw(24) << inName;
				ifile.read(inIsbn, NUM1);
				cout << setw(24) << inIsbn;
				ifile.read(price, NUM2);
				cout << setw(12) << price;
				ifile.read(inAuthor, NUM2);
				cout << setw(12) << inAuthor;
				cout << endl;
				if (ifile.tellg()<0)
				{
					bIndex = false;
				}
				else
				{
					bIndex = true;
				}
			}
		}
	}
	catch (...)
	{
		cout << "throw file exception" << endl;
		throw "file error occured";
		ifile.close();
	}
	if (iCurPage<iPage)
	{
		iCurPage = iCurPage + 1;
		WaitView(iCurPage);
	}
	else
	{
		WaitView(iCurPage);
	}

	ifile.close();

}

void DeleteBookFromFile()
{
	int iDelCount;
	cout << "Input delete index" << endl;
	cin >> iDelCount;
	Book tmpBook;
	tmpBook.DeleteDate(iDelCount);
	cout << "Delete Finish" << endl;
	WaitUser();
}

void mainloop()
{
	ShowWelcome();
	while (1)
	{
		ClearScreen();
		ShowWelcome();
		ShowRootMenu();
		switch (GetSelect())
		{
		case 1:
			ClearScreen();
			GuideInput();
			break;
		case 2:
			ClearScreen();
			ViewData();
			break;
		case 3:
			ClearScreen();
			DeleteBookFromFile();
			break;
		default:
			break;
		}
	}
}
