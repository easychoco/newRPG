#include "Title.h"
#include "StateParent.h"
#include "..\Data.h"
#include "..\KeyInput.h"


namespace StateNS{



Title::Title()
{
	initialize();
}

Title::~Title()
{

}

void Title::initialize()
{

}

Child* Title::update(const GrandParent* parent)
{
	Child* next = this;
	
	if (Input_Z())
	{
		next = new Parent();
	}

	return next;
}

void Title::draw() const
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Title");
}




}