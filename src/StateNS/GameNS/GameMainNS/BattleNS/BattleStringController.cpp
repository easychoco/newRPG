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

//frameMessage���X�V
void StringController::addMessage(string _message)
{
	//���̂ق����V�������b�Z�[�W
	//���ɐV�������b�Z�[�W��ǉ�
	frameMessage.push_back(_message);

	
	//���b�Z�[�W�������ς��Ȃ�擪�ɂ����ԌÂ����b�Z�[�W���폜
	if(frameMessage.size() > 4)
		frameMessage.erase(frameMessage.begin());
}


//========================================================================
// ����private�֐�
//========================================================================





}
}
}
}
