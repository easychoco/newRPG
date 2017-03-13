#include "Converse.h"
#include "..\StateParent.h"

#include "..\..\Data.h"
#include "..\..\KeyInput.h"


namespace StateNS {
namespace GameNS {


Converse::Converse()
{

}

Converse::~Converse()
{

}

void Converse::initialize()
{

}

Child* Converse::update(StateNS::Parent* _parent)
{
	Child* next = this;

	if (Input_C())
	{
		_parent->moveTo(_parent->NextSequence::SEQ_TITLE);
	}

	return next;
}

void Converse::draw() const
{
	DrawFormatString(0, 0, MyData::WHITE, "Converse");
}






}
}

