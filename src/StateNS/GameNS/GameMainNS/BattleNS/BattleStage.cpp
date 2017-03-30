#include "BattleStage.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace BattleNS {


Stage::Stage()
{
	initialize();
}

Stage::~Stage()
{

}

void Stage::initialize()
{
	mBackImg = LoadGraph("Data/Image/BattleBackTmp.png");
	assert(mBackImg != -1 && "バトル背景画像読み込みエラー");
}

void Stage::update()
{

}

void Stage::draw() const
{
	DrawGraph(0, 0, mBackImg, true);
}


//========================================================================
// 内部private関数
//========================================================================





}
}
}
}
