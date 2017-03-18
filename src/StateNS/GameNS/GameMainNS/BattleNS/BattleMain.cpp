#include "BattleMain.h"
#include "BattleStage.h"
#include "BattleActor.h"
#include "BattleAction.h"
#include "BattlePlayer.h"
#include "BattleStringController.h"

#include "..\..\..\..\Data.h"
#include "..\..\..\..\KeyInput.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace BattleNS {


Main::Main()
{
	initialize();
}

Main::~Main()
{

}

void Main::initialize()
{
	stage = new Stage();
	aController = new ActionController();
	sController = new StringController();

	mNext = GameScene::SCENE_NONE;
	mTime = 0;

	//���b�Z�[�W�ǉ�
	sController->addMessage("�䂤����͂ǂ�����H");
	sController->addMessage("���������ꂽ�I");
	sController->addMessage("line two");
	sController->addMessage("line one");


	//�o�g���ɎQ������L�����N�^�[�̔z����쐬
	addActor();

	//�f�������Ƀ\�[�g
	sort(actors.begin(), actors.end());

	//�͂��߂͍s������̏��
	mChild = new Decide(actors);


}

void Main::update(GameParent* _parent)
{
	mTime++;

	//�w�i�̏���
	stage->update();

	//if (mTime % 60 == 1)newTurn();

	//�o�g���̏���(State�p�^�[��)
	BattleChild* next = mChild->update(this);

	//�V�[�P���X�X�V
	if (mChild != next)
	{
		SAFE_DELETE(mChild);
		mChild = next;
	}

	//S�L�[�Ńt�B�[���h��
	if (Input_S())
		mNext = GameScene::SCENE_FIELD;

}

void Main::draw() const
{
	DrawFormatString(0, 40, MyData::WHITE, "BattleMain");
	stage->draw();
	mChild->draw();
	sController->draw();
}

//���̏�ʂ�Ԃ�
GameScene Main::changeScene()
{
	return mNext;
}

//ActionController��Action��ǉ�����
void Main::addAction(Action* a) { aController->addAction(a); }

//========================================================================
// ����private�֐�
//========================================================================
void Main::addActor()
{
	Actor::Status s = { 0, "me", false, 100, 10, 10, 10, 10, 5 };
	actors.push_back(new Player(s));

}

//========================================================================
// Decide�N���X
//========================================================================
Decide::Decide(vector<Actor*>& vec_act)
{
	initialize(vec_act);
}

Decide::~Decide() 
{
	while (!act_que.empty())act_que.pop();
}

//�e�^�[���̏��߂ɍs���鏈��
void Decide::initialize(vector<Actor*> vec_act)
{
	//�s�����̃L���[���쐬
	for (auto &act : vec_act)
	{
		act_que.push(act);
	}
}

BattleChild* Decide::update(Main* _main)
{
	BattleChild* next = this;

	//�U��������, �Ԃ�l�͌��܂������ǂ���
	bool doneAction = (act_que.front())->attack();

	//�U�������܂�����
	if (doneAction)
	{
		//ActionController�ɒǉ�
		_main->addAction((act_que.front())->getAction());

		//�擪��pop
		act_que.pop();

		//�o�g����ʂֈڍs
		if (act_que.empty())
		{
			next = new Battle();
		}
	}
	return next;
}

void Decide::draw() const
{

}


//========================================================================
// Battle�N���X
//========================================================================
Battle::Battle()
{
	initialize();
}

Battle::~Battle()
{

}

void Battle::initialize()
{

}

BattleChild* Battle::update(Main* _main)
{
	BattleChild* next = this;

	return next;
}

void Battle::draw() const
{

}



}
}
}
}