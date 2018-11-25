#pragma once

#define NUM1 128
#define NUM2 50

class Book
{
	//customer
public:
	Book();
	Book(char* cName, char* clsbn, char* cPrice, char* cAuthor);
	~Book();
	//operator
public:
	char* GetName();				//获取图书名称
	void SetName(char* Name);		//设置图书名称
	char* Getlsbn();				//获取图书ISBN编号
	void Setlsbn(char* clsbn);		//设置图书ISBN编号
	char* GetPrice();				//获取图书价格
	void SetPrice(char* cPrice);	//设置图书价格
	char* GetAuthor();				//获取图书作者
	void SetAuthor(char* cAuthor);	//设置图书作者

	void VriteData();
	void DeleteDate(int iCount);
	void GetBookFromFile(int iCount);
	inline int GetLength();
protected:
	char m_nName[NUM1];
	char m_clsbn[NUM1];
	char m_cPrice[NUM2];
	char m_cAuthor[NUM2];
};