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

//数字からActionへ変換する配列
const array< Action::Actions, 4 > toAction
{
	Action::Actions::ACT_ATTACK,
	Action::Actions::ACT_MAGIC,
	Action::Actions::ACT_SPECIAL,
	Action::Actions::ACT_SPECIAL,
};

class Actor
{
public:
	// ID, name, isEnemy, maxHP, atk, def, matk, mdef, speed
	struct Status {
		const int ID;
		const char* name;
		const bool isEnemy;
		const int maxHP;
		const int attack, defence;
		const int mattack, mdefence;
		const int speed;
	};

	//速い順にソートするから,ソート用の関数を定義
	static bool cmp(Actor* mine, Actor* other)
	{
		return ((mine->status).speed > (other->status).speed);
	}

	//コンストラクタ
	Actor(Status _s) : status(_s) { HP = status.maxHP; act = 0; };
	virtual ~Actor() {};

	//行動が決まったかどうかを返す
	virtual bool attack(StringController*, const vector<Actor*>&) = 0;
	virtual void draw(vector<Actor*>) const = 0;
	virtual void initialize() = 0;
	Action* getAction() const { return act; };
	bool isAlive() const { return HP > 0; }
	void damage(int _value) { this->HP = max(this->HP - _value, 0); }
	int getHP() const { return HP; }

	const Status status;

protected:
	int HP;
	Action* act;
};




}
}
}
}
