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
	SAFE_DELETE(mChild);
}

void GameMain::initialize()
{
	mChild = new BattleNS::Main();
}

void GameMain::update(GameParent* _parent)
{
	mChild->update(_parent);

	//�Q�[���V�[���ύX
	GameScene next = mChild->changeScene();

	if (next != GameScene::SCENE_NONE)
	{
		SAFE_DELETE(mChild);
		switch (next)
		{
		case GameScene::SCENE_FIELD: mChild = new FieldNS::Main(); break;
		case GameScene::SCENE_BATTLE: mChild = new BattleNS::Main(); break;
		default: assert(!"�s���ȃV�[���ύX!");
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