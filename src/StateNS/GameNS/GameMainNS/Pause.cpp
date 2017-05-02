#include "Pause.h"

#include "..\..\..\Data.h"
#include "..\..\..\KeyInput.h"


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

bool Pause::update()
{
	return Input_A();
}

void Pause::draw() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
	DrawBox(0, 0, 640, 480, MyData::WHITE, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawFormatString(0, 0, MyData::BLACK, "Pause");
}






}
}

