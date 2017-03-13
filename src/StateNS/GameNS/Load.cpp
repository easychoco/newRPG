#include "Load.h"
#include "..\StateParent.h"

#include "..\..\Data.h"
#include "..\..\KeyInput.h"


namespace StateNS {
namespace GameNS {


Load::Load()
{

}

Load::~Load()
{

}

void Load::initialize()
{

}

Child* Load::update(StateNS::Parent* _parent)
{
	Child* next = this;

	if (Input_C())
	{
		_parent->moveTo(_parent->NextSequence::SEQ_TITLE);
	}

	return next;
}

void Load::draw() const
{
	DrawFormatString(0, 0, MyData::WHITE, "Load");
}






}
}

