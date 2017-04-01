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
	//���̊֐��͊e�^�[���̏��߂ɂ��Ă΂��
	//act�̓^�[�����ƂɐV�������邩��,�ȑO�̂��̂�delete
	SAFE_DELETE(act);
}

bool Enemy::attack(StringController* _sController, const vector<Actor*>& _players)
{
	//�����ōs��������
	act = new Action(status.ID, GetRand(0), Action::Actions::ACT_ATTACK);
	return true;
}

void Enemy::draw(vector<Actor*>) const
{

}


//========================================================================
// ����private�֐�
//========================================================================





}
}
}
}
