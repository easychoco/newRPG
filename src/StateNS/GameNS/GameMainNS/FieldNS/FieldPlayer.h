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
	//���W�x�N�g��
	Vector2* point;

	//�����ł�1000�{�����l��ێ�����
	const int pointRate = MyData::vectorRate;

	//���������߂�bitmask�Ŏg�p����
	const unsigned char f_right = 0b0001;
	const unsigned char f_left  = 0b0010;
	const unsigned char f_down  = 0b0100;
	const unsigned char f_up    = 0b1000;

	//�摜�̔ԍ�
	int mGraphNum;

	//�摜
	int mImg[24];

	int mTime;

	//==================
	// ����private�֐�
	//==================
	//�ړ�
	void move(const FieldNS::Main*);
	void move(float speed, const FieldNS::Main*);
};




}
}
}
}