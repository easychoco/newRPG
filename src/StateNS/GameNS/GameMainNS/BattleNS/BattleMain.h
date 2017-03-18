#pragma once
#include "..\GameMainChild.h"
#include "..\..\..\..\Data.h"

#include <string>
#include <vector>


namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace BattleNS {

class Stage;
class Actor;
class Action;
class ActionController;
class StringController;
class BattleChild;

class Main : public Child
{
public:
	Main();
	~Main();
	void initialize();
	void update(GameParent*);
	void draw() const;
	GameScene changeScene();
	void addAction(Action* a);

protected:
	Stage* stage;

	ActionController* aController;
	StringController* sController;

	GameScene mNext;
	BattleChild* mChild;
	int mTime;


	//プレイヤーと敵が一緒に入っている配列
	vector<Actor*> actors;

	void addActor();

};

//========================================================================
// バトル中の場面
//========================================================================
class BattleChild
{
public:
	virtual ~BattleChild() {};
	virtual BattleChild* update(Main*) = 0;
	virtual void draw() const = 0;
};

//========================================================================
//バトルでの行動決定場面クラス
//Stateパターンだぜ
//========================================================================
class Decide : public BattleChild
{
public:
	Decide(vector<Actor*>& vec_act);
	~Decide();
	void initialize(vector<Actor*> vec_act);
	BattleChild* update(Main*);
	void draw() const;
private:
	//行動を決めるときのキュー
	//中身はプレイヤーと敵が行動順に入っている
	queue<Actor*> act_que;
};

//========================================================================
//バトルでの行動実行クラス
//Stateパターンだぜ
//========================================================================
class Battle : public BattleChild
{
public:
	Battle();
	~Battle();
	void initialize();
	BattleChild* update(Main*);
	void draw() const;
};

}
}
}
}