#pragma once

#include "..\..\..\..\Data.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace BattleNS {


class Stage
{
public:
	Stage(int);
	~Stage();
	void initialize(int);
	void update();
	void draw() const;

private:
	int mBackImg;
};
















}
}
}
}