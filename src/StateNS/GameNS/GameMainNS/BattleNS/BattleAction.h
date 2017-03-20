#pragma once

#include "..\..\..\..\Data.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace BattleNS {

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
	void update();
	void draw() const;
	void addAction(Action* a);
	bool processAction();

	//�s���L���[
	queue<Action*> actions;
};















}
}
}
}