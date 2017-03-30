#include "BattleMain.h"
#include "BattleStage.h"
#include "BattleActor.h"
#include "BattleAction.h"
#include "BattlePlayer.h"
#include "BattleEnemy.h"
#include "BattleStringController.h"
#include "..\MiddleMain.h"

#include "..\..\..\..\Data.h"
#include "..\..\..\..\KeyInput.h"

#include<fstream>


namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace BattleNS {


Main::Main(const GameMain* _parent)
{
	initialize(_parent->players);
}

Main::~Main()
{

}

void Main::initialize(vector<GameMainNS::GameMain::Status> _s)
{

	stage = new Stage();
	aController = new ActionController();
	sController = new StringController();

	mNext = GameScene::SCENE_NONE;
	mTime = 0;

	sController->addMessage("�܂��̂������ꂽ�I");
	
	//�o�g���ɎQ������L�����N�^�[�̔z����쐬
	addActor(_s);

	//�͂��߂͍s������̏��
	mChild = new Decide(actors);
}

Child* Main::update(const GameMain* _parent)
{

	Child* next = this;

	mTime++;

	//�w�i�̏���
	stage->update();

	BattleChild* nextChild = 0;

	//�o�g���̏���(State�p�^�[��)
	//if(!finBattle())
		nextChild = mChild->update(aController, sController, actors);

	//�o�g���̃V�[�P���X�X�V
	if (mChild != nextChild)
	{
		SAFE_DELETE(mChild);
		mChild = nextChild;
	}

	if(mChild->goField())next = new MiddleMain(GameScene::SCENE_FIELD, 0);


	return next;
}

void Main::draw() const
{
	stage->draw();
	if (!finBattle())
	{
		drawStatus(0, 330 - players.size() * 40, players);//330�̓��b�Z�[�W�g�̏�[
		drawStatus(440, 330 - enemies.size() * 40, enemies);//330��(ry
		sController->draw();
		aController->draw();
	}
	mChild->draw(aController);
}


//========================================================================
// ����private�֐�
//========================================================================
void Main::addActor(vector<GameMainNS::GameMain::Status> _s)
{
	//Actor�z��̍쐬

	//player��enemy�ʂ��Ŏg��ID
	int ID{ 0 };

	//�t�@�C���ǂݍ���
	std::ifstream player_in("Data/Text/PlayerExp.txt");

	//��l���ǂݍ����vector�ɒǉ�
	while (player_in)
	{
		int _ID{ -10 };
		string name{"dummy"};
		int exp { 0 };

		player_in >> _ID >> name >> exp;

		//�ǂݍ��݂����Ă�����break
		if (player_in.eof())break;

		//ID����v����L������T��
		auto player = std::find_if(_s.begin(), _s.end(),
			[_ID](auto &status) { return (status.ID == _ID); });

		if (player == _s.end())
		{
			//�Ώۂ̃L�����N�^�[�����Ȃ�������I��
			assert(!"�t�@�C�����s���ł�");
			exit(0);
		}

		//1000�͎��̃��x���܂ł̕K�v�o���l
		int lv = 1 + exp / 1000;
		
		int h{ -10 }, a{ -10 }, b{ -10 }, c{ -10 }, d{ -10 }, s{ -10 };

		//�\�͒l���v�Z
		h = calcHP(player->h, lv);
		a = calcStatus(player->a, lv);
		b = calcStatus(player->b, lv);
		c = calcStatus(player->c, lv);
		d = calcStatus(player->d, lv);
		s = calcStatus(player->s, lv);


		Actor::Status _s{ ID, name, false, h, a, b, c, d, s };
		actors.push_back(new Player(_s));

		ID++;
	}
	
	//�G�̒ǉ�
	Actor::Status e1{ ID++, "�Ă�����", true, 100, 100, 100, 100, 100, 100 };
	actors.push_back(new Enemy(e1, 5));

	Actor::Status e2{ ID++, "�Ă��ł�", true, 100, 100, 100, 100, 100, 100 };
	actors.push_back(new Enemy(e2, 5));


	//players��enemies�z��̍쐬
	//�Q�Ƃɂ��actors�Ɠ����C���X�^���X���g��
	for (auto &actor : actors)
	{
		if (actor->status.isEnemy)enemies.push_back(actor);
		else players.push_back(actor);
	}
}

void Main::drawStatus(int _x, int _y, const vector<Actor*>& _actor) const
{
	//�`�悷��͈͂̉��[
	int bottom = _y + _actor.size() * 40;

	//�Ă��Ƃ���200
	int right = _x + 200;

	//�g��`��
	DrawBox(_x, _y, right, bottom, MyData::GLAY, true);

	//���O�Ƒ̗͂�`��
	short i = 0;
	for (auto &actor : _actor)
	{
		//5�Ƃ�7�Ƃ��͗v�E������
		DrawFormatString(_x + 10, _y + 3 + 40 * i, MyData::BLACK, "%s %d / %d", actor->status.name.c_str(), actor->getHP(), actor->status.maxHP);
		DrawBox(_x + 5, _y + 40 * i + 20, _x + right - 5, _y + 40 * i + 30, MyData::WHITE, false);
		DrawBox(_x + 7, _y + 40 * i + 22, _x + 7 + (right - 14) * actor->getHP() / actor->status.maxHP, _y + 40 * i + 28, MyData::GREEN, true);
		i++;
	}
}

bool Main::finBattle() const
{
	bool eFin = false;
	for (auto& ene : enemies)
	{
		eFin |= ene->isAlive();
	}

	bool pFin = false;
	{
		for (auto& player : players)
		{
			pFin |= player->isAlive();
		}
	}
	return !(eFin & pFin);
}

int Main::calcHP(int _HP, int _lv) const
{
	return _HP * _lv * 2 / 7 + 10;
}

int Main::calcStatus(int _value, int _lv) const
{
	return _value * _lv / 7 + 5;
}



//========================================================================
// ��������BattleChild����
//========================================================================







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
			if (actor->status.isEnemy)enemies.push_back(actor);
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

	//�o�g�����I����Ă�����Result��
	if (finBattle(_actors))return new Result();

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

bool Battle::finBattle(const vector<Actor*> _actors) const 
{
	bool f_enemy{ false };
	bool f_player{false};

	//f_player��f_enemy�ɂ��ꂼ��isAlive()�𑫂�(�_���a)
	for_each(_actors.begin(), _actors.end(), 
		[&](Actor* act) 
	{
		if (act->status.isEnemy)f_enemy |= act->isAlive();
		else f_player |= act->isAlive();
	});

	//f_enemy��f_player�ɂ���...
	//Player��Enemy�̂ǂ��炩��HP�����ׂă[���Ȃ�false�̂܂�
	//HP���[���łȂ�Actor����ł������true�ɂȂ�
	//�ǂ��炩��false�Ȃ�true���Ԃ����
	return !(f_player & f_enemy);
}


//========================================================================
// Result�N���X
//========================================================================
Result::Result()
{
	initialize();
}

Result::~Result()
{

}

void Result::initialize()
{
	mImg = LoadGraph("Data/Image/player_up.png");
	mBackImg = LoadGraph("Data/Image/BattleBackTmp.png");

	mTime = 0;
}

BattleChild* Result::update(ActionController* _aController, StringController* _sController, vector<Actor*> _actors)
{
	BattleChild* next = this;

	mTime++;

	return next;
}

void Result::draw(ActionController* _aController) const
{
	DrawFormatString(0, 60, MyData::WHITE, "Result");
	DrawGraph(0, 0, mBackImg, true);
	drawResult(0, 0, mImg);
	drawResult(320, 0, mImg);
	drawResult(0, 240, mImg);
	drawResult(320, 240, mImg);
}

bool Result::goField() const
{
	return mTime > 60;
}

void Result::drawResult(int _x, int _y, int _img) const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
	DrawBox(_x + 5, _y + 5, _x + 320, _y + 240, MyData::BLUE, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawGraph(_x + 130, _y, _img, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 200);

}


}
}
}
}