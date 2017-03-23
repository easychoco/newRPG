#include "MiddleMain.h"
#include "BattleNS\BattleMain.h"
#include "FieldNS\FieldMain.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{




MiddleMain::MiddleMain(GameScene _nextScene) :
nextScene(_nextScene){
	initialize();
}

MiddleMain::~MiddleMain()
{
	SAFE_DELETE(mChild);
}

void MiddleMain::initialize()
{
	mTime = 0;
	switch (nextScene)
	{
	case GameScene::SCENE_BATTLE: mChild = new ToBattle(); break;
	case GameScene::SCENE_FIELD: mChild = new ToField(); break;
	default: assert(!"�s���ȏ�ԑJ��");
	}
}

Child* MiddleMain::update(GameParent* _parent)
{
	Child* next = this;

	//���̉�ʂ�update
	mChild->update();

	//���̏�Ԃ֑J��
	if (mChild->goNext())
	{
		switch (nextScene)
		{
		case GameScene::SCENE_BATTLE: next = new BattleNS::Main(); break;
		case GameScene::SCENE_FIELD: next = new FieldNS::Main(); break;
		default: assert(!"�s���ȏ�ԑJ��");
		}

	}

	return next;
}

void MiddleMain::draw() const
{
	DrawFormatString(0, 40, MyData::WHITE, "MiddleMain");
	mChild->draw();
}

//======================================
// State�ł����N���X����
//======================================

//======================================
// ToBattle�N���X
//======================================
ToBattle::ToBattle()
{
	initialize();
}

ToBattle::~ToBattle()
{

}

void ToBattle::initialize()
{
	mTime = 0;
}

void ToBattle::update()
{
	//�G���J�E���g�����߂�
	mTime++;
	mGoNext = mTime > 60;
}

void ToBattle::draw() const
{
	DrawFormatString(0, 60, MyData::WHITE, "ToBattle");
}


//======================================
// ToField�N���X
//======================================
ToField::ToField()
{
	initialize();
}

ToField::~ToField()
{

}

void ToField::initialize()
{
	mTime = 0;
}

void ToField::update()
{
	//�o���l�̌v�Z
	//�����郊�U���g���
	mTime++;
	mGoNext = mTime > 60;
}

void ToField::draw() const
{
	DrawFormatString(0, 60, MyData::WHITE, "ToField");
}






}
}
}