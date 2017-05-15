#pragma once

#include "BattleNS\BattleStringController.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

namespace BattleNS {
	class StringController;
}

using BattleNS::StringController;

class Converse
{
public:
	Converse(char* textName);
	~Converse();
	void initialize();
	bool update();
	void draw() const;

private:
	int mTime;
	int toImage[2];

	int mTalkerSide;
	int mLeftNum;
	int mRightNum;
	std::vector<string> mAllText;
	int mNowText;

	bool fin;
	bool mPrePush;

	StringController* sController;

	void nextText();
};



}
}
}
