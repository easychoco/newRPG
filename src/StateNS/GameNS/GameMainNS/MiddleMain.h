#pragma once

#include "GameMainChild.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class MiddleChild;
namespace BattleNS 
{
	class StringController;
}

class MiddleMain : public Child
{
public:
	MiddleMain(GameScene, int arg);//arg は敵レベル，または獲得経験値
	~MiddleMain();
	void initialize(int);
	Child* update(GameParent*);
	void draw() const;

private:
	MiddleChild* mChild;
	GameScene nextScene;
	int arg;
};

//MiddleMainでつかうStateのChild
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
	ToBattle(int _arg);
	~ToBattle();
	void initialize(int);
	void update();
	void draw() const;
private:
	int mTime;

	//敵レベル
	int arg;
};

class ToField : public MiddleChild
{
public:
	ToField(int _arg);
	~ToField();
	void initialize(int);
	void update();
	void draw() const;
private:
	int mTime;

	int mImg;
	int mBackImg;

	//経験値
	int arg;

	//バトルに勝ったかどうか
	bool win;

	//メッセージ描画
	BattleNS::StringController* sController;

	//経験値とかステータス表示
	void drawResult(int x, int y, int img) const;
};



}
}
}