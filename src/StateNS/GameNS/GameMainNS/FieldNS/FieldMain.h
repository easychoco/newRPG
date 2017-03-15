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
	bool canPass(int, int) const;
private:
	//éüÇÃÉVÅ[Éì
	GameScene mNext;

	Stage* mStage;
	Player* mPlayer;
	GameSystem* mGameSystem;

};




}
}
}
}