#pragma once

#include "DXLib.h"
#include <array>
#include <cassert>



//�~����
#define Pi 3.14159265358979f


//delete��0�|�C���^
#define SAFE_DELETE(p){\
	delete (p);\
	(p) = 0;\
}

//delete[]��0�|�C���^
#define SAFE_DELETE_ARRAY(p){\
	delete[] (p);\
	(p) = 0;\
}

//========================================
//�~�����̌v�Z(�R���p�C�����v�Z)
//zero division�͉�����Ă��Ȃ����璍��
//========================================
constexpr float pi(float num)
{
	return Pi * num;
}


//========================================
//Data.cpp/h�Ŏg�p���閼�O���
//========================================
namespace MyData{



//��ʂ̒��S���W
const int CX = 320;
const int CY = 240;

//�F
const unsigned BLACK = GetColor(0, 0, 0);
const unsigned WHITE = GetColor(255, 255, 255);
const unsigned RED = GetColor(255, 0, 0);
const unsigned GREEN = GetColor(0, 255, 0);
const unsigned BLUE = GetColor(0, 0, 255);



//2�����x�N�g��
template <typename T>
class Vector2
{
public:
	T x;
	T y;

	Vector2() :
		Vector2(0, 0)
	{

	}
	Vector2(T _x, T _y)
	{
		this->x = _x;
		this->y = _y;
	}


	bool isZero() const
	{
		return *this == Vector2::ZERO;
	}

	Vector2& operator += (const Vector2& other)
	{
		return *this = *this + other;
	}
	Vector2& operator -= (const Vector2& other)
	{
		return *this = *this - other;
	}
	const Vector2 operator + (const Vector2& other)
	{
		return Vector2(x + other.x, y + other.y);
	}
	const Vector2 operator - (const Vector2& other)
	{
		return Vector2(x - other.x, y - other.y);
	}
	const Vector2 operator * (T other) const
	{
		return Vector2(x * other, y * other);
	}
	const Vector2 operator / (T other) const
	{
		return Vector2(x / other, y / other);
	}
	bool operator == (const Vector2& other) const
	{
		return (x == other.x) && (y == other.y);
	}
	bool operator != (const Vector2& other) const
	{
		return !(*this == other);
	}

	/*
	static const Vector2<T> ZERO;
	static const Vector2<int> LEFT;
	static const Vector2<int> RIGHT;
	static const Vector2<int> UP;
	static const Vector2<int> DOWN;
	*/

};

}


using MyData::Vector2;

