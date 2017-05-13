#include "Pause.h"
#include "GameMain.h"

#include "CharacterData.h"
#include "..\..\..\Data.h"
#include "..\..\..\KeyInput.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS {


Pause::Pause(array<int, 4> _p)
{
	initialize(_p);
}

Pause::~Pause()
{
	SAFE_DELETE(child);
}

void Pause::initialize(array<int, 4> _p)
{
	child = new Home();
	child->setParty(_p);
}

bool Pause::update(GameMain* _gameMain)
{
	PauseChild* next = child->update(_gameMain);

	if (child != next)
	{
		SAFE_DELETE(child);
		child = next;
	}

	//パーティ変更
	//_gameMain->setParty(newParty);

	//return trueでPause解除
	return child->finPause();
}

void Pause::draw() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
	DrawBox(0, 0, 640, 480, MyData::WHITE, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	child->draw();
}


//==============================================
//内部プライベートクラス
//==============================================

//-----------------------------------------
//Home
//-----------------------------------------
Pause::Home::Home()
{
	initialized = false;
}

Pause::Home::~Home()
{

}

void Pause::Home::initialize()
{
	mCursorPos = 0;
	mMenuImg = LoadGraph("Data/Image/PauseHome.png");
	mCursorImg = LoadGraph("Data/Image/PauseCursor.png");
	assert((mMenuImg | mCursorImg) != -1 && "PauseHome画像読み込みエラー!");

	mTime = 0;

	for (int i = 0; i < 4; i++)
	{
		//パーティのmove画像読み込み
		LoadDivGraph(getFileName(toCharacter[party[i]].fileName).c_str(), 12, 3, 4, 32, 32, mPartyImg[i]);
	}

	initialized = true;

}


Pause::PauseChild* Pause::Home::update(GameMain* _gameMain)
{
	Pause::PauseChild* next = this;

	if (!initialized)initialize();

	mTime++;

	//Input
	if (!prePush)
	{
		if (Input_UP())
		{
			mCursorPos--;
		}
		if (Input_DOWN())
		{
			mCursorPos++;
		}
		//決定
		if (Input_Z())
		{
			//シーケンス遷移
			switch (mCursorPos)
			{
			case 0: next = new PartyChange(); break;
			case 1: next = new Config(); break;
			case 2: next = new Save(); break;
			case 3: next = new Load(); break;
			}
			prePush = true;
		}
		mCursorPos = (mCursorPos + 4) % 4;
	}

	prePush = Input_UP() || Input_DOWN() || Input_Z();

	return next;
}

void Pause::Home::draw() const
{
	DrawGraph(0, 0, mMenuImg, true);
	DrawGraph(-5, 25 + mCursorPos * 60, mCursorImg, true);

	drawParty();
}

bool Pause::Home::finPause() const
{
	//for Debug
	return Input_A();
}

string Pause::Home::getFileName(char* _fileName)
{
	string ret = "Data/Image/move_";
	ret += _fileName;
	ret += ".png";
	return ret;
}

void Pause::Home::drawParty() const
{
	drawChara(0, 320, 20);
	drawChara(1, 480, 20);
	drawChara(2, 320, 240);
	drawChara(3, 480, 240);
}

void Pause::Home::drawChara(int _ID, int _x, int _y) const
{
	DrawGraph(_x, _y, mPartyImg[_ID][mTime / 10 % 3], true);
	DrawFormatString(_x - 20, _y + 50, MyData::BLACK, toCharacter[party[_ID]].fileName);
}
//-----------------------------------------
//PartyChange
//-----------------------------------------
Pause::PartyChange::PartyChange()
{
	initialize();
}

Pause::PartyChange::~PartyChange()
{

}

void Pause::PartyChange::initialize()
{

}

Pause::PauseChild* Pause::PartyChange::update(GameMain* _gameMain)
{
	return this;
}

void Pause::PartyChange::draw() const
{
	DrawFormatString(0, 0, MyData::BLACK, "PartyChange");
}

bool Pause::PartyChange::finPause() const
{
	return false;
}

//-----------------------------------------
//Config
//-----------------------------------------
Pause::Config::Config()
{
	initialize();
}

Pause::Config::~Config()
{

}

void Pause::Config::initialize()
{

}

Pause::PauseChild* Pause::Config::update(GameMain* _gameMain)
{
	return this;
}

void Pause::Config::draw() const
{
	DrawFormatString(0, 0, MyData::BLACK, "Config");
}

bool Pause::Config::finPause() const
{
	return false;
}

//-----------------------------------------
//Save
//-----------------------------------------
Pause::Save::Save()
{
	initialize();
}

Pause::Save::~Save()
{

}

void Pause::Save::initialize()
{

}

Pause::PauseChild* Pause::Save::update(GameMain* _gameMain)
{
	return this;
}

void Pause::Save::draw() const
{
	DrawFormatString(0, 0, MyData::BLACK, "Save");
}

bool Pause::Save::finPause() const
{
	return false;
}

//-----------------------------------------
//Load
//-----------------------------------------
Pause::Load::Load()
{
	initialize();
}

Pause::Load::~Load()
{

}

void Pause::Load::initialize()
{

}

Pause::PauseChild* Pause::Load::update(GameMain* _gameMain)
{
	return this;
}

void Pause::Load::draw() const
{
	DrawFormatString(0, 0, MyData::BLACK, "Load");
}

bool Pause::Load::finPause() const
{
	return false;
}




}
}
}

