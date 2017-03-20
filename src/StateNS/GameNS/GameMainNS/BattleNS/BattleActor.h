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

	//速い順にソートするから演算子を定義
	bool operator < (Actor& other) const
	{
		return ((this->status).speed < other.status.speed);
	}

	Actor(Status _s) : status(_s) { HP = status.maxHP; act = 0; };
	virtual ~Actor() {};

	//行動が決まったかどうかを返す
	virtual bool attack() = 0;
	virtual void draw(int _x, int _y) const = 0;
	Action* getAction() { return act; };
	bool isAlive() const { return HP > 0; }
	void damage(int _damage) { this->HP -= _damage; }

	const Status status;

protected:
	int HP;
	Action* act;
};




}
}
}
}
