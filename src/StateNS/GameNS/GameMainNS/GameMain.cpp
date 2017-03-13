#include "GameMain.h"
#include "..\Play.h"
#include "FieldNS\FieldMain.h"
#include "BattleNS\BattleMain.h"
#include "GameMainChild.h"

#include "..\..\..\Data.h"
#include "..\..\..\KeyInput.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


GameMain::GameMain(){
	initialize();
}

GameMain::~GameMain()
{

}

void GameMain::initialize()
{
	mChild = new FieldNS::Main();
}

void GameMain::update(GameParent* _parent)
{
	mChild->update(_parent);

	//ゲームシーン変更
	GameScene next = mChild->changeScene();

	if (next != GameScene::SCENE_NONE)
	{
		SAFE_DELETE(mChild);
		switch (next)
		{
		case GameScene::SCENE_FIELD: mChild = new FieldNS::Main(); break;
		case GameScene::SCENE_BATTLE: mChild = new BattleNS::Main(); break;
		default: assert(!"不正なシーン変更!");
		}
	}

}

void GameMain::draw() const
{
	DrawFormatString(0, 20, MyData::WHITE, "GameMain");
	mChild->draw();
}







}
}
}