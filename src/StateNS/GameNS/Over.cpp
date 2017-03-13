#include "Over.h"
#include "..\StateParent.h"

#include "..\..\Data.h"
#include "..\..\KeyInput.h"


namespace StateNS {
namespace GameNS {


Over::Over()
{

}

Over::~Over()
{

}

void Over::initialize()
{

}

Child* Over::update(StateNS::Parent* _parent)
{
	Child* next = this;

	if (Input_C())
	{
		_parent->moveTo(_parent->NextSequence::SEQ_TITLE);
	}

	return next;
}

void Over::draw() const
{
	DrawFormatString(0, 0, MyData::WHITE, "Over");
}






}
}

