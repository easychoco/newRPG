#include "FieldMain.h"

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
}

void Main::update(GameParent* _parent)
{
	//Aキーでバトルへ
	if (Input_A())mNext = GameScene::SCENE_BATTLE;
}

void Main::draw() const
{
	DrawFormatString(0, 40, MyData::WHITE, "FieldMain");
}

GameScene Main::changeScene()
{
	return mNext;
}






}
}
}
}