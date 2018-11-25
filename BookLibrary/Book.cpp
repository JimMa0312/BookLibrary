#include "pch.h"
#include "Book.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>


Book::Book()
{
}

Book::Book(char * cName, char * clsbn, char * cPrice, char * cAuthor)
{
	strncpy_s(m_nName, cName, NUM1);
	strncpy_s(m_clsbn, clsbn, NUM1);
	strncpy_s(m_cPrice, cPrice, NUM2);
	strncpy_s(m_cAuthor, cAuthor, NUM2);
}


Book::~Book()
{
}

char * Book::GetName()
{
	return m_nName;
}

void Book::SetName(char * Name)
{
	strncpy_s(m_nName, Name, NUM1);
}

char * Book::Getlsbn()
{
	return m_clsbn;
}

void Book::Setlsbn(char * clsbn)
{
	strncpy_s(m_clsbn, clsbn, NUM1);
}

char * Book::GetPrice()
{
	return m_cPrice;
}

void Book::SetPrice(char * cPrice)
{
	strncpy_s(m_cPrice, cPrice, NUM2);
}

char * Book::GetAuthor()
{
	return m_cAuthor;
}

void Book::SetAuthor(char * cAuthor)
{
	strncpy_s(m_cAuthor, cAuthor, NUM2);
}

void Book::VriteData()
{
	std::ofstream ofile;
	ofile.open("book.dat", std::ios::binary | std::ios::app);

	try
	{
		ofile.write(m_nName, NUM1);
		ofile.write(m_clsbn, NUM1);
		ofile.write(m_cPrice, NUM2);
		ofile.write(m_cAuthor, NUM2);
	}
	catch (...)
	{
		throw "file error occurred";
		ofile.close();
	}
	ofile.close();
}

void Book::DeleteDate(int iCount)
{
	long respos;
	int iDataCount = 0;
	std::fstream file;
	std::fstream tempFile;
	std::ofstream ofile;

	char cTempBuffer[NUM1 + NUM1 + NUM2 + NUM2];

	file.open("book.dat", std::ios::binary | std::ios::in | std::ios::out);
	tempFile.open("temp.dat", std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);
	file.seekg(0, std::ios::end);

	respos = file.tellg();
	iDataCount = respos / this->GetLength();
	if (iCount<0 && iCount>iDataCount)
	{
		throw "Input number error";
	}
	else
	{
		file.seekg((iCount)*this->GetLength(), std::ios::beg);
		for (int j = 0; j < (iDataCount-iCount); j++)
		{
			memset(cTempBuffer, 0, this->GetLength());
			file.read(cTempBuffer, this->GetLength());
			tempFile.write(cTempBuffer, this->GetLength());
		}

		file.close();
		tempFile.seekg(0, std::ios::beg);
		ofile.open("book.dat");
		ofile.seekp((iCount-1)*this->GetLength(), std::ios::beg);
		for (int i = 0; i < (iDataCount-iCount); i++)
		{
			memset(cTempBuffer, 0, this->GetLength());
			tempFile.read(cTempBuffer, this->GetLength());
			ofile.write(cTempBuffer, this->GetLength());
		}

		tempFile.close();
		ofile.close();

		remove("temp.dat");
	}
}

void Book::GetBookFromFile(int iCount)
{
	char cName[NUM1];
	char cIsbn[NUM1];
	char cPrice[NUM2];
	char cAuthor[NUM2];

	std::ifstream ifile;
	ifile.open("book.dat", std::ios::binary);

	try
	{
		ifile.seekg(iCount*this->GetLength(), std::ios::beg);

		ifile.read(cName, NUM1);
		if (ifile.tellg()>0)
		{
			strncpy_s(m_nName, cName, NUM1);
		}
		
		ifile.read(cIsbn, NUM1);
		if (ifile.tellg() > 0)
		{
			strncpy_s(m_clsbn, cIsbn, NUM1);
		}

		ifile.read(cPrice, NUM2);
		if (ifile.tellg() > 0)
		{
			strncpy_s(m_cPrice, cPrice, NUM2);
		}

		ifile.read(cAuthor, NUM2);
		if (ifile.tellg() > 0)
		{
			strncpy_s(m_cAuthor, cAuthor, NUM2);
		}
	}
	catch (...)
	{
		throw "file erro occurred";
		ifile.close();
	}
	ifile.close();
}

inline int Book::GetLength()
{
	return NUM1+NUM1+NUM2+NUM2;
}
