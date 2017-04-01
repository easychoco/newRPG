#include "BattleEnemy.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace BattleNS {


Enemy::Enemy(Status _s, int _exp) :
Actor(_s, _exp)
{
	initialize();
}

Enemy::~Enemy()
{
	SAFE_DELETE(act);
}

void Enemy::initialize()
{
	//この関数は各ターンの初めにも呼ばれる
	//actはターンごとに新しくするから,以前のものはdelete
	SAFE_DELETE(act);
}

bool Enemy::attack(StringController* _sController, const vector<Actor*>& _players)
{
	//乱数で行動を決定
	act = new Action(status.ID, GetRand(0), Action::Actions::ACT_ATTACK);
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
