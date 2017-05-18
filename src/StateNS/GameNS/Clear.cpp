#include "Clear.h"
#include "..\StateParent.h"

#include "..\..\Data.h"
#include "..\..\KeyInput.h"

namespace StateNS {
namespace GameNS {

Clear::Clear()
{
	initialize();
}

Clear::~Clear()
{

}

void Clear::initialize()
{
	mTime = 0;
	mBackImg = LoadGraph("Data/Image/ResultBack.png");
	mClearImg = LoadGraph("Data/Image/clear.png");
	mThankImg = LoadGraph("Data/Image/thankyou.png");
	mToTitleImg = LoadGraph("Data/Image/totitle.png");
	toTitle = false;
}

Child* Clear::update(StateNS::Parent* _parent)
{
	Child* next = this;

	mTime+=2;

	if (Input_Z())
	{
		mTime = 600;
	}

	toTitle = mTime > 600;

	if (toTitle && Input_X())
	{
		_parent->moveTo(_parent->NextSequence::SEQ_TITLE);
	}

	return next;
}

void Clear::draw() const
{
	DrawGraph(0, 0, mBackImg, true);
	DrawGraph(157, max(480 - mTime, 50), mClearImg, true);
	DrawGraph(148, max(700 - mTime, 150), mThankImg, true);

	if (toTitle)
	{
		DrawGraph(270, 425, mToTitleImg, true);
	}
}






}
}

