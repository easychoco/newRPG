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
}

Child* Main::update(const GameMain* _parent)
{
	Child* next = this;

	//Aキーでバトルへ
	if (Input_A())next = new MiddleMain(GameScene::SCENE_BATTLE, 1);

	//update
	mStage->update();
	mPlayer->update(this);
	mGameSystem->update();

	return next;
}

void Main::draw() const
{
	DrawFormatString(0, 40, MyData::WHITE, "FieldMain");
	mStage->draw(mPlayer->getVector2());
	mPlayer->draw();
	mGameSystem->draw();
}

bool Main::canPass(int px, int py) const
{
	return mStage->canPass(px, py);
}





}
}
}
}