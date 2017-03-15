#pragma once

#include "..\..\..\..\Data.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace FieldNS{

class Main;

class Player
{
public:
	Player();
	~Player();
	void initialize();
	void update(const FieldNS::Main*);
	void draw() const;
	const Vector2* getVector2() const { return point; }
private:
	//座標ベクトル
	Vector2* point;

	//内部では1000倍した値を保持する
	const int pointRate = MyData::vectorRate;

	//方向を決めるbitmaskで使用する
	const unsigned char f_right = 0b0001;
	const unsigned char f_left  = 0b0010;
	const unsigned char f_down  = 0b0100;
	const unsigned char f_up    = 0b1000;

	//画像の番号
	int mGraphNum;

	//画像
	int mImg[24];

	int mTime;

	//==================
	// 内部private関数
	//==================
	//移動
	void move(const FieldNS::Main*);
	void move(float speed, const FieldNS::Main*);
};




}
}
}
}