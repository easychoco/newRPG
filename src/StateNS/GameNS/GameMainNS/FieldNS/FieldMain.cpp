#include "FieldMain.h"
#include "FieldStage.h"
#include "FieldPlayer.h"
#include "FieldSystem.h"
#include "..\MiddleMain.h"

#include "..\..\..\..\Data.h"
#include "..\..\..\..\KeyInput.h"



namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace FieldNS{


Main::Main()
{
	initialize();
}

Main::~Main()
{

}

void Main::initialize()
{
	mNext = GameScene::SCENE_NONE;

	mStage = new Stage();
	mPlayer = new  Player();
	mGameSystem = new GameSystem();
	mEAnimation = 0;
}

Child* Main::update(const GameMain* _parent)
{
	Child* next = this;

	//Aキーでバトルへ
	if (Input_A())next = new MiddleMain(GameScene::SCENE_BATTLE, 1);

	//update
	mStage->update();
	mGameSystem->update();

	//エンカウントしていなかったら移動可能
	if(!mEAnimation)mPlayer->update(this);

	//敵にエンカウントしたら
	if (mPlayer->isEncount() && mStage->getEnemyLevel(mPlayer->getVector2()) > 0)
	{
		mEAnimation = new EncountAnimation();
		//エンカウントのフラグを折るために一度だけupdate()
		mPlayer->update(this);
	}

	//mEAnimationにインスタンスがあるなら
	if (mEAnimation)
	{
		//条件が満たされたらバトルへ
		if(mEAnimation->update())next = new MiddleMain(GameScene::SCENE_BATTLE, 1);

		//キャンセルでインスタンス破壊
		if (mEAnimation->cancelEncount())SAFE_DELETE(mEAnimation);
	}

	return next;
}

void Main::draw() const
{
	DrawFormatString(0, 40, MyData::WHITE, "FieldMain");
	mStage->draw(mPlayer->getVector2());
	mPlayer->draw();
	mGameSystem->draw();

	//インスタンスがあればdraw
	if (mEAnimation)mEAnimation->draw();
}

bool Main::canPass(int px, int py) const
{
	return mStage->canPass(px, py);
}

//====================================
//EncountAnimationクラス
//====================================
EncountAnimation::EncountAnimation()
{
	initialize();
}

EncountAnimation::~EncountAnimation()
{

}

void EncountAnimation::initialize()
{
	mTime = 0;
}

//trueが返るとBattleへ
bool EncountAnimation::update()
{
	mTime++;
	return mTime > 60;
}

void EncountAnimation::draw() const
{
	DrawBox(0, 0, 640, mTime * 8, MyData::BLACK, true);
}

//trueが返るとフィールドへ戻る
bool EncountAnimation::cancelEncount() const
{
	return Input_X();
}



}
}
}
}