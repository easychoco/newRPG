#include "Converse.h"

#include "..\..\..\Data.h"
#include "..\..\..\KeyInput.h"


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

bool Converse::update()
{
	return Input_A();
}

void Converse::draw() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
	DrawBox(0, 0, 640, 480, MyData::WHITE, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawFormatString(0, 0, MyData::BLACK, "Converse");
}






}
}

