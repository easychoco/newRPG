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


class Main : public Child
{
public:
	Main(Vector2);
	~Main();
	void initialize(Vector2);
	Child* update(GameMain*);
	void draw() const;
	bool canPass(int, int) const;
	void loadParty();
	const array<int, 4> getParty() const;
private:

	Stage* mStage;
	Player* mPlayer;
	GameSystem* mGameSystem;
	EncountAnimation* mEAnimation;
	int mBGM;

	array<int, 4> party;
};

class EncountAnimation
{
public:
	EncountAnimation();
	~EncountAnimation();
	void initialize();
	bool update();
	void draw() const;
	bool cancelEncount() const;

private:
	int mTime;
	

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