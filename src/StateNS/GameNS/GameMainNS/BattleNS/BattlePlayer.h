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
	int getDrawX() { return 0; }

	bool mPrePush;

private:
	enum SelectState
	{
		SELECT_MOVE,
		SELECT_TARGET,
	};
	SelectState mState;
	int mMove;
	int mPointerImg[4];
	int mTime;
	int eneNum;

	int mCursorPos;
	bool mFirstCome;

};



}
}
}
}