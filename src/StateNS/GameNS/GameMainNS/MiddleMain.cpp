#include "MiddleMain.h"
#include "BattleNS\BattleMain.h"
#include "FieldNS\FieldMain.h"

#include "..\..\..\KeyInput.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{




MiddleMain::MiddleMain(GameScene _nextScene, int _arg) :
nextScene(_nextScene){
	initialize(_arg);
}

MiddleMain::~MiddleMain()
{
	SAFE_DELETE(mChild);
}

void MiddleMain::initialize(int _arg)
{
	arg = _arg;
	switch (nextScene)
	{
	case GameScene::SCENE_BATTLE: mChild = new ToBattle(arg); break;
	case GameScene::SCENE_FIELD: mChild = new ToField(arg); break;
	default: assert(!"�s���ȏ�ԑJ�� MiddleMain::initialize()");
	}
}

Child* MiddleMain::update(const GameMain* _parent)
{
	Child* next = this;

	//���̉�ʂ�update
	mChild->update();

	//���̏�Ԃ֑J��
	if (mChild->goNext())
	{
		/*
		switch (nextScene)
		{
		case GameScene::SCENE_BATTLE: next = new BattleNS::Main(); break;
		case GameScene::SCENE_FIELD: next = new FieldNS::Main(0, 0); break;
		default: assert(!"�s���ȏ�ԑJ�� MiddleMain::update()");
		}
		*/
	}

	return next;
}

void MiddleMain::draw() const
{
	mChild->draw();
}

//======================================
// State�ł����N���X����
//======================================

//======================================
// ToBattle�N���X
//======================================
ToBattle::ToBattle(int _arg)
{
	initialize(_arg);
}

ToBattle::~ToBattle()
{

}

void ToBattle::initialize(int _arg)
{
	mTime = 0;
	arg = _arg;
}

void ToBattle::update()
{
	mTime++;
	mGoNext = mTime > 0;
}

void ToBattle::draw() const
{

}


//======================================
// ToField�N���X
//======================================
ToField::ToField(int _arg)
{
	initialize(_arg);
}

ToField::~ToField()
{

}

void ToField::initialize(int _arg)
{
	mTime = 0;
	arg = _arg;
}

void ToField::update()
{
	//���U���g���
	mTime++;
	mGoNext = mTime > 0;
}

void ToField::draw() const
{
}

void ToField::drawResult(int _x, int _y, int _img) const
{

}




}
}
}