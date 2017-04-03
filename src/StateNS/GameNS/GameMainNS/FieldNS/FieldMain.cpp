#include "FieldMain.h"
#include "FieldStage.h"
#include "FieldPlayer.h"
#include "FieldSystem.h"
#include "..\MiddleMain.h"

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

	mStage = new Stage();
	mPlayer = new  Player();
	mGameSystem = new GameSystem();
	mEAnimation = 0;
}

Child* Main::update(const GameMain* _parent)
{
	Child* next = this;

	//A�L�[�Ńo�g����
	if (Input_A())next = new MiddleMain(GameScene::SCENE_BATTLE, 1);

	//update
	mStage->update();
	mGameSystem->update();

	//�G���J�E���g���Ă��Ȃ�������ړ��\
	if(!mEAnimation)mPlayer->update(this);

	//�G�ɃG���J�E���g������
	if (mPlayer->isEncount() && mStage->getEnemyLevel(mPlayer->getVector2()) > 0)
	{
		mEAnimation = new EncountAnimation();
		//�G���J�E���g�̃t���O��܂邽�߂Ɉ�x����update()
		mPlayer->update(this);
	}

	//mEAnimation�ɃC���X�^���X������Ȃ�
	if (mEAnimation)
	{
		//�������������ꂽ��o�g����
		if(mEAnimation->update())next = new MiddleMain(GameScene::SCENE_BATTLE, 1);

		//�L�����Z���ŃC���X�^���X�j��
		if (mEAnimation->cancelEncount())SAFE_DELETE(mEAnimation);
	}

	return next;
}

void Main::draw() const
{
	DrawFormatString(0, 40, MyData::WHITE, "FieldMain");
	mStage->draw(mPlayer->getVector2());
	mPlayer->draw();
	mGameSystem->draw();

	//�C���X�^���X�������draw
	if (mEAnimation)mEAnimation->draw();
}

bool Main::canPass(int px, int py) const
{
	return mStage->canPass(px, py);
}

//====================================
//EncountAnimation�N���X
//====================================
EncountAnimation::EncountAnimation()
{
	initialize();
}

EncountAnimation::~EncountAnimation()
{

}

void EncountAnimation::initialize()
{
	mTime = 0;
}

//true���Ԃ��Battle��
bool EncountAnimation::update()
{
	mTime++;
	return mTime > 60;
}

void EncountAnimation::draw() const
{
	DrawBox(0, 0, 640, mTime * 8, MyData::BLACK, true);
}

//true���Ԃ�ƃt�B�[���h�֖߂�
bool EncountAnimation::cancelEncount() const
{
	return Input_X();
}



}
}
}
}