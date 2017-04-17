#include "FieldMain.h"
#include "FieldStage.h"
#include "FieldPlayer.h"
#include "FieldSystem.h"
//#include "..\MiddleMain.h"
#include "..\BattleNS\BattleMain.h"

#include "..\..\..\..\Data.h"
#include "..\..\..\..\KeyInput.h"



namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace FieldNS{

Main::Main(Vector2 _player)
{
	initialize(_player);
}

Main::~Main()
{

}

void Main::initialize(Vector2 _player)
{
	mStage = new Stage();
	mPlayer = new  Player(_player);
	mGameSystem = new GameSystem();
	mEAnimation = 0;
}

Child* Main::update(const GameMain* _parent)
{
	Child* next = this;

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
		if (mEAnimation->update())next = new BattleNS::Main(*mPlayer->getVector2());


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
	SAFE_DELETE(mChild);
}

void EncountAnimation::initialize()
{
	mTime = 0;

	//�ǂ̃A�j���[�V�����ɂ��邩�𗐐��Ō���
	auto seed = GetRand(3);

	switch (seed)
	{
	case 0:mChild = new Anime1(); break;
	case 1:mChild = new Anime2(); break;
	case 2:mChild = new Anime3(); break;
	case 3:mChild = new Anime4(); break;
	default:assert(!"�s����Anime");
	}

}

//true���Ԃ��Battle��
bool EncountAnimation::update()
{
	mTime++;
	return mTime > 60;
}

void EncountAnimation::draw() const
{
	//Strategy
	mChild->draw(mTime);
}

//true���Ԃ�ƃt�B�[���h�֖߂�
bool EncountAnimation::cancelEncount() const
{
	return Input_X();
}


//====================================
//EncountAnimation�N���X�̓����N���X
//====================================
void EncountAnimation::Anime1::draw(int _time) const
{
	DrawBox(0, 0, 640, _time * 8, MyData::BLACK, true);
}

void EncountAnimation::Anime2::draw(int _time) const
{
	DrawBox(0, 480 - _time * 8, 640, 480, MyData::BLACK, true);
}

void EncountAnimation::Anime3::draw(int _time) const
{
	int draw_x1{ 320 - _time * 16 / 3 };//16 / 3 = 320 / 60
	int draw_y1{ 240 - _time * 4 };
	int draw_x2{ 320 + _time * 16 / 3 };//16 / 3 = 320 / 60
	int draw_y2{ 240 + _time * 4 };
	DrawBox(draw_x1, draw_y1, draw_x2, draw_y2, MyData::BLACK, true);
}

void EncountAnimation::Anime4::draw(int _time) const
{
	//�ŏ���255, _time��60��0
	int val{ 255 - 255 * _time / 60 };
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - val);
	DrawBox(0, 0, 640, 480, GetColor(val, val, val), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}



}
}
}
}