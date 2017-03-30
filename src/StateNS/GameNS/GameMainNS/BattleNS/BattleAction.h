#pragma once

#include "..\..\..\..\Data.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace BattleNS {

class StringController;
class Actor;

class Action
{
public:
	//�N�����s��
	enum Actions
	{
		ACT_ATTACK,
		ACT_MAGIC,
		ACT_SPECIAL,

		ACT_NONE,
	};

	//�����C����C�s�����e
	Action(int, int, Actions);
	~Action();

	//�s������Actor��ID
	const int fromID;

	//�Ώۂ�Actor��ID
	const int toID;

	//�s�����e
	const Actions act;
	
};


class ActionController
{
public:
	ActionController();
	~ActionController();
	void initialize();
	bool update(StringController*, vector<Actor*>);
	void draw() const;
	void addAction(Action* a);
	bool processAction();

	int mTime;

	//�s���L���[
	queue<Action*> actions;

private:
	void updateMessage(StringController*, vector<Actor*>);
	void updateDamage(StringController*, vector<Actor*>);
};















}
}
}
}