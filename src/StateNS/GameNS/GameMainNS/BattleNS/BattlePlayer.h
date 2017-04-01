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
	bool attack(StringController*, const vector<Actor*>& _enemies);
	void draw(vector<Actor*>) const;


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










}
}
}
}