#include "BattleMain.h"
#include "BattleStage.h"
#include "BattleActor.h"
#include "BattleAction.h"
#include "BattlePlayer.h"
#include "BattleEnemy.h"
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

	//���b�Z�[�W������
	sController->addMessage("");
	sController->addMessage("");
	sController->addMessage("");
	sController->addMessage("");

	sController->addMessage("�܂��̂������ꂽ�I");
	
	//�o�g���ɎQ������L�����N�^�[�̔z����쐬
	addActor();

	//�͂��߂͍s������̏��
	mChild = new Decide(actors);
}

void Main::update(GameParent* _parent)
{
	mTime++;

	//�w�i�̏���
	stage->update();

	//�o�g���̏���(State�p�^�[��)
	BattleChild* next = mChild->update(aController, sController, actors);

	//�V�[�P���X�X�V
	if (mChild != next)
	{
		SAFE_DELETE(mChild);
		mChild = next;
	}

	//S�L�[�Ńt�B�[���h��
	if (Input_S() || finBattle())
		mNext = GameScene::SCENE_FIELD;

}

void Main::draw() const
{
	DrawFormatString(0, 40, MyData::WHITE, "BattleMain");
	stage->draw();
	drawStatus(0, 250, players);
	drawStatus(440, 250, enemies);
	sController->draw();
	mChild->draw(aController);
	aController->draw();
}

//���̏�ʂ�Ԃ�
GameScene Main::changeScene()
{
	return mNext;
}


//========================================================================
// ����private�֐�
//========================================================================
void Main::addActor()
{
	//Actor�z��̍쐬
	Actor::Status p1{ 0, "�v���C���[", false, 5100, 109, 80, 1000, 100, 100 };
	actors.push_back(new Player(p1));

	Actor::Status p2{ 1, "�v���C���[", false, 300, 100, 70, 5000, 510, 510 };
	actors.push_back(new Player(p2));

	Actor::Status e1{ 2, "�Ă�����", true, 100, 10, 10, 10, 10000, 10 };
	actors.push_back(new Enemy(e1));

	Actor::Status e2{ 3, "�Ă��ł�", true, 100, 10, 10, 10, 10000, 10 };
	actors.push_back(new Enemy(e2));


	//players��enemies�z��̍쐬
	//�Q�Ƃɂ��actors�Ɠ����C���X�^���X���g��
	for (auto &actor : actors)
	{
		if (actor->status.isEnemy && actor->isAlive())enemies.push_back(actor);
		else players.push_back(actor);
	}
}

void Main::drawStatus(int _x, int _y, const vector<Actor*>& _actor) const
{
	//�`�悷��͈͂̉��[
	int bottom = _y + players.size() * 40;

	//�Ă��Ƃ���200
	int right = _x + 200;

	//�g��`��
	DrawBox(_x, _y, right, bottom, MyData::GLAY, true);

	//���O�Ƒ̗͂�`��
	short i = 0;
	for (auto &actor : _actor)
	{
		//5�Ƃ�7�Ƃ��͗v�E������
		DrawFormatString(_x + 10, _y + 3 + 40 * i, MyData::BLACK, "%s %d / %d", actor->status.name, actor->getHP(), actor->status.maxHP);
		DrawBox(_x + 5, _y + 40 * i + 20, _x + right - 5, _y + 40 * i + 30, MyData::WHITE, false);
		DrawBox(_x + 7, _y + 40 * i + 22, _x + 7 + (right - 14) * actor->getHP() / actor->status.maxHP, _y + 40 * i + 28, MyData::GREEN, true);
		i++;
	}
}

bool Main::finBattle()
{
	bool fin = false;
	for (auto& ene : enemies)
	{
		fin |= ene->isAlive();
	}
	return !fin;
}



//========================================================================
// Decide�N���X
//========================================================================
Decide::Decide(vector<Actor*> vec_act)
{
	initialize(vec_act);
}

Decide::~Decide() 
{
	while (!act_que.empty())act_que.pop();

	enemies.clear();
	enemies.shrink_to_fit();

	players.clear();
	players.shrink_to_fit();
}

//�e�^�[���̏��߂ɍs���鏈��
void Decide::initialize(vector<Actor*>& vec_act)
{
	//�eact��������
	for (auto &act : vec_act)
	{
		act->initialize();
	}

	//enemy��player�̔z����쐬
	for (auto &actor : vec_act)
	{
		if (actor->isAlive())
		{
			if (actor->status.isEnemy && actor->isAlive())enemies.push_back(actor);
			else players.push_back(actor);
		}
	}

	//�f�������Ƀ\�[�g
	std::sort(vec_act.begin(), vec_act.end(), &Actor::cmp);

	//�s�����̃L���[���쐬
	for (auto &act : vec_act)
	{
		act_que.push(act);
	}
}

BattleChild* Decide::update(ActionController* _aController, StringController* _sController, vector<Actor*> _actors)
{
	BattleChild* next = this;

	//�U��������, �Ԃ�l�͌��܂������ǂ���(boolean)
	doneNum += (players[doneNum])->attack(_sController, enemies);		

	//�S�Ă�player�̍s�������܂�����
	if(doneNum >= (int)players.size())
	{
		//�G�̍s�������߂�
		for (auto& ene : enemies)
		{
			ene->attack(_sController, players);
		}

		while (!act_que.empty())
		{
			//ActionController�ɒǉ�
			_aController->addAction((act_que.front())->getAction());

			//�擪��pop
			act_que.pop();
		}

		//�o�g����ʂֈڍs
		next = new Battle();
		
	}
	return next;
}

void Decide::draw(ActionController* gomi) const
{
	(players[doneNum])->draw(enemies);
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

BattleChild* Battle::update(ActionController* _aController, StringController* _sController, vector<Actor*> _actors)
{
	BattleChild* next = this;

	bool battleDone = _aController->update(_sController, _actors);

	if (battleDone)
	{
		next = new Decide(_actors);
	}

	return next;
}

void Battle::draw(ActionController* _aController) const
{
	_aController->draw();
}



}
}
}
}