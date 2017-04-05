#pragma once

#include "BattleAction.h"
#include <string>

using std::string;

namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace BattleNS {

class StringController;
class Action;

//��������Action�֕ϊ�����z��
const array< Action::Actions, 4 > toAction
{
	Action::Actions::ACT_ATTACK,
	Action::Actions::ACT_MAGIC,
	Action::Actions::ACT_RECOVER,
	Action::Actions::ACT_ESCAPE,
};

class Actor
{
public:
	// ID, name, isEnemy, maxHP, atk, def, matk, mdef, recover, speed
	struct Status {
		const int ID;
		string name;
		const bool isEnemy;
		int maxHP;
		int attack, defence;
		int mattack, mdefence;
		int recover;
		int speed;
	};

	//�������Ƀ\�[�g���邩��,�\�[�g�p�̊֐����`
	static bool cmp(Actor* mine, Actor* other)
	{
		return ( (mine->status).speed > (other->status).speed );
	}

	//�R���X�g���N�^ Status, exp
	Actor(Status _s, int _exp) : status(_s), exp(_exp) { HP = status.maxHP; act = 0; };
	virtual ~Actor() {};

	//�s�������܂������ǂ�����Ԃ�
	virtual bool attack(StringController*, const vector<Actor*>&, const vector<Actor*>&) = 0;
	virtual void draw(vector<Actor*>, vector<Actor*>) const = 0;
	virtual void initialize() = 0;

	bool isAlive() const { return HP > 0; }
	void damage(int _value) { this->HP = max(this->HP - _value, 0); }
	void recover(int _value) { this->HP = min(status.maxHP, this->HP + _value);	}
	int getHP() const { return HP; }
	int getExp() const { return exp; }
	Action* getAction() const { return act; };
	void setName(string _name) { status.name = _name; }

	Status status;

protected:
	int HP;
	const int exp;
	Action* act;
};




}
}
}
}
