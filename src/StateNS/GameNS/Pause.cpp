#include "Pause.h"
#include "..\StateParent.h"

#include "..\..\Data.h"
#include "..\..\KeyInput.h"


namespace StateNS {
namespace GameNS {


Pause::Pause()
{

}

Pause::~Pause()
{

}

void Pause::initialize()
{

}

Child* Pause::update(StateNS::Parent* _parent)
{
	Child* next = this;

	if (Input_C())
	{
		_parent->moveTo(_parent->NextSequence::SEQ_TITLE);
	}

	return next;
}

void Pause::draw() const
{
	DrawFormatString(0, 0, MyData::WHITE, "Pause");
}






}
}

