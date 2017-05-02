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

void Enemy::setData(char* filename, int _x, int _y)
{
	mImg = LoadGraph(filename);
	assert(mImg != -1 && "�G�摜�ǂݍ��݃G���[");

	draw_x = _x;
	draw_y = _y;
}

bool Enemy::attack(StringController* _sController, const vector<Actor*>& _enemies, const vector<Actor*>& _players)
{
	//�U�����@�͎����̃p�����[�^�ˑ��Ō���
	act = new Action(status.ID, GetRand(_players.size() - 1), decideAttack());
	return true;
}

void Enemy::draw(vector<Actor*>, vector<Actor*>) const
{
	if(isAlive())DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImg, true, false);
}


//========================================================================
// ����private�֐�
//========================================================================
Action::Actions Enemy::decideAttack()
{
	Action::Actions ret = Action::Actions::ACT_NONE;

	int a = this->status.attack;
	int d = this->status.mattack;

	int rand = GetRand(a + d);

	//a / (a + d) �� d / (a + d) �̊m���ōU�������@
	if (rand < a)ret = Action::Actions::ACT_ATTACK;
	else ret = Action::Actions::ACT_MAGIC;

	return ret;
}




}
}
}
}
