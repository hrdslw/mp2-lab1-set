// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int _MaxPower) : bf(_MaxPower)
{
    MaxPower = _MaxPower;
}

// конструктор копирования
TSet::TSet(const TSet &s) : bf(s.bf), MaxPower(s.MaxPower)
{}

// конструктор преобразования типа
TSet::TSet(const TBitField & _bf) : bf(_bf), MaxPower(_bf.GetLength())
{}

TSet::operator TBitField()
{
    return this->bf;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return this->MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return 0;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    bf.SetBit(Elem);
    //
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    MaxPower = s.MaxPower;
    bf = s.bf;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if (MaxPower != s.MaxPower || bf != s.bf)
        return 0;
    return 1;
}

int TSet::operator!=(const TSet &s) const // сравнение
{   
    if (*this == s)
        return 0;
    else
        return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    

    return *this;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet res(*this);
    res.InsElem(Elem);
    return res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    return *this;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    return *this;
}

TSet TSet::operator~(void) // дополнение
{
    return *this;
}

// перегрузка ввода/вывода

istream &operator>>(istream &is, TSet &s) // ввод
{
    char b1;
    int a;
    is >> b1;
    while (b1 != ')') {
        is >> a;
        s.InsElem(a);
        is >> b1;
    }
    return is;
}

ostream& operator<<(ostream &os, const TSet &s) // вывод
{
    os << '{';
    for (int i = 0; i < s.MaxPower - 1; i++) {
        if (s.IsMember(i)) {
            os << i << ' ';
        }
    }
    if (s.IsMember(s.MaxPower - 1))
        os << s.MaxPower - 1;
    os << '}';
    return os;
}
