#pragma once

#include "..\..\..\..\Data.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace FieldNS {

class NPC
{
public:
	virtual ~NPC() {}
	virtual void update() = 0;
	virtual void draw() const = 0;
	void talk(Vector2);
protected:
	virtual void talkEvent() = 0;
	Vector2 point;
};

class Ally : public NPC
{
public:
	Ally(int, int);
	~Ally();
	void update();
	void draw() const;
private:
	void talkEvent();
};

class Monster : public NPC
{
	Monster(int, int);
	~Monster();
	void update();
	void draw() const;
private:
	void talkEvent();

};

}
}
}
}