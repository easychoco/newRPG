#pragma once

#include "CharacterData.h"

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
	Pause();
	~Pause();
	void initialize();
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
		void setParty();//ファイルからパーティ情報を読み込み
	protected:
		struct Chara { int ID; string name; int exp; };

		bool prePush = false;
		array<Chara, 4> party;
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
		bool isFin;
		bool initialized;
		array<char*, 5> toString
		{
			"パーティメンバーを入れ替えます",
			"いろいろな設定をします",
			"データをセーブします",
			"セーブデータをロードします",
			"もどります",
		};

		void initialize();
		string getFileName(char*);
		void drawParty() const;
		void drawChara(int, int, int) const;
		void drawMessage() const;
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
		enum PartyEdit
		{
			EDIT_PARTY,
			EDIT_CHARA,
		};
		PartyEdit pEdit;
		int drawNum;
		int mUpImg[CharacterData::CharaNumber];
		int mMoveImg[CharacterData::CharaNumber][12];

		int mTime;
		int mSelectedChara;
		int mNowSelect;


		void initialize();
		void editParty(GameMain*);
		bool checkParty();
		void save();
		void drawChara(int, int, int) const;
		void drawStatus() const;
		void drawParty() const;
		string getUpFileName(char*);
		string getMoveFileName(char*);
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

	//メンバ変数
	PauseChild* child;

};



}
}
}