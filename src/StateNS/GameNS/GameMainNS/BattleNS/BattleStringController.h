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

private:
	int mFrameImg;

	//枠に表示する文字の配列
	vector<string> frameMessage{};

	//文字を書く位置, BattleFrame.pngに依存
	array<const int, 4> frameLine{ 371, 394, 418, 442 };

};
















}
}
}
}