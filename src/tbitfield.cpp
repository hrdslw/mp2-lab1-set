// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len <= 0)
		throw "Ошибка: отрицательное значение длины";
	MemLen = len / 32 + 1;
	BitLen = len;
	pMem - new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	int idx;
	idx = n / 32;
	return idx;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	int idx = n % 32;
	TELEM t = 1;
	t << idx;
	return t;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0 || n >= BitLen)
		throw "Ошибка: отрицательное значение индекса бита";
	TELEM m = GetMemMask(n);
	int idx = GetMemIndex(n);
	pMem[idx] = pMem[idx] | m;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n >= BitLen)
		throw "Ошибка: отрицательное значение индекса бита";
	TELEM m = ~(GetMemMask(n));
	int idx = GetMemIndex(n);
	pMem[idx] = pMem[idx] & m;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || n >= BitLen)
		throw "Ошибка: отрицательное значение индекса бита";
	TELEM m = GetMemMask(n);
	int idx = GetMemIndex(n);
	TELEM res = m & pMem[idx];
	return res;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this->MemLen != bf.MemLen) {
		delete[] this->pMem;
		pMem = new TELEM[bf.MemLen];
	}
	this->BitLen = bf.BitLen;
	for (int i = 0; i < MemLen; i++) {
		this->pMem[i] = bf.pMem[i];
	}
	return *this;
}

bool TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return false;
	else {
		if (MemLen != bf.MemLen)
			return false;
		else {
			for (int i = 0; i < MemLen - 1; i++) {
				if (pMem[i] != bf.pMem[i])
					return false;
			}
			for (int i = (MemLen - 1) * 32; i < BitLen; i++) {
				if (GetBit(i) != bf.GetBit(i))
					return false;
			}
			return true;
		}
	}
}


int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	return*this;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	return* this;
}

TBitField TBitField::operator~(void) // отрицание
{
	return*this;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	return istr;

}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	return ostr;

}
