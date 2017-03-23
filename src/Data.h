#pragma once

#include "DXLib.h"
#include <cassert>
#include <array>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>


using std::array;
using std::string;
using std::queue;
using std::vector;


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

//�}�b�v�̃T�C�Y
//32x32pixcel����40x30�`�b�v
const int MAP_WIDTH = 1280;
const int MAP_HEIGHT = 960;

//1�s�N�Z�����ǂꂾ���g�����邩
const int vectorRate = 1000;

//�F
const unsigned BLACK = GetColor(0, 0, 0);
const unsigned GLAY = GetColor(128, 128, 128);
const unsigned WHITE = GetColor(255, 255, 255);
const unsigned RED = GetColor(255, 0, 0);
const unsigned GREEN = GetColor(0, 255, 0);
const unsigned BLUE = GetColor(0, 0, 255);



//�����l2�����x�N�g��
class Vector2
{
public:
	int x;
	int y;

	Vector2() :
		Vector2(0, 0)
	{

	}
	Vector2(int _x, int _y)
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
	const Vector2 operator * (int other) const
	{
		return Vector2(x * other, y * other);
	}
	const Vector2 operator / (int other) const
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

	
	static const Vector2 ZERO;
	static const Vector2 LEFT;
	static const Vector2 RIGHT;
	static const Vector2 UP;
	static const Vector2 DOWN;
	

};

}

using MyData::Vector2;


