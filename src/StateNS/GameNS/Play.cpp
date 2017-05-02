#include "Play.h"
#include "Load.h"
#include "Clear.h"
#include "Over.h"
#include "..\StateParent.h"

#include "..\..\Data.h"
#include "..\..\KeyInput.h"



namespace StateNS {
namespace GameNS {

Play::Play()
{
	initialize();
}

Play::~Play()
{
	SAFE_DELETE(gameMain);
}

void Play::initialize()
{
	mNextSeq = SEQ_NONE;
	gameMain = new GameMainNS::GameMain();
}


Child* Play::update(Parent* _parent)
{
	Child* next = this;
	gameMain->update(this);

	if (mNextSeq != SEQ_NONE)
	{
		if (mNextSeq == SEQ_TITLE)_parent->moveTo(_parent->SEQ_TITLE);
		else next = changeSequence();
	}

	if (Input_C())
	{
		SAFE_DELETE(gameMain);
		next = new Clear();
	}


	return next;
}

void Play::draw() const
{
	DrawFormatString(0, 0, MyData::WHITE, "Play");
	gameMain->draw();
}

void Play::moveTo(NextSequence _next)
{
	mNextSeq = _next;
}

Child* Play::changeSequence()
{
	Child* next = 0;
	SAFE_DELETE(gameMain);
	switch (mNextSeq)
	{
	case SEQ_LOAD: next = new Load(); break;
	case SEQ_CLEAR: next = new Clear(); break;
	case SEQ_OVER: next = new Over(); break;
	}
	return next;
}



}
}