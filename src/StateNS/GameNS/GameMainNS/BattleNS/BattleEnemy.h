#pragma once

#include "BattleActor.h"
#include "..\..\..\..\Data.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace BattleNS {

class Enemy : public Actor
{
public:
	Enemy(Status);
	~Enemy();
	void initialize();
	bool attack(StringController*, const vector<Actor*>& _players);
	void draw(vector<Actor*>) const;

private:

};
















}
}
}
}