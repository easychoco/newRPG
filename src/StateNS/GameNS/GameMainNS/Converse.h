#pragma once

#include "BattleNS\BattleStringController.h"

namespace StateNS {

class Parent;

namespace GameNS {

namespace GaemMainNS{
namespace BattleNS {
	class  StringController;
}
}

using GameMainNS::BattleNS::StringController;

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
	int toImage[3];

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
