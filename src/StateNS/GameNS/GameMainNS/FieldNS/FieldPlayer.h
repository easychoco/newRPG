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
	//���W�x�N�g��
	//�����ł�1000�{�����l��ێ�����
	Vector2* point;
};




}
}
}
}