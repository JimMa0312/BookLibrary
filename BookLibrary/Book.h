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
	char* GetName();				//��ȡͼ������
	void SetName(char* Name);		//����ͼ������
	char* Getlsbn();				//��ȡͼ��ISBN���
	void Setlsbn(char* clsbn);		//����ͼ��ISBN���
	char* GetPrice();				//��ȡͼ��۸�
	void SetPrice(char* cPrice);	//����ͼ��۸�
	char* GetAuthor();				//��ȡͼ������
	void SetAuthor(char* cAuthor);	//����ͼ������

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