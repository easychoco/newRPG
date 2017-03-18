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
	Player(Status _s);
	~Player();
	void initialize();
	bool attack();
	void draw(int, int) const;

private:
	int mImg;
};
















}
}
}
}