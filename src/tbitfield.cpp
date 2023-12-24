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
	{
		throw - 1;
	}
	else
	{
		BitLen = len;
		MemLen = len / 32 + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = 0;
		}
	}
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
	pMem = nullptr;
	BitLen = 0;
	MemLen = 0;
}

int TBitField::GetMemIndex(const int n) const
{
	if (n > BitLen - 1 || n < 0)
	{
		throw " index out of range";
	}
	return n / 32;
}

TELEM TBitField::GetMemMask(const int n) const
{
	TELEM t = 1;
	int shift = n % 32;
	TELEM res = t << shift;
	return res;

}

int TBitField::GetLength(void) const // получить длину (к-во битов)
{

	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n > BitLen - 1 || n < 0)
	{
		throw " index out of range";
	}
	TELEM m = GetMemMask(n);
	int ind = GetMemIndex(n);
	pMem[ind] = pMem[ind] | m;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n > BitLen - 1 || n < 0)
	{
		throw " index out of range";
	}
	TELEM m = ~(GetMemMask(n));
	int ind = GetMemIndex(n);
	pMem[ind] = pMem[ind] & m;

}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n > BitLen - 1 || n < 0)
	{
		throw " index out of range";
	}
	TELEM m = (GetMemMask(n));
	int ind = GetMemIndex(n);
	TELEM res = pMem[ind] & m;
	return res;
}

// битовые операции
bool TBitField::operator!=(const TBitField& bf) const // сравнение
{
	if (*this == bf)
		return false;
	return true;
}
TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	if (*this != bf)
	{
		delete[]pMem;
		pMem = new TELEM[bf.MemLen];
		MemLen = bf.MemLen;
	}
	BitLen = bf.BitLen;
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

bool TBitField::operator==(const TBitField& bf) const // сравнение
{
	if (BitLen != bf.BitLen)
	{
		return false;

	}
	for (int i = 0; i < MemLen - 1; i++)
	{
		if (pMem[i] != bf.pMem[i])
		{
			return false;
		}
	}
	for (int i = (MemLen - 1) * 32; i < BitLen; i++)
	{
		if (GetBit(i) != bf.GetBit(i))
		{
			return false;
		}
	}
	return true;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	if (BitLen > bf.BitLen)
	{
		TBitField ans(*this);
		for (int i = 0; i < bf.MemLen; i++)
		{
			ans.pMem[i] = pMem[i] | bf.pMem[i];
		}
		for (int i = (bf.MemLen - 1) * 32 + bf.BitLen % 32; i < BitLen; i++)
		{
			if (GetBit(i))
			{
				ans.SetBit(i);
			}
			else {
				ans.ClrBit(i);
			}
		}
		return ans;
	}
	else if (bf.BitLen > BitLen)
	{
		TBitField ans(bf);
		for (int i = 0; i < MemLen; i++)
		{
			ans.pMem[i] = pMem[i] | bf.pMem[i];
		}
		for (int i = (MemLen - 1) * 32 + BitLen % 32; i < bf.BitLen; i++)
		{
			if (bf.GetBit(i))
			{
				ans.SetBit(i);
			}
			else
			{
				ans.ClrBit(i);
			}
		}
		return ans;
	}
	else {
		TBitField ans(bf);
		for (int i = 0; i < MemLen; i++)
		{
			ans.pMem[i] = pMem[i] | bf.pMem[i];
		}
		return ans;
	}
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	if (BitLen > bf.BitLen)
	{
		TBitField ans(*this);
		for (int i = 0; i < bf.MemLen; i++)
		{
			ans.pMem[i] = bf.pMem[i] & pMem[i];
		}
		for (int i = (bf.MemLen - 1) * 32 + bf.BitLen % 32; i < BitLen; i++)
		{
			ans.ClrBit(i);
		}
		return ans;
	}
	else if (bf.BitLen > BitLen)
	{
		TBitField ans(bf);
		for (int i = 0; i < MemLen; i++)
		{
			ans.pMem[i] = bf.pMem[i] & pMem[i];
		}
		for (int i = (MemLen - 1) * 32 + BitLen % 32; i < bf.BitLen; i++)
		{
			ans.ClrBit(i);
		}
		return ans;
	}
	else {
		TBitField ans(bf);
		for (int i = 0; i < MemLen; i++)
		{
			ans.pMem[i] = pMem[i] & bf.pMem[i];
		}
		return ans;
	}

}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField res(*this);
	for (int i = 0; i < MemLen; i++)
	{
		res.pMem[i] = ~(res.pMem[i]);
	}
	return res;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	char a;
	for (int i = 0; i < bf.MemLen; i++)
	{
		bf.pMem[i] = 0;
	}
	for (int i = 0; i < bf.BitLen; i++)
	{

		istr >> a;
		if (a == '1')
		{
			bf.SetBit(i);
		}
		else
		{
			if (a == '0')
			{
				bf.ClrBit(i);
			}
			else
			{
				break;
			}
		}
	}
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
	{
		if (bf.GetBit(i))
		{
			ostr << '1';

		}
		else
		{
			ostr << '0';
		}
	}
	return ostr;

}




//TBitField::TBitField(int len)
//{
//	if (len <= 0)
//		throw "Ошибка: отрицательное значение длины";
//	MemLen = len / 32 + 1;
//	BitLen = len;
//	pMem = new TELEM[MemLen];
//	for (int i = 0; i < MemLen; i++) {
//		pMem[i] = 0;
//	}
//}
//
//TBitField::TBitField(const TBitField& bf) // конструктор копирования
//{
//	MemLen = bf.MemLen;
//	BitLen = bf.BitLen;
//	pMem = new TELEM[MemLen];
//	for (int i = 0; i < MemLen; i++) {
//		pMem[i] = bf.pMem[i];
//	}
//}
//
//TBitField::~TBitField()
//{
//	delete[] pMem;
//}
//
//int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
//{
//	int idx;
//	idx = n / 32;
//	return idx;
//}
//
//TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
//{
//	TELEM t = 1;
//	char shift = n % 32;
//	TELEM res = t << shift;
//	return res;
//}
//
//// доступ к битам битового поля
//
//int TBitField::GetLength(void) const // получить длину (к-во битов)
//{
//	return BitLen;
//}
//
//void TBitField::SetBit(const int n) // установить бит
//{
//	if (n < 0 || n >= BitLen)
//		throw "Incorrect number";
//	TELEM m = GetMemMask(n);
//	int idx = GetMemIndex(n);
//	pMem[idx] = pMem[idx] | m;
//}
//
//void TBitField::ClrBit(const int n) // очистить бит
//{
//	if (n < 0 || n >= BitLen)
//		throw "Ошибка: отрицательное значение индекса бита";
//	TELEM m = ~(GetMemMask(n));
//	int idx = GetMemIndex(n);
//	pMem[idx] = pMem[idx] & m;
//}
//
//int TBitField::GetBit(const int n) const // получить значение бита
//{
//	if (n < 0 || n >= BitLen)
//		throw "Ошибка: отрицательное значение индекса бита";
//	TELEM m = GetMemMask(n);
//	int idx = GetMemIndex(n);
//	TELEM res = m & pMem[idx];
//	return res;
//}
//
//// битовые операции
//
//TBitField& TBitField::operator=(const TBitField& bf) // присваивание
//{
//	if (this->MemLen != bf.MemLen) {
//		delete[] this->pMem;
//		pMem = new TELEM[bf.MemLen];
//	}
//	this->BitLen = bf.BitLen;
//	for (int i = 0; i < MemLen; i++) {
//		this->pMem[i] = bf.pMem[i];
//	}
//	return *this;
//}
//
//bool TBitField::operator==(const TBitField& bf) const // сравнение
//{
//	if (BitLen != bf.BitLen)
//		return false;
//	else {
//		if (MemLen != bf.MemLen)
//			return false;
//		else {
//			for (int i = 0; i < MemLen - 1; i++) {
//				if (pMem[i] != bf.pMem[i])
//					return false;
//			}
//			for (int i = (MemLen - 1) * 32; i < BitLen; i++) {
//				if (GetBit(i) != bf.GetBit(i))
//					return false;
//			}
//			/*for (int i = 0; i < BitLen; i++) {
//				if (GetBit(i) != bf.GetBit(i))
//					return false;
//			}*/
//			return true;
//		}
//	}
//}
//
//
//bool TBitField::operator!=(const TBitField& bf) const // сравнение
//{
//	if (*this == bf)
//		return false;
//	else
//		return true;
//}
//
//TBitField TBitField::operator|(const TBitField& bf) // операция "или"
//{
//	int mlen = bf.BitLen;
//	if (BitLen > bf.BitLen)
//		mlen = BitLen;
//	TBitField res(mlen);
//	for (int i = 0; i < MemLen - 1; i++) {
//		res.pMem[i] = pMem[i];
//	}
//	for (int i = (MemLen - 1) * 32; i < BitLen; i++) {
//		if (GetBit(i) == 0)
//			res.ClrBit(i);
//		else if (GetBit(i) != 0)
//			res.SetBit(i);
//	}
//	for (int i = 0; i < bf.MemLen; i++) {
//		res.pMem[i] = bf.pMem[i] | res.pMem[i];
//	}
//
//	return res;
//}
//
//TBitField TBitField::operator&(const TBitField& bf) // операция "и"
//{
//	int mlen = bf.BitLen;
//	int minlen = BitLen;
//	if (BitLen > bf.BitLen) {
//		mlen = BitLen;
//		minlen = bf.BitLen;
//	}
//	TBitField CopyMin(mlen);
//	TBitField CopyMax(mlen);
//	TBitField Max(mlen);
//	TBitField Min(mlen);
//	if (BitLen == minlen) {
//		/*for (int i = 0; i < MemLen - 1; i++) {
//			CopyMin.pMem[i] = pMem[i];
//
//		}*/
//		//cout << "Copying  " << res << endl;
//		for (int i = 0; i < BitLen; i++) {
//			if (GetBit(i) == 0)
//				CopyMin.ClrBit(i);
//			else if (GetBit(i) != 0)
//				CopyMin.SetBit(i);
//		}
//		for (int i = BitLen; i < mlen; i++)
//			CopyMin.ClrBit(i);
//
//
//		for (int i = 0; i < bf.MemLen - 1; i++) {
//			CopyMax.pMem[i] = pMem[i];
//		}
//		for (int i = (bf.MemLen - 1) * 32; i < bf.BitLen; i++) {
//			if (GetBit(i) == 0)
//				CopyMax.ClrBit(i);
//			else if (GetBit(i) != 0)
//				CopyMax.SetBit(i);
//		}
//	}
//	else if (bf.BitLen == minlen) {
//		/*CopyMin = bf;
//		cout << CopyMin;*/
//		for (int i = 0; i < bf.MemLen - 1; i++) {
//			CopyMin.pMem[i] = bf.pMem[i];
//
//		}
//		//cout << "Copying  " << res << endl;
//		for (int i = 0; i < bf.BitLen; i++) {
//			if (bf.GetBit(i) == 0)
//				CopyMin.ClrBit(i);
//			else if (bf.GetBit(i) != 0)
//				CopyMin.SetBit(i);
//		}
//		cout << "Copy min til bf.Bitlen:  " << CopyMin << endl;
//		for (int i = bf.BitLen; i < mlen; i++)
//			CopyMin.ClrBit(i);
//		cout << "Copy min til mlen:  " << CopyMin << endl;
//		
//		for (int i = 0; i < MemLen - 1; i++) {
//			CopyMax.pMem[i] = pMem[i];
//		}
//		for (int i = (MemLen - 1) * 32; i < BitLen; i++) {
//			if (GetBit(i) == 0)
//				CopyMax.ClrBit(i);
//			else if (GetBit(i) != 0)
//				CopyMax.SetBit(i);
//		}
//		int j = 0;
//		
//		for (int i = BitLen - 1; i > 0; i--) {
//			if (CopyMax.GetBit(i) == 0)
//				Max.ClrBit(j);
//			else if (CopyMax.GetBit(i) != 0)
//				Max.SetBit(j);
//			j++;
//		}
//		j = 0;
//		for (int i = bf.BitLen - 1; i > 0; i--) {
//			if (CopyMin.GetBit(i) == 0)
//				Min.ClrBit(j);
//			else if (CopyMin.GetBit(i) != 0)
//				Min.SetBit(j);
//			j++;
//		}
//	}
//	cout << "secBf =  " << *this << endl;
//	cout << "negFirstBf = 1110" << endl;
//	
//	cout << "Max:  " << Max << endl;
//
//	cout << "bf :: " << bf << endl;
//	cout << "CMix:  " << CopyMin << endl;
//	cout << "Min:  " << Min << endl;
//	
//	TBitField res(mlen);
//	/*for (int i = 0; i < MemLen - 1; i++) {
//		res.pMem[i] = pMem[i];
//
//	}
//	cout << "Copying  " << res << endl;
//	for (int i = (MemLen - 1) * 32; i < BitLen; i++) {
//		if (GetBit(i) == 0)
//			res.ClrBit(i);
//		else if (GetBit(i) != 0)
//			res.SetBit(i);
//	}
//	cout << "secBf = 00011000" << endl;
//	cout << "negFirstBf = 1110" << endl;
//	cout << "Entering  " << res << endl;
//	for (int i = 0; i < MemLen - 1; i++) {
//		res.pMem[i] = pMem[i];
//		
//	}
//	cout << "Copying  " << res << endl;
//	for (int i = (MemLen - 1) * 32; i < BitLen; i++) {
//		if (GetBit(i) == 0)
//			res.ClrBit(i);
//		else if (GetBit(i) != 0)
//			res.SetBit(i);
//	}
//	cout << "Copying 2:  " << res << endl;
//	for (int i = 0; i < bf.MemLen; i++) {
//		res.pMem[i] = bf.pMem[i] & res.pMem[i];
//	}*/
//	for (int i = 0; i < CopyMax.MemLen; i++) {
//		res.pMem[i] = Min.pMem[i] & Max.pMem[i];
//	}
//	cout << "Result:  " << res << endl;
//
//	return res;
//}
//
//TBitField TBitField::operator~(void) // отрицание
//{
//	TBitField res(BitLen);
//	for (int i = 0; i < MemLen; i++)
//		res.pMem[i] = ~pMem[i];
//	return res;
//}
//
//// ввод/вывод
//
//istream& operator>>(istream& is, TBitField& bf) // ввод
//{
//	char a;
//	for (int i = 0; i < bf.MemLen; i++) {
//		bf.pMem[i] = 0;
//	}
//	for (int i = 0; i < bf.BitLen; i++) {
//		is >> a;
//		if (a == '1')
//			bf.SetBit(i);
//		else if (a == '0')
//			bf.ClrBit(i);
//		else break;
//	}
//	return is;
//
//}
//
//ostream& operator<<(ostream& os, const TBitField& bf) // вывод
//{
//	for (int i = 0; i < bf.BitLen; i++)
//	{
//		if (bf.GetBit(i))
//			os << '1';
//		else
//			os << '0';
//	}
//	os << endl;
//	return os;
//
//}
