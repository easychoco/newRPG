#include "BattleMain.h"

#include "..\..\..\..\Data.h"
#include "..\..\..\..\KeyInput.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace BattleNS{


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
	//Sキーでフィールドへ
	if (Input_S())
		mNext = GameScene::SCENE_FIELD;
}

void Main::draw() const
{
	DrawFormatString(0, 40, MyData::WHITE, "BattleMain");
}

GameScene Main::changeScene()
{
	return mNext;
}






}
}
}
}