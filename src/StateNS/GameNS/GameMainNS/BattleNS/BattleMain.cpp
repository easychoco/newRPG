#include "BattleMain.h"
#include "BattleStage.h"
#include "BattleActor.h"
#include "BattleAction.h"
#include "BattlePlayer.h"
#include "BattleEnemy.h"
#include "BattleStringController.h"
#include "..\FieldNS\FieldMain.h"

#include "..\..\..\..\KeyInput.h"

#include<fstream>


namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace BattleNS {


Main::Main(Vector2 _player) : mPlayerPos(_player)
{
	initialize();
}

Main::~Main()
{
	actors.clear();
	actors.shrink_to_fit();

	players.clear();
	players.shrink_to_fit();

	enemies.clear();
	enemies.shrink_to_fit();

	SAFE_DELETE(stage);
	SAFE_DELETE(aController);
	SAFE_DELETE(sController);
	SAFE_DELETE(mChild);
}

void Main::initialize()
{
	stage = new Stage();
	aController = new ActionController();
	sController = new StringController();

	mTime = 0;

	sController->addMessage("�܂��̂������ꂽ�I");
	
	//�o�g���ɎQ������L�����N�^�[�̔z����쐬
	addActor();

	//�͂��߂͍s������̏��
	mChild = new FirstAnimation(actors);
}

Child* Main::update(const GameMain* _parent)
{

	Child* next = this;

	mTime++;

	//�w�i�̏���
	stage->update();

	//BattleChild* nextChild = 0;

	//�o�g���̏���(State�p�^�[��)
	BattleChild*  nextChild = mChild->update(aController, sController, actors);

	//�o�g���̃V�[�P���X�X�V
	if (mChild != nextChild)
	{
		SAFE_DELETE(mChild);
		mChild = nextChild;
	}

	if (Input_S() || mChild->goField())
		next = new FieldNS::Main(mPlayerPos);


	return next;
}

void Main::draw() const
{
	stage->draw();

	drawStatus(0, 330 - players.size() * 40, players);//330�̓��b�Z�[�W�g�̏�[
	drawStatus(440, 330 - enemies.size() * 40, enemies);//330��(ry
	sController->draw();
	aController->draw();

	mChild->draw(aController);
}




//========================================================================
// ����private�֐�
//========================================================================
void Main::addActor()
{
	//Actor�z��̍쐬

	//player��enemy�ʂ��Ŏg��ID
	int ID{ 0 };

	//�t�@�C���ǂݍ���
	std::ifstream player_in("Data/Text/PlayerExp.txt");
	if (!player_in)
	{
		using std::endl;
		std::ofstream out("Data/Text/PlayerExp.txt");
		out << "0 player 0" << endl;
		out << "1 magic 0" << endl;
		out << "2 macho 0" << endl;
		out << "3 healer 0" << endl;
		out.close();
		player_in.open("Data/Text/PlayerExp.txt");
	}

	using CharacterSpec::p_spec;

	//��l���ǂݍ����vector�ɒǉ�
	while (player_in)
	{
		int _ID{ -10 };
		string name{ "dummy" };
		int exp { 0 };

		player_in >> _ID >> name >> exp;

		//�ǂݍ��݂����Ă�����break
		if (player_in.eof())break;

		//ID����v����L������T��
		auto player = std::find_if(p_spec.begin(), p_spec.end(),
			[_ID](auto &spec) { return (spec.ID == _ID); });

		if (player == p_spec.end())
		{
			//�Ώۂ̃L�����N�^�[�����Ȃ�������I��
			assert(!"�t�@�C�����s���ł�");
			exit(0);
		}

		//100�͎��̃��x���܂ł̕K�v�o���l
		int lv = 1 + exp / CharacterSpec::nextExp;
		
		int h{ -10 }, a{ -10 }, b{ -10 }, c{ -10 }, d{ -10 }, s{ -10 };

		//�\�͒l���v�Z
		h = calcHP(player->h, lv);
		a = calcStatus(player->a, lv);
		b = calcStatus(player->b, lv);
		c = calcStatus(player->c, lv);
		d = calcStatus(player->d, lv);
		s = calcStatus(player->s, lv);

		//�񕜗ʂ��v�Z
		int r = h - abs(a - c);
		r = max(r / 3, min(a, c));

		Actor::Status status{ ID, name, false, h, a, b, c, d, r, s };
		actors.push_back(new Player(status, exp));

		ID++;
	}

	assert(actors.size() != 0 && "�t�@�C�����s���ł�");
	player_in.close();

	//�G��1~4��
	short ene_num = 1 + GetRand(3);

	for (int i = 0; i < ene_num; i++)
	{
		string name = "�Ă�" + std::to_string(i + 1);
		Actor::Status e{ ID++, name.c_str(), true, 10, 10, 10, 10, 10, 10, 10 };
actors.push_back(new Enemy(e, 5));
	}

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
	int right = _x + 210;

	//�g��`��
	DrawBox(_x, _y, right, bottom, MyData::GLAY, true);

	//���O�Ƒ̗͂�`��
	short i = 0;
	for (auto &actor : _actor)
	{
		//5�Ƃ�7�Ƃ��͗v�E������
		DrawFormatString(_x + 10, _y + 3 + 40 * i, MyData::BLACK, "%s %d / %d", actor->status.name.c_str(), actor->getHP(), actor->status.maxHP);
		DrawBox(_x + 5, _y + 40 * i + 20, _x + 200, _y + 40 * i + 30, MyData::WHITE, false);
		DrawBox(_x + 7, _y + 40 * i + 22, _x + 7 + 191 * actor->getHP() / actor->status.maxHP, _y + 40 * i + 28, MyData::GREEN, true);
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
// FirstAnimation�N���X
//========================================================================
FirstAnimation::FirstAnimation(vector<Actor*> gomi)
{
	initialize();
}

FirstAnimation::~FirstAnimation()
{
	SAFE_DELETE(mChild);
}

void FirstAnimation::initialize()
{
	mTime = 0;

	//�ǂ̃A�j���[�V�����ɂ��邩�𗐐��Ō���
	auto seed = GetRand(3);

	switch (seed)
	{
	case 0:mChild = new Anime1(); break;
	case 1:mChild = new Anime2(); break;
	case 2:mChild = new Anime3(); break;
	case 3:mChild = new Anime4(); break;
	default:assert(!"�s����Anime");
	}
}

//�����͎g��Ȃ�
BattleChild* FirstAnimation::update(ActionController*, StringController*, vector<Actor*> _actors)
{
	BattleChild* next = this;

	mTime++;
	if (mTime > 60)next = new Decide(_actors);

	return next;

}

void FirstAnimation::draw(ActionController*) const
{
	mChild->draw(mTime);
}

void FirstAnimation::Anime1::draw(int _time) const
{
	DrawBox(0, 0, 640, 480 - _time * 8, MyData::BLACK, true);
}

void FirstAnimation::Anime2::draw(int _time) const
{
	DrawBox(0, _time * 8, 640, 480, MyData::BLACK, true);
}

void FirstAnimation::Anime3::draw(int _time) const
{
	int draw_x1{ _time * 16 / 3 };//16 / 3 = 320 / 60
	int draw_y1{ _time * 4 };
	int draw_x2{ 640 - _time * 16 / 3 };//16 / 3 = 320 / 60
	int draw_y2{ 480 - _time * 4 };
	DrawBox(draw_x1, draw_y1, draw_x2, draw_y2, MyData::BLACK, true);
}

void FirstAnimation::Anime4::draw(int _time) const
{
	//�ŏ���0, _time��60��255
	int val{ 255 * _time / 60 };
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - val);
	DrawBox(0, 0, 640, 480, GetColor(val, val, val), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
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
	doneNum += (players[doneNum])->attack(_sController, enemies, players);

	//�S�Ă�player�̍s�������܂�����
	if(doneNum >= (int)players.size())
	{
		//�G�̍s�������߂�
		for (auto& ene : enemies)
		{
			ene->attack(_sController, enemies, players);
		}

		while (!act_que.empty())
		{
			//����Ă��Ȃ�������ActionController�ɒǉ�
			if (act_que.front()->isAlive())
			{
				//�����Ă��Ȃ��Ȃ�
				_aController->addAction((act_que.front())->getAction());
				assert(act_que.front()->getAction() && "�s����action");
			}

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
	(players[doneNum])->draw(enemies, players);
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

	//�o�g���I��
	if (finBattle(_actors))
	{
		mFinTime++;
		updateMessage(_sController, true);
		
		if (mFinTime == 105)next = new Result(180);
	}
	else 	//�o�g����
	{
		bool battleDone = _aController->update(_sController, _actors);

		//�����Ă�����
		if (_aController->escapeBattle())
		{
			return new Result(0);
		}

		//�s���I����
		//�^�[���I���Ɠ����Ƀo�g�����I������ꍇ�͍s���I���������ɏI���
		if (battleDone && !finBattle(_actors))
		{
			next = new Decide(_actors);
		}
	}
	
	return next;
}

void Battle::draw(ActionController* _aController) const
{
	_aController->draw();
}


//========================================================================
// ����private�֐�
//========================================================================
bool Battle::finBattle(const vector<Actor*> _actors) const 
{
	bool f_enemy{ false };
	bool f_player{ false };

	//f_player��f_enemy�ɂ��ꂼ��isAlive()�𑫂�(�_���a)
	for(auto* act : _actors) 
	{
		if (act->status.isEnemy)f_enemy |= act->isAlive();
		else f_player |= act->isAlive();
	}

	//f_enemy��f_player�ɂ���...
	//Player��Enemy�̂ǂ��炩��HP�����ׂă[���Ȃ�false�̂܂�
	//HP���[���łȂ�Actor����ł������true�ɂȂ�
	//�ǂ��炩��false�Ȃ�true���Ԃ����
	return !(f_player & f_enemy);
}

void Battle::updateMessage(StringController* _sController, bool _win)
{
	if (mFinTime == 45)
	{
		//��������
		if(_win)_sController->addMessage("�Ă������������I");
		//�܂�����
		else _sController->addMessage("�܂��Ă��܂���...");
	}
}

int Battle::calcExp(vector<Actor*> _actors)
{
	int value = 0;
	for (auto& act : _actors)
	{
		value += act->getExp();
	}
	return value;
}


//========================================================================
// Result�N���X
//========================================================================
Result::Result(int _exp) :
mGetExp(_exp)
{
	initialized = false;
}

Result::~Result()
{
	players.clear();
	players.shrink_to_fit();
}

void Result::initialize(vector<Actor*> _actors)
{
	mTime = 0;

	//ResultStatus��������
	for (auto& act : _actors)
	{
		if(!act->status.isEnemy)players.push_back(new ResultStatus(act, mGetExp));
	}
	
	mImg = LoadGraph("Data/Image/player_up.png");
	mBackImg = LoadGraph("Data/Image/BattleBackTmp.png");

	initialized = true;
}

BattleChild* Result::update(ActionController* _aController, StringController* _sController, vector<Actor*> _actors)
{
	if (!initialized)initialize(_actors);

	BattleChild* next = this;

	mTime++;

	for (auto& player : players)
	{
		player->update();
	}

	//Field�ɍs���O�ɃZ�[�u
	if (goField())saveData();

	return next;
}

void Result::draw(ActionController* _aController) const
{
	DrawFormatString(0, 60, MyData::WHITE, "Result");
	DrawGraph(0, 0, mBackImg, true);
	
	if (players.size() >= 1)players[0]->draw(0, 0);
	if (players.size() >= 2)players[1]->draw(320, 0);
	if (players.size() >= 3)players[2]->draw(0, 240);
	if (players.size() >= 4)players[3]->draw(320, 240);
}

//���̃V�[�P���X�ɍs����
bool Result::goField() const
{
	bool goNext = false;

	for (auto& player : players)
	{
		goNext |= player->goNext();
	}
	
	//2�b�o���C���x���A�b�v�A�j���[�V�������I��邩
	return (mTime > 120 && goNext) || (mGetExp == 0 && mTime > 30);
}

void Result::saveData()
{
	std::ofstream fout("Data/Text/PLayerExp.txt");
	for (auto& player : players)
	{
		fout << player->getSaveString() << std::endl;
	}
}


//=================================
//�����N���X
//=================================
Result::ResultStatus::ResultStatus(Actor* _actor, int _mGetExp)
{
	//�����G�̃��[�h
	mImg = LoadGraph("Data/Image/player_up.png");

	initialize(_actor, _mGetExp);
}

void Result::ResultStatus::initialize(Actor* _actor, int _mGetExp)
{
	ID = _actor->status.ID;
	name = _actor->status.name;

	mLevelUp = false;
	mLevelTime = 60;

	//���̌o���l�o�[�̈ʒu
	mNowExp = _actor->getExp() % CharacterSpec::nextExp;

	//�ڕW�̌o���l�o�[�̈ʒu
	mAfterExp = mNowExp + _mGetExp;

	//�o���l�̑����v
	mAllExp = _actor->getExp() + _mGetExp;

}

void Result::ResultStatus::update()
{
	mTime++;

	//mAfterExp�܂Ōo���l�𑝂₷
	mNowExp = min(mNowExp + 1, mAfterExp);

	//�o���l�������ς��ɂȂ����烌�x���A�b�v
	if (mNowExp % CharacterSpec::nextExp == (CharacterSpec::nextExp - 1) &&
		mNowExp != mAfterExp)
	{
		mLevelUp = true;
		mLevelTime = 0;
		mTime = 0;
	}

	mLevelTime += mLevelUp;
	mLevelUp = mLevelTime < 30;
}

void Result::ResultStatus::draw(int _x, int _y) const
{
	//�w�i�Ɨ����G��`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
	DrawBox(_x + 5, _y + 5, _x + 320, _y + 240, MyData::BLUE, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawGraph(_x + 130, _y, mImg, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 200);

	//�o���l�o�[�̏����ꏊ���v�Z
	int exp = mNowExp % CharacterSpec::nextExp;
	int draw_x = 186 * (exp + 1) / CharacterSpec::nextExp;

	//�o���l�o�[��`��
	DrawBox(_x + 10, _y + 190, _x + 200, _y + 230, MyData::WHITE, false);
	DrawBox(_x + 12, _y + 192, _x + 12 + draw_x, _y + 228, MyData::WHITE, true);

	//���x���A�b�v!
	if(mLevelUp)DrawFormatString(_x + 20, _y + 170, MyData::WHITE, "Level Up!");
}

string Result::ResultStatus::getSaveString()
{
	return std::to_string(ID) + " " + name + " " + std::to_string(mAllExp);
}

bool Result::ResultStatus::goNext() const
{
	//���x���A�b�v����2�b���return
	return mTime > 120;
}



}
}
}
}