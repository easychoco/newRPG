#pragma once

#include "BattleActor.h"
#include "..\..\..\..\Data.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace BattleNS {

class SelectChild;

class Player : public Actor
{
public:
	Player(Status _s);
	~Player();
	void initialize();
	bool attack();
	void draw(int, int) const;


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
	const array<Action::Actions, 4 > toAction
	{
		Action::Actions::ACT_ATTACK,
		Action::Actions::ACT_MAGIC,
		Action::Actions::ACT_SPECIAL,
		Action::Actions::ACT_SPECIAL,
	};


};










}
}
}
}