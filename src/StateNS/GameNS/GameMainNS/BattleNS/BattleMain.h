#pragma once
#include "..\GameMainChild.h"
#include "..\GameMain.h"
#include "..\..\..\..\Data.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {

class GameMain;

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
	Main(const GameMain*);
	~Main();
	void initialize(vector<GameMainNS::GameMain::Status>);
	Child* update(const GameMain*);
	void draw() const;

private:
	Stage* stage;

	ActionController* aController;
	StringController* sController;

	GameScene mNext;
	BattleChild* mChild;
	int mTime;
	int mFinTime = 0;

	//プレイヤーと敵が一緒に入っている配列
	vector<Actor*> actors;

	//プレイヤーの配列
	vector<Actor*> players;

	//敵の配列
	vector<Actor*> enemies;

	//Actorの配列を作成
	void addActor(vector<GameMainNS::GameMain::Status>);

	//プレイヤーのステータスを描画する
	void drawStatus(int, int, const vector<Actor*>&) const;

	//バトルが終わったかを判定する
	bool finBattle() const;

	//HPを計算する
	int calcHP(int, int) const;

	//能力値を計算する
	int calcStatus(int, int) const;

};

//========================================================================
// バトル中の場面
//========================================================================
class BattleChild
{
public:
	virtual ~BattleChild() {};
	virtual BattleChild* update(ActionController*, StringController*, vector<Actor*>) = 0;
	virtual void draw(ActionController*) const = 0;
	virtual bool goField() const = 0;
};

//========================================================================
//バトルでの行動決定場面クラス
//Stateパターンだぜ
//========================================================================
class Decide : public BattleChild
{
public:
	Decide(vector<Actor*>);
	~Decide();
	void initialize(vector<Actor*>&);
	BattleChild* update(ActionController*, StringController*, vector<Actor*>);
	void draw(ActionController*) const;
	bool goField() const { return false; }
private:
	int doneNum = 0;

	//行動を決めるときのキュー
	//中身はプレイヤーと敵が行動順に入っている
	queue<Actor*> act_que;

	vector<Actor*> enemies;
	vector<Actor*> players;

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
	BattleChild* update(ActionController*, StringController*, vector<Actor*>);
	void draw(ActionController*) const;
	bool goField() const { return false; }

private:
	//バトルが終わったか
	bool finBattle(const vector<Actor*>) const;
};


//========================================================================
//バトル後のリザルト画面
//Stateパターンだぜ
//========================================================================
class Result : public BattleChild
{
public:
	Result();
	~Result();
	void initialize();
	BattleChild* update(ActionController*, StringController*, vector<Actor*>);
	void draw(ActionController*) const;
	bool goField() const;

private:
	int mImg;
	int mBackImg;
	int mTime;

	void drawResult(int, int, int) const;

};



}
}
}
}