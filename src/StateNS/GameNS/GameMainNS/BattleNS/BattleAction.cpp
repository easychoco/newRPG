#include "BattleAction.h"

#include "BattleStringController.h"
#include "BattleActor.h"

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
	mTime = 0;
}

bool ActionController::update(StringController* _sController, vector<Actor*> _actors)
{
	mTime++;

	if (mTime == 30)
	{
		//���b�Z�[�W�����ƒǉ�

		string s = _actors[actions.front()->fromID]->status.name;
		s += " ��";

		if (actions.front()->act == Action::Actions::ACT_ATTACK) s += "��������";
		else if (actions.front()->act == Action::Actions::ACT_MAGIC) s += "�܂ق�";
		_sController->addMessage(s);
	}
	else if (mTime == 60)
	{
		//�_���[�W�v�Z
		int damage_value{ 0 };

		//��������
		if (actions.front()->act == Action::Actions::ACT_ATTACK)
		{
			damage_value = _actors[actions.front()->fromID]->status.attack - _actors[actions.front()->toID]->status.defence;
		}
		//�܂ق�
		else if (actions.front()->act == Action::Actions::ACT_MAGIC)
		{
			damage_value = _actors[actions.front()->fromID]->status.mattack - _actors[actions.front()->toID]->status.mdefence;
		}

		//�_���[�W�ʂ͍ŏ���1
		damage_value = max(damage_value, 1);

		//�_���[�W
		_actors[actions.front()->toID]->damage(damage_value);

		//���b�Z�[�W�쐬�ƒǉ�
		string s = _actors[actions.front()->toID]->status.name;
		s += " �� ";
		s += std::to_string(damage_value);
		s += "�̃_���[�W!";
		_sController->addMessage(s);

		//���L�����̍s����
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

//�s���̏������I�������return true
bool ActionController::processAction()
{
	return true;
}




}
}
}
}

