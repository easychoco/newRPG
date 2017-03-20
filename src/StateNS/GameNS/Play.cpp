#include "Play.h"
#include "Clear.h"

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

}

void Play::initialize()
{
	gameMain = new GameMainNS::GameMain();
}

Child* Play::update(Parent* parent)
{
	Child* next = this;
	gameMain->update(this);

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




}
}