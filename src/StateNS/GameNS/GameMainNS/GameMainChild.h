#pragma once


namespace StateNS {
namespace GameNS {

class Play;
using GameParent = Play;

namespace GameMainNS{

enum GameScene
{
	SCENE_FIELD,
	SCENE_BATTLE,

	SCENE_NONE,
};

class Child
{
public:
	virtual ~Child() {};
	virtual void update(GameParent*) = 0;
	virtual void draw() const = 0;
	virtual GameScene changeScene() = 0;
};




}
}
}