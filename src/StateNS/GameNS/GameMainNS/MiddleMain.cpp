#include "MiddleMain.h"
#include "BattleNS\BattleMain.h"
#include "FieldNS\FieldMain.h"

#include "BattleNS\BattleStringController.h"
#include "..\..\..\KeyInput.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{




MiddleMain::MiddleMain(GameScene _nextScene, int _arg) :
nextScene(_nextScene){
	initialize(_arg);
}

MiddleMain::~MiddleMain()
{
	SAFE_DELETE(mChild);
}

void MiddleMain::initialize(int _arg)
{
	arg = _arg;
	switch (nextScene)
	{
	case GameScene::SCENE_BATTLE: mChild = new ToBattle(arg); break;
	case GameScene::SCENE_FIELD: mChild = new ToField(arg); break;
	default: assert(!"不正な状態遷移 MiddleMain::initialize()");
	}
}

Child* MiddleMain::update(const GameMain* _parent)
{
	Child* next = this;

	//この画面のupdate
	mChild->update();

	//次の状態へ遷移
	if (mChild->goNext())
	{
		switch (nextScene)
		{
		case GameScene::SCENE_BATTLE: next = new BattleNS::Main(); break;
		case GameScene::SCENE_FIELD: next = new FieldNS::Main(); break;
		default: assert(!"不正な状態遷移 MiddleMain::update()");
		}
	}

	return next;
}

void MiddleMain::draw() const
{
	DrawFormatString(0, 40, MyData::WHITE, "MiddleMain");
	mChild->draw();
}

//======================================
// Stateでつかうクラスたち
//======================================

//======================================
// ToBattleクラス
//======================================
ToBattle::ToBattle(int _arg)
{
	initialize(_arg);
}

ToBattle::~ToBattle()
{

}

void ToBattle::initialize(int _arg)
{
	mTime = 0;
	arg = _arg;
}

void ToBattle::update()
{
	mTime++;
	mGoNext = mTime > 0;
}

void ToBattle::draw() const
{
	//エンカウントのアニメーション?
	DrawFormatString(0, 60, MyData::WHITE, "ToBattle");
}


//======================================
// ToFieldクラス
//======================================
ToField::ToField(int _arg)
{
	initialize(_arg);
}

ToField::~ToField()
{

}

void ToField::initialize(int _arg)
{
	sController = new BattleNS::StringController();
	sController->addMessage("てす");
	sController->addMessage("てすてす");
	sController->addMessage("てすてすてす");
	sController->addMessage("てすてすてすてす");

	mTime = 0;
	arg = _arg;

	//経験値が0なら負け
	win = (arg != 0);

	mImg = LoadGraph("Data/Image/player_up.png");
	mBackImg = LoadGraph("Data/Image/BattleBackTmp.png");
}

void ToField::update()
{
	//リザルト画面
	mTime++;
	mGoNext = mTime > 0;
}

void ToField::draw() const
{
	//DrawFormatString(0, 60, MyData::WHITE, "ToField");

	DrawGraph(0, 0, mBackImg, true);
	drawResult(0, 0, mImg);
	drawResult(320, 0, mImg);
	drawResult(0, 240, mImg);
	drawResult(320, 240, mImg);

	//sController->draw();
}

void ToField::drawResult(int _x, int _y, int _img) const
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