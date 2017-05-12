#include "GameMain.h"
#include "..\Play.h"
#include "FieldNS\FieldMain.h"
#include "GameMainChild.h"
#include "Converse.h"
#include "Pause.h"

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
	mConverse = 0;
	mPause = 0;
}

void GameMain::update(GameParent* _parent)
{
	//インスタンスのあるものをupdate
	if (mConverse) { if (mConverse->update()) { SAFE_DELETE(mConverse); } }

	else if (mPause) { if (mPause->update()) { SAFE_DELETE(mPause); } }

	else
	{
		Child* next = mChild->update(this);

		//シーケンス遷移
		if (next != mChild)
		{
			SAFE_DELETE(mChild);
			mChild = next;
		}
	}



}

void GameMain::draw() const
{
	mChild->draw();
	if (mConverse)mConverse->draw();
	else if (mPause)mPause->draw();
	
}


//==============================================
//内部プライベート関数
//==============================================
void GameMain::toConverse(char* fileName)
{
	if (!mConverse)mConverse = new Converse(fileName);
}

void GameMain::toPause()
{
	if (!mPause)mPause = new Pause();
}



}
}
}