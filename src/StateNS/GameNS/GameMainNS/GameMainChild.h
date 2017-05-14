#pragma once

#include <vector>
#include <array>

namespace StateNS {
namespace GameNS {

namespace GameMainNS{

class GameMain;

enum GameScene
{
	SCENE_FIELD,
	SCENE_BATTLE,
	SCENE_MIDDLE,

	SCENE_NONE,
};

class Child
{
public:
	virtual ~Child() {};
	virtual Child* update(GameMain*) = 0;
	virtual void draw() const = 0;
	virtual void loadParty() = 0;
};




}
}
}