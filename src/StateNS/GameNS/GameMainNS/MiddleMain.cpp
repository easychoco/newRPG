#include "MiddleMain.h"
#include "BattleNS\BattleMain.h"
#include "FieldNS\FieldMain.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{




MiddleMain::MiddleMain(GameScene _nextScene) :
nextScene(_nextScene){
	initialize();
}

MiddleMain::~MiddleMain()
{
	SAFE_DELETE(mChild);
}

void MiddleMain::initialize()
{
	mTime = 0;
	switch (nextScene)
	{
	case GameScene::SCENE_BATTLE: mChild = new ToBattle(); break;
	case GameScene::SCENE_FIELD: mChild = new ToField(); break;
	default: assert(!"不正な状態遷移");
	}
}

Child* MiddleMain::update(GameParent* _parent)
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
		default: assert(!"不正な状態遷移");
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
ToBattle::ToBattle()
{
	initialize();
}

ToBattle::~ToBattle()
{

}

void ToBattle::initialize()
{
	mTime = 0;
}

void ToBattle::update()
{
	//エンカウントを決める
	mTime++;
	mGoNext = mTime > 60;
}

void ToBattle::draw() const
{
	DrawFormatString(0, 60, MyData::WHITE, "ToBattle");
}


//======================================
// ToFieldクラス
//======================================
ToField::ToField()
{
	initialize();
}

ToField::~ToField()
{

}

void ToField::initialize()
{
	mTime = 0;
}

void ToField::update()
{
	//経験値の計算
	//いわゆるリザルト画面
	mTime++;
	mGoNext = mTime > 60;
}

void ToField::draw() const
{
	DrawFormatString(0, 60, MyData::WHITE, "ToField");
}






}
}
}