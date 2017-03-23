#include "BattleEnemy.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace BattleNS {


Enemy::Enemy(Status _s) :
Actor(_s)
{
	initialize();
}

Enemy::~Enemy()
{
	SAFE_DELETE(act);
}

void Enemy::initialize()
{
	SAFE_DELETE(act);
}

bool Enemy::attack(StringController* _sController, const vector<Actor*>& _players)
{
	//乱数で行動を決定
	act = new Action(status.ID, GetRand(3), Action::Actions::ACT_ATTACK);
	return true;
}

void Enemy::draw(vector<Actor*>) const
{

}


//========================================================================
// 内部private関数
//========================================================================





}
}
}
}
