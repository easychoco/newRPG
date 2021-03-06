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
	//起こす行動
	enum Actions
	{
		ACT_ATTACK,
		ACT_MAGIC,
		ACT_RECOVER,
		ACT_ESCAPE,

		ACT_NONE,
	};

	//自分，相手，行動内容
	Action(int, int, Actions);
	~Action();

	//行動するActorのID
	const int fromID;

	//対象のActorのID
	const int toID;

	//行動内容
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
	bool escapeBattle();

	unsigned mTime;


private:
	//行動キュー
	queue<Action*> actions;

	//行動開始のメッセージ
	void updateMessage(StringController*, vector<Actor*>);

	//行動結果のメッセージ
	void updateDamage(StringController*, vector<Actor*>);

	bool isEscape;
};















}
}
}
}