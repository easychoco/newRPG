#pragma once

#include "..\..\..\..\Data.h"



namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace BattleNS {


class StringController
{
public:
	StringController();
	~StringController();
	void initialize();
	void update();
	void draw() const;
	void addMessage(string _message);
	void resetMessage();

private:
	int mFrameImg;

	//˜g‚É•\¦‚·‚é•¶š‚Ì”z—ñ
	vector<string> frameMessage{};

	//•¶š‚ğ‘‚­ˆÊ’u, BattleFrame.png‚ÉˆË‘¶
	array<const int, 4> frameLine{ 371, 394, 418, 442 };

};
















}
}
}
}