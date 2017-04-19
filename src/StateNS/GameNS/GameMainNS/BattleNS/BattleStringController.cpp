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
	mFrameImg = LoadGraph("Data/Image/BattleFrame.png");
	mUpperImg = LoadGraph("Data/Image/UpperFrame.png");

	mTime = 0;
	mTimeFromLastAdd = 0;
	message_dy = 0;

	//FrameMessage�̐擪�ƍŌ����ݒ�
	beginMessage = new FrameMessage("");
	endMessage = new FrameMessage("");

	beginMessage->addNext(endMessage);
	
	FrameMessage* tmpMessage = new FrameMessage("");
	endMessage->addNext(tmpMessage);
	endMessage = tmpMessage;
	
	tmpMessage = new FrameMessage("");
	endMessage->addNext(tmpMessage);
	endMessage = tmpMessage;

	tmpMessage = new FrameMessage("");
	endMessage->addNext(tmpMessage);
	endMessage = tmpMessage;
	
	tmpMessage = new FrameMessage("");
	endMessage->addNext(tmpMessage);
	endMessage = tmpMessage;

	//frameMessage�̃T�C�Y��5
	frameMessage.push_back("");
	frameMessage.push_back("");
	frameMessage.push_back("");
	frameMessage.push_back("");
	frameMessage.push_back("");
	
}

void StringController::update()
{
	mTime++;
	mTimeFromLastAdd++;
	message_dy = min(mTimeFromLastAdd, 25);
}

void StringController::draw() const
{
	DrawGraph(0, 330, mFrameImg, true);

	beginMessage->draw(50, 470 + message_dy);

	DrawGraph(0, 330, mUpperImg, true);
}

//frameMessage���X�V
void StringController::addMessage(string _message)
{
	//���ɒǉ�
	FrameMessage* tmpMessage = new FrameMessage(_message);
	endMessage->addNext(tmpMessage);
	endMessage = tmpMessage;

	//�擪��t���ւ�
	FrameMessage* postBegin = beginMessage;
	beginMessage = beginMessage->get(1);
	SAFE_DELETE(postBegin);

	mTimeFromLastAdd = message_dy = 0;
}

//���b�Z�[�W�����Z�b�g
void StringController::resetMessage()
{
	addMessage("");
	addMessage("");
	addMessage("");
	addMessage("");
	addMessage("");
}


//========================================================================
// ����private�֐�
//========================================================================

//========================================================================
// ����FrameMessage�N���X
//========================================================================
//����������Composite�ۂ�
StringController::FrameMessage::FrameMessage(string _message)
{
	message = _message;
	isEnd = true;
}

StringController::FrameMessage::~FrameMessage()
{
	this->next = 0;
}

void StringController::FrameMessage::update()
{
	//�Ō���Ȃ�return
	if (this->isEnd)return;

	//�Ō���łȂ��Ȃ玟��`��
	next->update();
}

void StringController::FrameMessage::draw(int _x, int _y) const
{
	DrawString(_x, _y, this->message.c_str(), MyData::BLACK);

	//�Ō���Ȃ�return
	if (this->isEnd)return;

	//�Ō���łȂ��Ȃ玟��`��
	next->draw(_x, _y - 25);
}

void StringController::FrameMessage::addNext(FrameMessage* _next)
{
	this->next = _next;
	this->isEnd = false;
}


void StringController::FrameMessage::setEnd(bool _isEnd)
{
	isEnd = _isEnd;
}

StringController::FrameMessage* StringController::FrameMessage::get(int num)
{
	return (num <= 0 || isEnd) ? this : next->get(num - 1);
}





}
}
}
}
