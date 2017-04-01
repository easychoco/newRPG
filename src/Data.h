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


//円周率
#define Pi 3.14159265358979f


//deleteと0ポインタ
#define SAFE_DELETE(p){\
	delete (p);\
	(p) = 0;\
}

//delete[]と0ポインタ
#define SAFE_DELETE_ARRAY(p){\
	delete[] (p);\
	(p) = 0;\
}

//========================================
//円周率の計算(コンパイル時計算)
//zero divisionは回避していないから注意
//========================================
constexpr float pi(float num)
{
	return Pi * num;
}


//========================================
//Data.cpp/hで使用する名前空間
//========================================
namespace MyData{



//画面の中心座標
const int CX = 320;
const int CY = 240;

//マップのサイズ
//32x32pixcelだと40x30チップ
const int MAP_WIDTH = 1280;
const int MAP_HEIGHT = 960;

//1ピクセルをどれだけ拡張するか
const int vectorRate = 1000;

//色
const unsigned BLACK = GetColor(0, 0, 0);
const unsigned GLAY = GetColor(128, 128, 128);
const unsigned WHITE = GetColor(255, 255, 255);
const unsigned RED = GetColor(255, 0, 0);
const unsigned GREEN = GetColor(0, 255, 0);
const unsigned BLUE = GetColor(0, 0, 255);



//整数値2次元ベクトル
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


namespace CharacterSpec
{
	//次のレベルまでのexp
	static const int nextExp = 100;

	//プレイヤーの種族値
	//ID, h, a, b, c, d, s
	struct Status
	{
		const int ID;
		int h;
		int a;
		int b;
		int c;
		int d;
		int s;
	};

	static const std::array< Status, 4> p_spec
	{
		Status{ 0, 20, 20, 20, 20, 20, 20 }, //ゆうしゃ
		Status{ 1, 15,  5, 10, 40, 20, 30 }, //まほうつかい
		Status{ 2, 30, 30, 30, 10, 10, 10 }, //ぶとうか
		Status{ 3, 40, 10, 20, 10, 20, 20 }, //けんじゃ
	};
}