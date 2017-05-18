#include "Title.h"
#include "StateParent.h"
#include "..\Data.h"
#include "..\KeyInput.h"


namespace StateNS{


Title::Title()
{
	InitGraph();
	initialize();
}

Title::~Title()
{

}

void Title::initialize()
{
	mTime = 0;
	mBackImg = LoadGraph("Data/Image/title.png");
	mLogoImg = LoadGraph("Data/Image/logo.png");
	mPushZImg = LoadGraph("Data/Image/pushZ.png");

	assert(mBackImg != -1 && mLogoImg != -1 && mPushZImg != -1 &&"title‰æ‘œ“Ç‚Ýž‚ÝƒGƒ‰[!");
}

Child* Title::update(const GrandParent* parent)
{
	Child* next = this;

	mTime++;
	
	if (Input_Z())
	{
		next = new Parent();
	}

	return next;
}

void Title::draw() const
{
	DrawGraph(0, 0, mBackImg, true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, max(255 - 2 * mTime, 0));
	DrawBox(0, 0, 640, 480, MyData::WHITE, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (mTime > 128)
	{
		DrawGraph(30, 100, mLogoImg, true);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, abs(128 - 2 * mTime % 256) + 128);
		DrawGraph(20, 330, mPushZImg, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}




}