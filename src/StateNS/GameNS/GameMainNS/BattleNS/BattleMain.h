#pragma once
#include "..\GameMainChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace BattleNS{


class Main : public Child
{
public:
	Main();
	~Main();
	void initialize();
	void update(GameParent*);
	void draw() const;
	GameScene changeScene();
private:
	GameScene mNext;
};




}
}
}
}