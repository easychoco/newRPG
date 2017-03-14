#include "FieldStage.h"

#include "..\..\..\..\Data.h"
#include "..\..\..\..\KeyInput.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace FieldNS{


Stage::Stage()
{
	initialize();
}

Stage::~Stage()
{

}

void Stage::initialize()
{
	mBackImg = LoadGraph("Data/FieldBack.png");
}

void Stage::update()
{

}

void Stage::draw() const
{
	DrawFormatString(100, 0, MyData::WHITE, "Stage");
	DrawGraph(0, 0, mBackImg, true);
}




}
}
}
}
