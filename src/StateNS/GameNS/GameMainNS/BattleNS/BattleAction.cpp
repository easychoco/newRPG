#include "BattleAction.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace BattleNS {

//========================================================================
// Action�N���X
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
// ActionController�N���X
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

//�s���̏������I�������return true
bool ActionController::processAction()
{
	return true;
}




}
}
}
}

