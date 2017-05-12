#pragma once

#include <string>
#include <vector>



namespace StateNS {
namespace GameNS {

class Play;
using GameParent = Play;

class Converse;
class Pause;

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
	void toConverse(char* fileName);
	void toPause();

	struct Status {
		int ID;
		int h, a, b, c, d, s;
	};	

	std::vector<Status> players;

private:
	Child* mChild;
	Converse* mConverse;
	Pause* mPause;

};




}
}
}