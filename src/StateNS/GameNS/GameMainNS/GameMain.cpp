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


GameMain::GameMain()
{
	initialize();
}

GameMain::~GameMain()
{
	SAFE_DELETE(mChild);
}

void GameMain::initialize()
{
	mChild = new FieldNS::Main( Vector2(0, 0) );
}

void GameMain::update(GameParent* _parent)
{
	Child* next = mChild->update(this);

	//シーケンス遷移
	if (next != mChild)
	{
		SAFE_DELETE(mChild);
		mChild = next;
	}
}

void GameMain::draw() const
{
	mChild->draw();
}


//==============================================
//内部プライベート関数
//==============================================

//そんなものはない



}
}
}