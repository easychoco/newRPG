#include "Converse.h"

#include "..\..\..\Data.h"
#include "..\..\..\KeyInput.h"
#include "BattleNS\BattleStringController.h"
#include <fstream>

namespace StateNS {
namespace GameNS {


Converse::Converse(char* textName)
{
	string name = "Data/Text/Converse/";
	name += textName;
	name += ".txt";

	std::ifstream fin(name);
	if (!fin)assert(!"Converse : file input error!");
	//全文読み込み
	while (!fin.eof())
	{
		string tmp;
		fin >> tmp;
		mAllText.push_back(tmp);
	}

	//最後の行を表示するために空白行を加える
	mAllText.push_back("");
	fin.close();

	initialize();
}

Converse::~Converse()
{

}

void Converse::initialize()
{

	toImage[0] = LoadGraph("Data/Image/Converse/player.png");
	toImage[1] = LoadGraph("Data/Image/Converse/king.png");
	toImage[2] = LoadGraph("Data/Image/Converse/princess.png");

	bool isErr = (toImage[0] != -1) & (toImage[1] != -1) & (toImage[2] != -1);
	assert(isErr && "画像読み込みエラー");

	mLeftNum = 0;
	mRightNum = 0;

	mTime = 0;
	mNowText = 0;
	fin = false;
	mPrePush = false;

	sController = new StringController();

	nextText();

	//for Debug
	mLeftNum = 0;
	mRightNum = 1;
}

bool Converse::update()
{
	mTime++;

	sController->update();

	//Zキーでテキスト送り
	if (!fin && !mPrePush && Input_Z())
	{
		nextText();
	}

	mPrePush = Input_Z();

	//finがtrueかつＺキーが押されていたらConverseが終わり
	return fin && Input_Z();
}

void Converse::draw() const
{
	//アルファチャンネルで薄い背景を描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
	DrawBox(0, 0, 640, 480, MyData::WHITE, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//会話者を描画
	DrawGraph(0, 0, toImage[mLeftNum], true);
	DrawTurnGraph(350, 0, toImage[mRightNum], true);

	//テキストを描画
	sController->draw();

	DrawFormatString(0, 30, 0, "%d %d", mAllText.size(), mNowText);
	DrawFormatString(0, 60, 0, "%d", fin && !mPrePush && Input_Z());
}

//==============================================
//内部プライベート関数
//==============================================
void Converse::nextText()
{
	sController->addMessage(mAllText[mNowText]);

	mNowText++;
	if (mNowText >= (int)mAllText.size())fin = true;
}


}
}

