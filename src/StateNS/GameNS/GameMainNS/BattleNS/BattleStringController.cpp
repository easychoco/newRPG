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

	//FrameMessageの先頭と最後尾を設定
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

	//frameMessageのサイズは5
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

//frameMessageを更新
void StringController::addMessage(string _message)
{
	//後ろに追加
	FrameMessage* tmpMessage = new FrameMessage(_message);
	endMessage->addNext(tmpMessage);
	endMessage = tmpMessage;

	//先頭を付け替え
	FrameMessage* postBegin = beginMessage;
	beginMessage = beginMessage->get(1);
	SAFE_DELETE(postBegin);

	mTimeFromLastAdd = message_dy = 0;
}

//メッセージをリセット
void StringController::resetMessage()
{
	addMessage("");
	addMessage("");
	addMessage("");
	addMessage("");
	addMessage("");
}


//========================================================================
// 内部private関数
//========================================================================

//========================================================================
// 内部FrameMessageクラス
//========================================================================
//そういえばCompositeぽい
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
	//最後尾ならreturn
	if (this->isEnd)return;

	//最後尾でないなら次を描画
	next->update();
}

void StringController::FrameMessage::draw(int _x, int _y) const
{
	DrawString(_x, _y, this->message.c_str(), MyData::BLACK);

	//最後尾ならreturn
	if (this->isEnd)return;

	//最後尾でないなら次を描画
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
