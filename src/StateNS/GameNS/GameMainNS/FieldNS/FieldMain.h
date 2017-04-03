#pragma once
#include "..\GameMainChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {

class GameMain;

namespace FieldNS{


class Stage;
class Player;
class GameSystem;
class EncountAnimation;


class Main : public Child
{
public:
	Main();
	~Main();
	void initialize();
	Child* update(const GameMain*);
	void draw() const;
	bool canPass(int, int) const;
private:
	//éüÇÃÉVÅ[Éì
	GameScene mNext;

	Stage* mStage;
	Player* mPlayer;
	GameSystem* mGameSystem;
	EncountAnimation* mEAnimation;

};

class EncountAnimation
{
public:
	EncountAnimation();
	~EncountAnimation();
	void initialize();
	bool update();
	void draw() const;
	bool cancelEncount() const;

private:
	int mTime;
};





}
}
}
}