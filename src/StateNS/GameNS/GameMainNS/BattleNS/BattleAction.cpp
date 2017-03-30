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
	while (!actions.empty())actions.pop();
}

void ActionController::initialize()
{
	mTime = 0;
}

bool ActionController::update(StringController* _sController, vector<Actor*> _actors)
{
	if (_actors.empty())return true;

	//攻撃者が倒れていたら攻撃は無し
	if (!_actors[actions.front()->fromID]->isAlive())
	{
		actions.pop();
	}

	mTime++;

	if (mTime == 30) 
	{
		//○○のこうげき！
		updateMessage(_sController, _actors);
	}

	else if (mTime == 60)
	{
		//○○に~のダメージ！
		updateDamage(_sController, _actors);

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

//========================================================================
// 内部private関数
//========================================================================
void ActionController::updateMessage(StringController* _sController, vector<Actor*> _actors)
{
	//メッセージ生成と追加
	string s = _actors[actions.front()->fromID]->status.name;
	s += " の ";

	//ATTACKかMAGICかでメッセージ変更
	if (actions.front()->act == Action::Actions::ACT_ATTACK) s += "こうげき";
	else if (actions.front()->act == Action::Actions::ACT_MAGIC) s += "まほう";
	_sController->addMessage(s);
}

void ActionController::updateDamage(StringController* _sController, vector<Actor*> _actors)
{
	int from = actions.front()->fromID;
	int to = actions.front()->toID;

	//攻撃対象が倒れていたら別のキャラを狙う
	if (!_actors[to]->isAlive())
	{
		int i = 0;

		//攻撃者がプレイヤーなら
		if (!_actors[from]->status.isEnemy)
		{
			//倒れていない敵を走査
			while ((!_actors[i]->status.isEnemy || !_actors[i]->isAlive()) && i + 1 < (int)_actors.size())
			{
				i++;
			}
			to = i;
		}
		//攻撃者が敵なら
		else
		{
			//倒れていないプレイヤーを走査
			while ((_actors[i]->status.isEnemy || !_actors[i]->isAlive()) && i + 1 < (int)_actors.size())
			{
				i++;
			}
			to = i;
		}
	}


	//ダメージ計算
	int damage_value{ 0 };

	//こうげき
	if (actions.front()->act == Action::Actions::ACT_ATTACK)
	{
		damage_value = _actors[from]->status.attack - _actors[to]->status.defence;
	}
	//まほう
	else if (actions.front()->act == Action::Actions::ACT_MAGIC)
	{
		damage_value = _actors[from]->status.mattack - _actors[to]->status.mdefence;
	}

	//ダメージ量は最小で1
	damage_value = max(damage_value, 1);

	//ダメージ
	_actors[to]->damage(damage_value);

	//メッセージ作成と追加
	string s = _actors[to]->status.name;
	s += " に ";
	s += std::to_string(damage_value);
	s += "のダメージ!";
	_sController->addMessage(s);
}




}
}
}
}

