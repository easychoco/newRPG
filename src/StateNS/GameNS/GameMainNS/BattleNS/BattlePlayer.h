#pragma once

#include "BattleActor.h"
#include "..\..\..\..\Data.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace BattleNS {

class Player : public Actor
{
public:
	Player(Status, int);
	~Player();
	void initialize();
	bool attack(StringController*, const vector<Actor*>& _enemies, const vector<Actor*>&);
	void draw(vector<Actor*>, vector<Actor*>) const;
	
	bool mPrePush;

private:
	enum SelectState
	{
		SELECT_MOVE,
		SELECT_TARGET,

	};
	SelectState mState;
	int mMove;
	int mImg;

	int mCursorPos;
	bool mFirstCome;

};


namespace CharacterSpec
{
	//���̃��x���܂ł�exp
	static const int nextExp = 100;

	//�v���C���[�̎푰�l
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
		Status{ 0, 20, 20, 20, 20, 20, 20 }, //�䂤����
		Status{ 1, 15,  5, 10, 40, 20, 30 }, //�܂ق�����
		Status{ 2, 30, 30, 30, 10, 10, 10 }, //�ԂƂ���
		Status{ 3, 40, 10, 20, 10, 20, 20 }, //���񂶂�
	};
}


}
}
}
}