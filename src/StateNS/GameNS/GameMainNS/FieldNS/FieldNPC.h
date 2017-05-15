#pragma once

#include "..\..\..\..\Data.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {

class GameMain;

namespace FieldNS {

class NPC
{
public:
	virtual ~NPC() {}
	virtual void update(GameMain*) = 0;
	virtual void draw(const Vector2* player) const = 0;
	virtual bool isAlive() { return true; }
	void talk(const Vector2*);
	bool canPass(int, int);
protected:
	virtual void talkEvent() = 0;
	Vector2* point;
};

class Ally : public NPC
{
public:
	Ally(int, int, char* fileName, char *eventFile);
	~Ally();
	void update(GameMain*);
	void draw(const Vector2* _player) const;
private:
	int mTime;
	int mImg[12];
	int mGraphNum;
	const int pointRate = MyData::vectorRate;
	char* eventFile;
	bool toEvent;
	
	void talkEvent();
	void initialize();
};

class Monster : public NPC
{
public:
	Monster(int x, int y, int ID, char* fileName);
	~Monster();
	void update(GameMain*);
	void draw(const Vector2* _player) const;
	bool isAlive() { return mIsAlive; };
private:
	int mMonsterID;
	int mImg[12];
	int mTime;
	int mGraphNum;
	const int pointRate = MyData::vectorRate;
	char* eventFile;
	bool toEvent;
	bool mIsAlive;

	void talkEvent();
	void initialize();
};

}
}
}
}