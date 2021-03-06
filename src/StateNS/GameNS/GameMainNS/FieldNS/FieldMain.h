#pragma once
#include "..\GameMainChild.h"
#include "..\..\..\..\Data.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS {

class GameMain;

namespace FieldNS{


class Stage;
class Player;
class GameSystem;
class EncountAnimation;
class NPC;

class Main : public Child
{
public:
	Main(Vector2);
	Main(Vector2, bool isEscape);
	~Main();
	Child* update(GameMain*);
	void draw() const;
	bool canPass(int, int) const;
	void loadParty();
	void loadData() { initialize(); };
	const array<int, 4> getParty() const;
	void talkWithNPC(Vector2*);
	void forceEncount(int monsterID);

private:
	Stage* mStage;
	Player* mPlayer;
	GameSystem* mGameSystem;
	EncountAnimation* mEAnimation;
	int mBGM;
	int monsterID;
	static int nextMonster;
	static bool isTalkWithSymbol;
	
	void initialize();
	void initialize(Vector2);

	vector<NPC*> NPCs;
	array<int, 4> party;
};

class EncountAnimation
{
public:
	EncountAnimation(bool);
	~EncountAnimation();
	void initialize();
	bool update();
	void draw() const;
	bool cancelEncount() const;

private:
	int mTime;
	bool cancelable;

	//バトル開始時のアニメーション
	class AnimeChild
	{
	public:
		virtual ~AnimeChild(){};
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





}
}
}
}