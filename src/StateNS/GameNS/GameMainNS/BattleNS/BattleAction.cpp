#include "BattleAction.h"

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

}

void ActionController::update()
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

