#pragma once

#include "GameMainChild.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class MiddleChild;

class MiddleMain : public Child
{
public:
	MiddleMain(GameScene);
	~MiddleMain();
	void initialize();
	Child* update(GameParent*);
	void draw() const;

private:
	MiddleChild* mChild;
	GameScene nextScene;
	int mTime;
};

//MiddleMain‚Å‚Â‚©‚¤State‚ÌChild
class MiddleChild
{
public:
	virtual ~MiddleChild() {};
	virtual void update() = 0;
	virtual void draw() const = 0;
	bool goNext() { return mGoNext; }
protected :
	bool mGoNext = false;
};

class ToBattle : public MiddleChild
{
public:
	ToBattle();
	~ToBattle();
	void initialize();
	void update();
	void draw() const;
private:
	int mTime;
};

class ToField : public MiddleChild
{
public:
	ToField();
	~ToField();
	void initialize();
	void update();
	void draw() const;
private:
	int mTime;
};


}
}
}