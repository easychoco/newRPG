#include "FieldMain.h"
#include "FieldStage.h"
#include "FieldPlayer.h"
#include "FieldSystem.h"

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

void Main::update(GameParent* _parent)
{
	//Aキーでバトルへ
	if (Input_A())mNext = GameScene::SCENE_BATTLE;

	//update
	mStage->update();
	mPlayer->update();
	mGameSystem->update();
}

void Main::draw() const
{
	DrawFormatString(0, 40, MyData::WHITE, "FieldMain");
	mStage->draw();
	mPlayer->draw();
	mGameSystem->draw();

}

GameScene Main::changeScene()
{
	return mNext;
}






}
}
}
}