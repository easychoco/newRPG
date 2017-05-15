#pragma once

#include <vector>
#include <array>


namespace StateNS {
namespace GameNS {

class Play;
using GameParent = Play;

namespace GameMainNS{


class Child;

class Converse;
class Pause;

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
	void changeParty();
	void forceEncount(int monsterID);
	
	struct Status {
		int ID;
		int h, a, b, c, d, s;
	};	

	std::vector<Status> players;

private:
	Child* mChild;
	Converse* mConverse;
	Pause* mPause;

	bool partyChanged;

};




}
}
}