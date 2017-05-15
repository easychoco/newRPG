#include "BattleStage.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace BattleNS {


Stage::Stage(int stageNum)
{
	initialize(stageNum);
}

Stage::~Stage()
{
	DeleteGraph(mBackImg);
}

void Stage::initialize(int _stageNum)
{
	string fileName = "Data/Image/BattleBack";
	fileName += std::to_string(_stageNum);
	fileName += ".png";

	mBackImg = LoadGraph(fileName.c_str());
	assert(mBackImg != -1 && "�o�g���w�i�摜�ǂݍ��݃G���[");
}

void Stage::update()
{

}

void Stage::draw() const
{
	DrawGraph(0, 0, mBackImg, true);
}


//========================================================================
// ����private�֐�
//========================================================================





}
}
}
}
