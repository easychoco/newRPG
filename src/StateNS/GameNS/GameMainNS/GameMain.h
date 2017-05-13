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
	std::array<int, 4> getParty() const { return party; }
	void setParty(std::array<int, 4>);
	
	struct Status {
		int ID;
		int h, a, b, c, d, s;
	};	

	std::vector<Status> players;

private:
	Child* mChild;
	Converse* mConverse;
	Pause* mPause;

	//パーティメンバー 中はIDを記憶
	std::array<int, 4> party{ 0, 1, 2, 4 };
};




}
}
}