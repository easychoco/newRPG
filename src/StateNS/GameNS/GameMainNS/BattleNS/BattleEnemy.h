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
	//status, exp
	Enemy(Status, int);
	~Enemy();
	void initialize();
	void setData(char* filename, int x, int y);
	bool attack(StringController*, const vector<Actor*>& _enemies, const vector<Actor*>& _players);
	void draw(vector<Actor*>, vector<Actor*>) const;
	int getDrawX() { return draw_x; }

private:
	int mImg;

	int draw_x;
	int draw_y;

	Action::Actions decideAttack();

};











}
}
}
}