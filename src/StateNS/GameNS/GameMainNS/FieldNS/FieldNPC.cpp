#include "FieldNPC.h"
#include "FieldMain.h"
#include "..\GameMain.h"

#include "..\..\..\..\KeyInput.h"

#include <cmath>


namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace FieldNS {


//============================
//スーパークラス
//============================

void NPC::talk(const Vector2* _player)
{
	if ( ( abs(this->point->x + 16000 - _player->x) < 16000 ) && ( abs(this->point->y - _player->y) < 48000 ) )
		this->talkEvent();
}

bool NPC::canPass(int _px, int _py)
{
	return !(_px / 32 / MyData::vectorRate == this->point->x / 32 / MyData::vectorRate
		  && _py / 32 / MyData::vectorRate == this->point->y / 32 / MyData::vectorRate);
}

//============================
//継承クラス
//============================

//味方NPC
Ally::Ally(int _x, int _y, char* _fileName, char* _eventFile)
{
	point = new Vector2(_x, _y);
	LoadDivGraph(_fileName, 12, 3, 4, 32, 32, mImg);
	eventFile = _eventFile;
	initialize();
}

void Ally::initialize()
{
	mTime = 90;
	mGraphNum = 0;
	toEvent = false;
}

Ally::~Ally()
{
	SAFE_DELETE(point)
}

void Ally::update(GameMain* _gameMain)
{
	mTime++;
	mGraphNum = mTime / 10 % 3;

	if (toEvent)
	{
		_gameMain->toConverse(eventFile);
		toEvent = false;
		mTime = 0;
	}
}

void Ally::draw(const Vector2* _player) const
{
	//マップ描画をする際に，自機の位置依存で描画位置のy座標が変わる
	//自機が真ん中にいるとき
	int draw_y = _player->y / MyData::vectorRate - MyData::CY;

	//下端
	if (_player->y / MyData::vectorRate > MyData::MAP_HEIGHT - MyData::CY)draw_y = MyData::MAP_HEIGHT - 480;

	//上端
	else if (_player->y / MyData::vectorRate < MyData::CY)draw_y = 0;

	//右側と左側のマップにいるときでfor文内部変数のxの範囲が変わる
	int x_sub = (_player->x / MyData::vectorRate < MyData::MAP_WIDTH / 2) ? 0 : 640000;


	DrawGraph((point->x - x_sub) / pointRate, point->y / pointRate - draw_y, mImg[mGraphNum], true);
}

//============================
//内部private関数
//============================
void Ally::talkEvent()
{
	toEvent = mTime > 60;
}

//==========================================
//敵NPC
//==========================================
Monster::Monster(int _x, int _y, int _ID, char* _eventFile)
{
	point = new Vector2(_x, _y);
	mMonsterID = _ID;
	eventFile = _eventFile;
	initialize();
}

Monster::~Monster()
{
	SAFE_DELETE(point);
}

void Monster::initialize()
{
	mTime = 0;
	mGraphNum = 0;
	toEvent = false;
	mIsAlive = true;

	LoadDivGraph("Data/Image/Character/king.png", 12, 3, 4, 32, 32, mImg);
}

void Monster::update(GameMain* _gameMain)
{
	mTime++;
	mGraphNum = mTime / 10 % 3;

	if (toEvent)
	{
		_gameMain->toConverse(eventFile);
		toEvent = false;
		mTime = -10;
	}
	if (mTime == -9)
	{
		_gameMain->forceEncount(mMonsterID);
		mIsAlive = false;
	}

}

void Monster::draw(const Vector2* _player) const
{
	//マップ描画をする際に，自機の位置依存で描画位置のy座標が変わる
	//自機が真ん中にいるとき
	int draw_y = _player->y / MyData::vectorRate - MyData::CY;

	//下端
	if (_player->y / MyData::vectorRate > MyData::MAP_HEIGHT - MyData::CY)draw_y = MyData::MAP_HEIGHT - 480;

	//上端
	else if (_player->y / MyData::vectorRate < MyData::CY)draw_y = 0;

	//右側と左側のマップにいるときでfor文内部変数のxの範囲が変わる
	int x_sub = (_player->x / MyData::vectorRate < MyData::MAP_WIDTH / 2) ? 0 : 640000;

	DrawGraph((point->x - x_sub) / pointRate, point->y / pointRate - draw_y, mImg[mGraphNum], true);
}

//============================
//内部private関数
//============================
void Monster::talkEvent()
{
	toEvent = true;
}





}
}
}
}