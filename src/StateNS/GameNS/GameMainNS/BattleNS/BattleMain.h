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
	Main(Vector2, int);
	~Main();
	void initialize(int);
	Child* update(const GameMain*);
	void draw() const;

private:
	Stage* stage;

	ActionController* aController;
	StringController* sController;

	BattleChild* mChild;
	int mTime;
	int mFinTime = 0;
	
	//プレイヤーのフィールドでの位置
	const Vector2 mPlayerPos;

	//プレイヤーと敵が一緒に入っている配列
	vector<Actor*> actors;

	//プレイヤーの配列
	vector<Actor*> players;

	//敵の配列
	vector<Actor*> enemies;

	//Actorの配列を作成
	void addActor(int);

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

class FirstAnimation : public BattleChild
{
public:
	FirstAnimation(vector<Actor*>);
	~FirstAnimation();
	void initialize();
	BattleChild* update(ActionController*, StringController*, vector<Actor*>);
	void draw(ActionController*) const;
	bool goField() const { return false; }
private:
	int mTime;

	//バトル開始時のアニメーション
	//Strategy
	class AnimeChild
	{
	public:
		virtual ~AnimeChild() {};
		virtual void draw(int) const = 0;
	};

	class Anime1 : public AnimeChild
	{
	public:
		Anime1() {};
		~Anime1() {};
		void draw(int _time)  const;
	};

	class Anime2 : public AnimeChild
	{
	public:
		Anime2() {};
		~Anime2() {};
		void draw(int _time)  const;
	};

	class Anime3 : public AnimeChild
	{
	public:
		Anime3() {};
		~Anime3() {};
		void draw(int _time)  const;
	};

	class Anime4 : public AnimeChild
	{
	public:
		Anime4() {};
		~Anime4() {};
		void draw(int _time)  const;
	};

	AnimeChild* mChild;
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
	int mFinTime = 0;

	//バトルが終わったか
	bool finBattle(const vector<Actor*>) const;

	//バトル終了後のメッセージを出力
	void updateMessage(StringController*, bool);

	//バトルで得られる経験値を計算
	int calcExp(vector<Actor*>);
};

//========================================================================
//バトル後のリザルト画面
//Stateパターンだぜ
//========================================================================
class Result : public BattleChild
{
public:
	Result(int);
	~Result();
	void initialize(vector<Actor*>);
	BattleChild* update(ActionController*, StringController*, vector<Actor*>);
	void draw(ActionController*) const;
	bool goField() const;

private:
	class ResultStatus
	{
	public:
		ResultStatus(Actor*, int);
		~ResultStatus() { DeleteGraph(mImg); };
		void initialize(Actor*, int);
		void update();
		void draw(int, int) const;

		//セーブ用の文字列を作成
		string getSaveString();

		//次に行っていいか(レベルアップのアニメーションは終わったか)
		bool goNext() const;

	private:
		//セーブ用
		int ID;
		std::string name;

		int mTime;
		int mImg;

		int mAllExp;
		int mNowExp;
		int mAfterExp;

		bool mLevelUp;
		int mLevelTime;
	};

	bool initialized;
	int mImg;
	int mBackImg;
	int mTime;
	const int mGetExp;

	vector< ResultStatus* > players{};

	//外部データにセーブ
	void saveData();
};





}
}
}
}