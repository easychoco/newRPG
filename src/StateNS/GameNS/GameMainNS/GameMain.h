#pragma once

#include <string>
#include <vector>



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

	struct Status {
		int ID;
		int h, a, b, c, d, s;
	};

	std::vector<Status> players;

private:
	Child* mChild;
	void loadPlayerData();
};




}
}
}