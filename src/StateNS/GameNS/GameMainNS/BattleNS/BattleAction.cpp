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
}

bool ActionController::update(StringController* _sController, vector<Actor*> _actors)
{
	if (_actors.empty())return true;

	//�U���҂��|��Ă�����U���͖���
	if (!_actors[actions.front()->fromID]->isAlive())
	{
		actions.pop();
	}

	mTime++;

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

//�s���̏������I�������return true
bool ActionController::processAction()
{
	return true;
}

//========================================================================
// ����private�֐�
//========================================================================
void ActionController::updateMessage(StringController* _sController, vector<Actor*> _actors)
{
	//���b�Z�[�W�����ƒǉ�
	string s = _actors[actions.front()->fromID]->status.name;
	s += " �� ";

	//ATTACK��MAGIC���Ń��b�Z�[�W�ύX
	if (actions.front()->act == Action::Actions::ACT_ATTACK) s += "��������";
	else if (actions.front()->act == Action::Actions::ACT_MAGIC) s += "�܂ق�";
	_sController->addMessage(s);
}

void ActionController::updateDamage(StringController* _sController, vector<Actor*> _actors)
{
	int from = actions.front()->fromID;
	int to = actions.front()->toID;

	//�U���Ώۂ��|��Ă�����ʂ̃L������_��
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
	string s = _actors[to]->status.name;
	s += " �� ";
	s += std::to_string(damage_value);
	s += "�̃_���[�W!";
	_sController->addMessage(s);
}




}
}
}
}

