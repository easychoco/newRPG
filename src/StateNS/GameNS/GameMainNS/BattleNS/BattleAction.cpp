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
	while (!actions.empty())actions.pop();
}

void ActionController::initialize()
{
	mTime = 0;
	isEscape = false;
}

bool ActionController::update(StringController* _sController, vector<Actor*> _actors)
{
	if (_actors.empty())return true;


	mTime++;

	//�U���҂��|��Ă�����U���͖���
	if (mTime <= 1 && !(_actors[actions.front()->fromID]->isAlive()))
	{
		mTime = 0;
		this->actions.pop();
		return actions.empty();
	}

	if (mTime == 30) 
	{
		//�����̂��������I
		updateMessage(_sController, _actors);
	}

	else if (mTime == 60)
	{
		//������~�̃_���[�W�I
		updateDamage(_sController, _actors);

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

bool ActionController::escapeBattle()
{
	return isEscape && mTime > 20;
}


//========================================================================
// ����private�֐�
//========================================================================
void ActionController::updateMessage(StringController* _sController, vector<Actor*> _actors)
{
	//���b�Z�[�W�����ƒǉ�

	//�܂����O��ǉ�
	string s = _actors[actions.front()->fromID]->status.name;
	s += " �� ";

	//�񕜂Ȃ�
	if (actions.front()->act == Action::Actions::ACT_RECOVER)
	{
		s += "�����ӂ��I";
		_sController->addMessage(s);
		return;
	}

	//������Ȃ�
	if (actions.front()->act == Action::Actions::ACT_ESCAPE)
	{
		s += "�ɂ���I";
		_sController->addMessage(s);
		return;
	}

	//�U�������@�Ȃ�

	//ATTACK��MAGIC���Ń��b�Z�[�W�ύX
	if (actions.front()->act == Action::Actions::ACT_ATTACK) s += "��������";
	else if (actions.front()->act == Action::Actions::ACT_MAGIC) s += "�܂ق�";
	_sController->addMessage(s);

	return;
}

void ActionController::updateDamage(StringController* _sController, vector<Actor*> _actors)
{
	string s = "";

	//������Ȃ�
	if (actions.front()->act == Action::Actions::ACT_ESCAPE)
	{
		s += _actors[actions.front()->fromID]->status.name;
		isEscape = true;

		//���b�Z�[�W�ǉ�
		s += " �� �ɂ��������I";
		_sController->addMessage(s);
		return;
	}

	int from = actions.front()->fromID;
	int to = actions.front()->toID;

	//�񕜂Ȃ�
	if (actions.front()->act == Action::Actions::ACT_RECOVER)
	{
		s += _actors[to]->status.name;
		//��
		_actors[to]->recover(_actors[from]->status.recover);

		//���b�Z�[�W�ǉ�
		s += " �� ";
		s += std::to_string(_actors[from]->status.recover);
		s += " �����ӂ��I";
		_sController->addMessage(s);
		return;
	}

	//�U�������@�Ȃ�

	//�U���Ώۂ�����Ă�����ʂ̃L������_��
	if (!_actors[to]->isAlive())
	{
		int i = 0;

		//�U���҂��v���C���[�Ȃ�
		if (!_actors[from]->status.isEnemy)
		{
			//�|��Ă��Ȃ��G�𑖍�
			while ((!_actors[i]->status.isEnemy || !_actors[i]->isAlive()) && i + 1 < (int)_actors.size())
			{
				i++;
			}
			to = i;
		}
		//�U���҂��G�Ȃ�
		else
		{
			//�|��Ă��Ȃ��v���C���[�𑖍�
			while ((_actors[i]->status.isEnemy || !_actors[i]->isAlive()) && i + 1 < (int)_actors.size())
			{
				i++;
			}
			to = i;
		}
	}


	//�_���[�W�v�Z
	int damage_value{ 0 };

	//��������
	if (actions.front()->act == Action::Actions::ACT_ATTACK)
	{
		damage_value = _actors[from]->status.attack - _actors[to]->status.defence;
	}
	//�܂ق�
	else if (actions.front()->act == Action::Actions::ACT_MAGIC)
	{
		damage_value = _actors[from]->status.mattack - _actors[to]->status.mdefence;
	}

	//�_���[�W�ʂ͍ŏ���1
	damage_value = max(damage_value, 1);

	//�_���[�W
	_actors[to]->damage(damage_value);

	//���b�Z�[�W�쐬�ƒǉ�
	s += _actors[to]->status.name;
	s += " �� ";
	s += std::to_string(damage_value);
	s += "�̃_���[�W!";
	_sController->addMessage(s);
}




}
}
}
}

