#include "MiddleMain.h"
#include "BattleNS\BattleMain.h"
#include "FieldNS\FieldMain.h"

#include "BattleNS\BattleStringController.h"
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
		switch (nextScene)
		{
		case GameScene::SCENE_BATTLE: next = new BattleNS::Main(); break;
		case GameScene::SCENE_FIELD: next = new FieldNS::Main(); break;
		default: assert(!"�s���ȏ�ԑJ�� MiddleMain::update()");
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
	//�G���J�E���g�̃A�j���[�V����?
	DrawFormatString(0, 60, MyData::WHITE, "ToBattle");
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
	sController = new BattleNS::StringController();
	sController->addMessage("�Ă�");
	sController->addMessage("�Ă��Ă�");
	sController->addMessage("�Ă��Ă��Ă�");
	sController->addMessage("�Ă��Ă��Ă��Ă�");

	mTime = 0;
	arg = _arg;

	//�o���l��0�Ȃ畉��
	win = (arg != 0);

	mImg = LoadGraph("Data/Image/player_up.png");
	mBackImg = LoadGraph("Data/Image/BattleBackTmp.png");
}

void ToField::update()
{
	//���U���g���
	mTime++;
	mGoNext = mTime > 0;
}

void ToField::draw() const
{
	//DrawFormatString(0, 60, MyData::WHITE, "ToField");

	DrawGraph(0, 0, mBackImg, true);
	drawResult(0, 0, mImg);
	drawResult(320, 0, mImg);
	drawResult(0, 240, mImg);
	drawResult(320, 240, mImg);

	//sController->draw();
}

void ToField::drawResult(int _x, int _y, int _img) const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
	DrawBox(_x + 5, _y + 5, _x + 320, _y + 240, MyData::BLUE, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawGraph(_x + 130, _y, _img, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 200);

}




}
}
}