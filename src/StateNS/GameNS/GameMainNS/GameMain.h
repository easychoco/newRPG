#pragma once



namespace StateNS {
namespace GameNS {

class Play;
using GameParent = Play;

namespace GameMainNS{

class Child;

class GameMain
{
public:
	GameMain();
	~GameMain();
	void initialize();
	void update(GameParent*);
	void draw() const;

private:
	Child* mChild;
};




}
}
}