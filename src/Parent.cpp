#include "Parent.h"
#include "StateNS\Title.h"
#include "StateNS\StateParent.h"

#include "Data.h"


Parent::Parent()
{
	mChild = 0;
	initialize();
}

Parent::~Parent()
{
	SAFE_DELETE(mChild);
}

void Parent::initialize()
{
	mChild = new StateNS::Title();
}

void Parent::update()
{
	Child* next = mChild->update(this);

	//‘JˆÚ
	if (mChild != next)
	{
		SAFE_DELETE(mChild);
		mChild = next;
	}

	next = 0;
}

void Parent::draw() const
{
	mChild->draw();
}

