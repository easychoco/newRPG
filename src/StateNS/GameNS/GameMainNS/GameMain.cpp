#include "GameMain.h"
#include "..\Play.h"
#include "FieldNS\FieldMain.h"
#include "BattleNS\BattleMain.h"
#include "GameMainChild.h"
#include "MiddleMain.h"

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

	Child* next = mChild->update(_parent);

	//ゲームシーン変更
	//Child* next = mChild->changeScene();

	if (next != mChild)
	{
		SAFE_DELETE(mChild);
		mChild = next;
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