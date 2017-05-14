#include "BattleMain.h"
#include "BattleStage.h"
#include "BattleActor.h"
#include "BattleAction.h"
#include "BattlePlayer.h"
#include "BattleEnemy.h"
#include "BattleStringController.h"
#include "..\FieldNS\FieldMain.h"
#include "..\CharacterData.h"

#include "..\..\..\..\KeyInput.h"

#include<fstream>


namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace BattleNS {

//�퓬BGM
int BattleChild::mBGM;


Main::Main(Vector2 _player, array<int, 4> _party, int _eneLevel) : 
	mPlayerPos(_player),
	party(_party)
{
	initialize(_eneLevel);
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

void Main::initialize(int _eneLevel)
{
	stage = new Stage();
	aController = new ActionController();
	sController = new StringController();

	mTime = 0;

	sController->addMessage("�܂��̂������ꂽ�I");
	
	//�o�g���ɎQ������L�����N�^�[�̔z����쐬
	addActor(_eneLevel);

	//�͂��߂͍s������̏��
	mChild = new FirstAnimation(actors);
	mChild->mBGM = LoadSoundMem("Data/Sound/Battle.mp3");
	PlaySoundMem(mChild->mBGM, DX_PLAYTYPE_LOOP);

}

Child* Main::update(GameMain* _parent)
{

	Child* next = this;

	mTime++;

	//�w�i�̏���
	stage->update();

	//���b�Z�[�W�̏���
	sController->update();

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
	//drawStatus(440, 330 - enemies.size() * 40, enemies);//330��(ry
	sController->draw();
	aController->draw();
	for (auto e : enemies)
	{
		e->draw(enemies, players);
	}

	mChild->draw(aController);
}




//========================================================================
// ����private�֐�
//========================================================================
void Main::addActor(int _eneLevel)
{
	//Actor�z��̍쐬

	//player��enemy�ʂ��Ŏg��ID
	int battleID{ 0 };

	//�t�@�C���ǂݍ���
	std::ifstream player_in("Data/Text/PlayerData.txt");

	//�t�@�C�����Ȃ�������
	if (!player_in)
	{
		using std::endl;
		std::ofstream out("Data/Text/PlayerData.txt");
		out << "0 �䂤���� 0" << endl;
		out << "1 �܂ق����� 0" << endl;
		out << "2 �����Ƃ��� 0" << endl;
		out << "3 ���񂶂� 0" << endl;
		out.close();
		player_in.open("Data/Text/PlayerData.txt");
	}

	int p_lv{ 0 };//�v���C���|�̃��x��

	//��l���ǂݍ����vector�ɒǉ�
	while (player_in)
	{
		int _ID{ -10 };
		string name{ "dummy" };
		int exp{ 0 };

		player_in >> _ID >> name >> exp;

		//�ǂݍ��݂����Ă�����break
		if (player_in.eof())break;

		//ID����v����L������T��
		auto player = std::find_if(toCharacter.begin(), toCharacter.end(),
			[_ID](auto &spec) { return (spec.ID == _ID); });

		if (player == toCharacter.end())
		{
			//�Ώۂ̃L�����N�^�[�����Ȃ�������I��
			assert(!"�t�@�C�����s���ł�");
			exit(0);
		}

		//100�͎��̃��x���܂ł̕K�v�o���l
		p_lv = 1 + exp / CharacterData::nextExp;

		int h{ -10 }, a{ -10 }, b{ -10 }, c{ -10 }, d{ -10 }, s{ -10 };

		//�\�͒l���v�Z
		h = calcHP(player->s.h, p_lv);
		a = calcStatus(player->s.a, p_lv);
		b = calcStatus(player->s.b, p_lv);
		c = calcStatus(player->s.c, p_lv);
		d = calcStatus(player->s.d, p_lv);
		s = calcStatus(player->s.s, p_lv);

		//�񕜗ʂ��v�Z
		int r = h - abs(a - c);
		r = max(r / 3, min(a, c));

		Actor::Status status{ battleID, _ID, name, false, p_lv, h, a, b, c, d, r, s };
		actors.push_back(new Player(status, exp));

		battleID++;
	}

	assert(actors.size() != 0 && "�t�@�C�����s���ł�");
	player_in.close();



	//��������G

	//�G��1~4��
	short ene_num{ 1 };

	//�v���C���[�̃��x����������x����������G�������̏o��
	if (p_lv > _eneLevel * 5 - 2)ene_num += GetRand(3);


	for (int i = 0; i < ene_num; i++)
	{
		int tmp_ID = GetRand(4);
		EnemySpec::Status ene = (toEneStatus[_eneLevel - 1])[tmp_ID];

		//�G�̃��x���� _eneLevel * 5 + 0~3
		int ene_lv = (_eneLevel - 1) * 5 + GetRand(3);
		int h{ -10 }, a{ -10 }, b{ -10 }, c{ -10 }, d{ -10 }, s{ -10 };

		//�\�͒l���v�Z
		h = calcHP(ene.h, ene_lv);
		a = calcStatus(ene.a, ene_lv);
		b = calcStatus(ene.b, ene_lv);
		c = calcStatus(ene.c, ene_lv);
		d = calcStatus(ene.d, ene_lv);
		s = calcStatus(ene.s, ene_lv);

		//�񕜗ʂ��v�Z
		int r = h - abs(a - c);
		r = max(r / 3, min(a, c));
		
		Actor::Status e{ battleID++, 0, ene.name, true, ene_lv, h, a, b, c, d, r, s,  };

		int exp = min(300, max(10, 20 * (ene_lv - p_lv + 5)) );
		Enemy* tmpEnemy = new Enemy(e, exp);
		tmpEnemy->setName(ene.name);
		tmpEnemy->setData(ene.filename, 640 / (ene_num + 1) * (i + 1), 100);

		actors.push_back(tmpEnemy);
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

	//�Ă��Ƃ���260
	int right = _x + 260;

	//�g��`��
	DrawBox(_x, _y, right, bottom, MyData::GLAY, true);

	//���x���Ɩ��O�Ƒ̗͂�`��
	short i = 0;
	for (auto &actor : _actor)
	{
		//5�Ƃ�7�Ƃ��͗v�E������
		DrawFormatString(_x + 10, _y + 3 + 40 * i, MyData::BLACK, "lv.%d %s %d / %d", actor->status.level, actor->status.name.c_str(), actor->getHP(), actor->status.maxHP);
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
		
		if (mFinTime == 105)
		{
			int exp{ 0 };
			for (const auto& e : _actors)
			{
				if (e->status.isEnemy)exp += e->getExp();
			}
			next = new Result(exp);
		}
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
	ResultPlayers.clear();
	ResultPlayers.shrink_to_fit();
}

void Result::initialize(vector<Actor*> _actors)
{
	mTime = 0;

	//ResultStatus��������
	for (auto& act : _actors)
	{
		if(!act->status.isEnemy)ResultPlayers.push_back(new ResultStatus(act, mGetExp));
	}
	
	//mImg = LoadGraph("Data/Image/play_up.png");
	mBackImg = LoadGraph("Data/Image/BattleBackTmp.png");

	initialized = true;
	DeleteSoundMem(mBGM);
	PlaySoundFile("Data/Sound/win.mp3", DX_PLAYTYPE_BACK);
}

BattleChild* Result::update(ActionController* _aController, StringController* _sController, vector<Actor*> _actors)
{
	if (!initialized)initialize(_actors);

	BattleChild* next = this;

	mTime++;

	for (auto& player : ResultPlayers)
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
	
	if (ResultPlayers.size() >= 1)ResultPlayers[0]->draw(0, 0);
	if (ResultPlayers.size() >= 2)ResultPlayers[1]->draw(320, 0);
	if (ResultPlayers.size() >= 3)ResultPlayers[2]->draw(0, 240);
	if (ResultPlayers.size() >= 4)ResultPlayers[3]->draw(320, 240);
}

//���̃V�[�P���X�ɍs����
bool Result::goField() const
{
	bool goNext = false;

	for (auto& player : ResultPlayers)
	{
		goNext |= player->goNext();
	}
	
	return goNext;
}

void Result::saveData()
{
	std::ofstream fout("Data/Text/PlayerData.txt");
	for (auto& player : ResultPlayers)
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
	mImg = LoadGraph(getFileName(toCharacter[_actor->status.charaID].fileName).c_str());

	initialize(_actor, _mGetExp);
}

void Result::ResultStatus::initialize(Actor* _actor, int _mGetExp)
{
	charaID = _actor->status.charaID;
	name = _actor->status.name;

	mTime = 0;

	mLevelUp = false;
	mLevelTime = 60;

	//���̌o���l�o�[�̈ʒu
	mNowExp = _actor->getExp() % CharacterData::nextExp;

	//�ڕW�̌o���l�o�[�̈ʒu
	mAfterExp = mNowExp + _mGetExp;

	//�o���l�̑����v
	mAllExp = _actor->getExp() + _mGetExp;

	name = _actor->status.name;

}

void Result::ResultStatus::update()
{
	mTime++;

	//mAfterExp�܂Ōo���l�𑝂₷
	mNowExp = min(mNowExp + 1, mAfterExp);

	//�o���l�������ς��ɂȂ����烌�x���A�b�v
	if (mNowExp % CharacterData::nextExp == (CharacterData::nextExp - 1) &&
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
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 230);
	DrawGraph(_x + 90, _y, mImg, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 200);

	//�o���l�o�[�̏����ꏊ���v�Z
	int exp = mNowExp % CharacterData::nextExp;
	int draw_x = 186 * (exp + 1) / CharacterData::nextExp;

	//�e�L�����̃��x���Ɩ��O��\��
	string expInfo = "Lv." + std::to_string(1 + (mAllExp -mAfterExp + mNowExp) / 100) + " " + name;
	DrawString(_x + 10, _y + 170, expInfo.c_str(), MyData::WHITE);

	//�o���l�o�[��`��
	DrawBox(_x + 10, _y + 190, _x + 200, _y + 230, MyData::WHITE, false);
	DrawBox(_x + 12, _y + 192, _x + 12 + draw_x, _y + 228, MyData::WHITE, true);

	//���x���A�b�v!
	if(mLevelUp)DrawFormatString(_x + 20, _y + 150, MyData::WHITE, "Level Up!");
}

string Result::ResultStatus::getSaveString()
{
	return std::to_string(charaID) + " " + name + " " + std::to_string(mAllExp);
}

bool Result::ResultStatus::goNext() const
{
	//���x���A�b�v����2�b���Z�L�[�܂���5�b���return
	return (mTime > 120 && Input_Z()) || mTime > 300;
}

//toCharacter.fileName����摜�̖��O�𐶐�
const string Result::ResultStatus::getFileName(char* _fileName) const
{
	string fileName = "Data/Image/up_";
	fileName += _fileName;
	fileName += ".png";

	return fileName;
}



}
}
}
}