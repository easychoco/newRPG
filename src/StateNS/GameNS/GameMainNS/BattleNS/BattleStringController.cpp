#include "BattleStringController.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace BattleNS {


StringController::StringController()
{
	initialize();
}

StringController::~StringController()
{
	frameMessage.clear();
	frameMessage.shrink_to_fit();
}

void StringController::initialize()
{
	mFrameImg = LoadGraph("Data/BattleFrame.png");
}

void StringController::update()
{

}

void StringController::draw() const
{
	DrawGraph(0, 330, mFrameImg, true);

	//if (frameMessage.size() < 3)return;
	DrawString(50, frameLine[0], frameMessage[3].c_str(), MyData::BLACK);
	DrawString(50, frameLine[1], frameMessage[2].c_str(), MyData::BLACK);
	DrawString(50, frameLine[2], frameMessage[1].c_str(), MyData::BLACK);
	DrawString(50, frameLine[3], frameMessage[0].c_str(), MyData::BLACK);
	
}

//frameMessageを更新
void StringController::addMessage(string _message)
{
	//後ろのほうが新しいメッセージ
	//後ろに新しいメッセージを追加
	frameMessage.push_back(_message);

	
	//メッセージがいっぱいなら先頭にある一番古いメッセージを削除
	if(frameMessage.size() > 4)
		frameMessage.erase(frameMessage.begin());
}


//========================================================================
// 内部private関数
//========================================================================





}
}
}
}
