#include "FieldMain.h"
#include "FieldStage.h"
#include "FieldPlayer.h"
#include "FieldSystem.h"
#include "FieldNPC.h"
#include "..\BattleNS\BattleMain.h"
#include "..\MonsterData.h"

#include "..\..\..\..\Data.h"
#include "..\..\..\..\KeyInput.h"

#include <fstream>



namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace FieldNS{


int Main::nextMonster = 0;
bool Main::isTalkWithSymbol = false;

Main::Main(Vector2 _player)
{
	initialize(_player);

	//初手は王様と会話
	NPCs[5]->talk( &Vector2(80000, 888000) );
}

Main::Main(Vector2 _player, bool isEscape)
{
	//逃げていなかったらnextMonster++
	nextMonster += (!isEscape & isTalkWithSymbol);
	isTalkWithSymbol = false;

	initialize(_player);
}

Main::~Main()
{
	SAFE_DELETE(mStage);
	SAFE_DELETE(mPlayer);
	SAFE_DELETE(mGameSystem);
	SAFE_DELETE(mEAnimation);
	for (auto& n : NPCs){ SAFE_DELETE(n); }
	NPCs.clear();
	NPCs.shrink_to_fit();

	DeleteSoundMem(mBGM);
}

void Main::initialize(Vector2 _player)
{
	mStage = new Stage();
	mPlayer = new  Player(_player);
	mGameSystem = new GameSystem();
	mEAnimation = 0;

	switch (nextMonster)
	{
	case 0: NPCs.push_back(new Monster( 320000, 608000, 0, "s0"));
	case 1: NPCs.push_back(new Monster(  64000, 224000, 1, "s1"));
	case 2: NPCs.push_back(new Monster( 800000, 496000, 2, "s2"));
	case 3:	NPCs.push_back(new Monster(1120000, 384000, 3, "s3"));
	case 4:	NPCs.push_back(new Monster(1120000,  32000, 4, "s4"));
	}

	NPCs.push_back(new Ally(  64000, 888000, "Data/Image/Character/king.png", "0"));

	//BGM再生
	mBGM = LoadSoundMem("Data/Sound/field1.mp3");
	PlaySoundMem(mBGM, DX_PLAYTYPE_LOOP);

	monsterID = -10;

	std::ifstream fin("Data/Text/PlayerData.txt");
	std::string gomi;
	for (auto& p : party)
	{
		fin >> p;
		fin >> gomi >> gomi;
	}
}

Child* Main::update(GameMain* _parent)
{
	Child* next = this;

	//update
	mStage->update();
	for (auto &n : NPCs)
	{
		n->update(_parent);
	}
	mGameSystem->update();

	//エンカウントしていなかったら移動可能
	if(!mEAnimation)mPlayer->update(this);

	//敵にエンカウントしたら
	if (mPlayer->isEncount() && mStage->getEnemyLevel(mPlayer->getVector2()) > 0)
	{
		mEAnimation = new EncountAnimation(true);
		//エンカウントのフラグを折るために一度だけupdate()
		mPlayer->update(this);
	}

	//mEAnimationにインスタンスがあるなら
	if (mEAnimation)
	{
		//条件が満たされたらバトルへ
		if (mEAnimation->update())
		{
			next = new BattleNS::Main(*mPlayer->getVector2(), party, mStage->getEnemyLevel(mPlayer->getVector2()), monsterID);
			if (!NPCs[0]->isAlive())isTalkWithSymbol = true;
		}

		//キャンセルでインスタンス破壊
		if (mEAnimation->cancelEncount())SAFE_DELETE(mEAnimation);
	}

	//ポーズ画面へ
	if (Input_S())
	{
		_parent->toPause();
	}

	//クリア画面へ
	if (nextMonster >= toMonster.size())
	{
		_parent->moveToClear();
	}

	return next;
}

void Main::draw() const
{
	mStage->draw(mPlayer->getVector2());
	for (auto &n : NPCs)n->draw(mPlayer->getVector2());
	mPlayer->draw();
	mGameSystem->draw();

	//インスタンスがあればdraw
	if (mEAnimation)mEAnimation->draw();
}

bool Main::canPass(int px, int py) const
{
	//for Debug
	//bool ret = true;
	//for (auto n : NPCs)ret &= n->canPass(px, py);
	//return (mStage->canPass(px, py) && ret) || Input_X();

	return mStage->canPass(px, py) && NPCs[0]->canPass(px, py);
}

void Main::loadParty()
{
	std::ifstream fin("Data/Text/PlayerData.txt");
	std::string gomi;
	for (auto& p : party)
	{
		fin >> p;
		fin >> gomi >> gomi;
	}
	mPlayer->loadParty();
}

const array<int, 4> Main::getParty() const
{
	return party;
}

void Main::talkWithNPC(Vector2* _player)
{
	for (auto &n : NPCs)n->talk(_player);
}

void Main::forceEncount(int _monsterID)
{
	monsterID = _monsterID;

	mEAnimation = new EncountAnimation(false);
	//エンカウントのフラグを折るために一度だけupdate()
	mPlayer->update(this);
}

//====================================
//EncountAnimationクラス
//====================================
EncountAnimation::EncountAnimation(bool _cancelable)
{
	cancelable = _cancelable;
	initialize();
}

EncountAnimation::~EncountAnimation()
{
	SAFE_DELETE(mChild);
	StopSoundFile();
}

void EncountAnimation::initialize()
{
	mTime = 0;

	//エンカウント音
	PlaySoundFile("Data/Sound/encount.mp3", DX_PLAYTYPE_BACK);

	//どのアニメーションにするかを乱数で決定
	auto seed = GetRand(3);

	switch (seed)
	{
	case 0:mChild = new Anime1(); break;
	case 1:mChild = new Anime2(); break;
	case 2:mChild = new Anime3(); break;
	case 3:mChild = new Anime4(); break;
	default:assert(!"不正なAnime");
	}

}

//trueが返るとBattleへ
bool EncountAnimation::update()
{
	mTime++;
	return mTime > 60;
}

void EncountAnimation::draw() const
{
	//Strategy
	mChild->draw(mTime);
}

//trueが返るとフィールドへ戻る
bool EncountAnimation::cancelEncount() const
{
	return cancelable & Input_X();
}


//====================================
//EncountAnimationクラスの内部クラス
//====================================
void EncountAnimation::Anime1::draw(int _time) const
{
	DrawBox(0, 0, 640, _time * 8, MyData::BLACK, true);
}

void EncountAnimation::Anime2::draw(int _time) const
{
	DrawBox(0, 480 - _time * 8, 640, 480, MyData::BLACK, true);
}

void EncountAnimation::Anime3::draw(int _time) const
{
	int draw_x1{ 320 - _time * 16 / 3 };//16 / 3 = 320 / 60
	int draw_y1{ 240 - _time * 4 };
	int draw_x2{ 320 + _time * 16 / 3 };//16 / 3 = 320 / 60
	int draw_y2{ 240 + _time * 4 };
	DrawBox(draw_x1, draw_y1, draw_x2, draw_y2, MyData::BLACK, true);
}

void EncountAnimation::Anime4::draw(int _time) const
{
	//最初は255, _timeが60で0
	int val{ 255 - 255 * _time / 60 };
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - val);
	DrawBox(0, 0, 640, 480, GetColor(val, val, val), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}



}
}
}
}