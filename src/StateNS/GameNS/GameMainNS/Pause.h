#pragma once

#include<array>
#include<string>

using std::array;
using std::string;

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class GameMain;

class Pause
{
public:
	Pause(array<int, 4>);
	~Pause();
	void initialize(array<int, 4>);
	bool update(GameMain*);
	void draw() const;
private:

	//-----------------------------------------
	//State
	//-----------------------------------------
	class PauseChild
	{
	public:
		virtual ~PauseChild() {};
		virtual PauseChild* update(GameMain*) = 0;
		virtual void draw() const = 0;
		virtual bool finPause() const = 0;
		void setParty(array<int, 4> _p) { this->party = _p; }
	protected:
		bool prePush = false;
		array<int, 4> party;
	};
	//-----------------------------------------
	class Home : public PauseChild
	{
	public:
		Home();
		~Home();
		PauseChild* update(GameMain*);
		void draw() const;
		bool finPause() const;
	private:
		int mTime;
		int mCursorPos;
		int mMenuImg;
		int mCursorImg;
		int mPartyImg[4][12];
		bool initialized;

		void initialize();
		string getFileName(char*);
		void drawParty() const;
		void drawChara(int, int, int) const;
	};
	//-----------------------------------------
	class PartyChange : public PauseChild
	{
	public:
		PartyChange();
		~PartyChange();
		PauseChild* update(GameMain*);
		void draw() const;
		bool finPause() const;
	private:
		void initialize();
	};
	//-----------------------------------------
	class Config : public PauseChild
	{
	public:
		Config();
		~Config();
		PauseChild* update(GameMain*);
		void draw() const;
		bool finPause() const;
	private:
		void initialize();
	};
	//-----------------------------------------
	class Save : public PauseChild
	{
	public:
		Save();
		~Save();
		PauseChild* update(GameMain*);
		void draw() const;
		bool finPause() const;
	private:
		void initialize();
	};
	//-----------------------------------------
	class Load : public PauseChild
	{
	public:
		Load();
		~Load();
		PauseChild* update(GameMain*);
		void draw() const;
		bool finPause() const;
	private:
		void initialize();
	};

	//ÉÅÉìÉoïœêî
	PauseChild* child;

};



}
}
}