#include "BattleAction.h"

#include "BattleStringController.h"
#include "BattleActor.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace BattleNS {

//========================================================================
// Actionクラス
//========================================================================
Action::Action(int _fromID, int _toID, Actions _act):
fromID(_fromID),
toID(_toID),
act(_act)
{

}

Action::~Action()
{

}


//========================================================================
// ActionControllerクラス
//========================================================================
ActionController::ActionController()
{
	initialize();
}

ActionController::~ActionController()
{

}

void ActionController::initialize()
{
	mTime = 0;
}

bool ActionController::update(StringController* _sController, vector<Actor*> _actors)
{
	mTime++;

	if (mTime == 30)
	{
		//メッセージ生成と追加

		string s = _actors[actions.front()->fromID]->status.name;
		s += " の";

		if (actions.front()->act == Action::Actions::ACT_ATTACK) s += "こうげき";
		else if (actions.front()->act == Action::Actions::ACT_MAGIC) s += "まほう";
		_sController->addMessage(s);
	}
	else if (mTime == 60)
	{
		//ダメージ計算
		int damage_value{ 0 };

		//こうげき
		if (actions.front()->act == Action::Actions::ACT_ATTACK)
		{
			damage_value = _actors[actions.front()->fromID]->status.attack - _actors[actions.front()->toID]->status.defence;
		}
		//まほう
		else if (actions.front()->act == Action::Actions::ACT_MAGIC)
		{
			damage_value = _actors[actions.front()->fromID]->status.mattack - _actors[actions.front()->toID]->status.mdefence;
		}

		//ダメージ量は最小で1
		damage_value = max(damage_value, 1);

		//ダメージ
		_actors[actions.front()->toID]->damage(damage_value);

		//メッセージ作成と追加
		string s = _actors[actions.front()->toID]->status.name;
		s += " に ";
		s += std::to_string(damage_value);
		s += "のダメージ!";
		_sController->addMessage(s);

		//次キャラの行動へ
		mTime = 0;
		actions.pop();
	}

	return actions.empty();
}

void ActionController::draw() const
{

}

void ActionController::addAction(Action* _a)
{
	actions.push(_a);
}

//行動の処理が終わったらreturn true
bool ActionController::processAction()
{
	return true;
}




}
}
}
}

