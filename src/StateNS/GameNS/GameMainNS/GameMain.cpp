#include "GameMain.h"
#include "..\Play.h"
#include "FieldNS\FieldMain.h"
#include "BattleNS\BattleMain.h"
#include "GameMainChild.h"
#include "MiddleMain.h"

#include "..\..\..\Data.h"
#include "..\..\..\KeyInput.h"
#include<fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


GameMain::GameMain(){
	initialize();
}

GameMain::~GameMain()
{
	SAFE_DELETE(mChild);
}

void GameMain::initialize()
{
	loadPlayerData();
	mChild = new BattleNS::Main(this);
}

void GameMain::update(GameParent* _parent)
{

	Child* next = mChild->update(this);

	//シーケンス遷移
	if (next != mChild)
	{
		SAFE_DELETE(mChild);
		mChild = next;
	}

}

void GameMain::draw() const
{
	DrawFormatString(0, 20, MyData::WHITE, "GameMain");
	mChild->draw();
}


//==============================================
//内部プライベート関数
//==============================================
void GameMain::loadPlayerData()
{
	std::ifstream player_in("Data/Text/PlayerData.txt");

	//キャラをひとつづつvectorに追加
	while (player_in)
	{
		int ID;
		int h{ -10 }, a{ -10 }, b{ -10 }, c{ -10 }, d{ -10 }, s{ -10 };
		player_in >> ID >> h >> a >> b >> c >> d >> s;

		if (player_in.eof())break;

		Status _s{ ID, h, a, b, c, d, s };
		players.push_back(_s);

	}

}




}
}
}