#pragma once

#include "..\..\..\..\Data.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace FieldNS{


class Player
{
public:
	Player();
	~Player();
	void initialize();
	void update();
	void draw() const;
	const Vector2* getVector2() { return point; }
private:
	//座標ベクトル
	//内部では1000倍した値を保持する
	Vector2* point;
};




}
}
}
}