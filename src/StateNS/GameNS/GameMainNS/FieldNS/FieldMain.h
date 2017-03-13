#pragma once
#include "..\GameMainChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace FieldNS{


class Stage;
class Player;
class GameSystem;


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
	//次のシーン
	GameScene mNext;

	Stage* mStage;
	Player* mPlayer;
	GameSystem* mGameSystem;
};




}
}
}
}