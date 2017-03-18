#pragma once

#include "..\..\..\..\Data.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace BattleNS {


class Stage
{
public:
	Stage();
	~Stage();
	void initialize();
	void update();
	void draw() const;

private:
	int mBackImg;
};
















}
}
}
}