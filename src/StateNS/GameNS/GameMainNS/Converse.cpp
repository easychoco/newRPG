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
	SAFE_DELETE(sController);
}

void Converse::initialize()
{

	toImage[0] = LoadGraph("Data/Image/Converse/player.png");
	toImage[1] = LoadGraph("Data/Image/Converse/king.png");
	toImage[2] = LoadGraph("Data/Image/Converse/princess.png");

	bool isErr = (toImage[0] != -1) & (toImage[1] != -1) & (toImage[2] != -1);
	assert(isErr && "Converse : 画像読み込みエラー");

	mLeftNum = 0;
	mRightNum = 0;

	mTime = 0;
	mNowText = 0;
	fin = false;
	mPrePush = false;

	sController = new StringController();

	nextText();
}

bool Converse::update()
{
	mTime++;

	sController->update();

	bool push_Z = !mPrePush && Input_Z();
	mPrePush = Input_Z();

	//Zキーでテキスト送り
	if (!fin && push_Z)
	{
		nextText();
	}

	//finがtrueかつＺキーが押されていたらConverseが終わり
	return fin && push_Z;
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

	//for Debug
	DrawFormatString(0, 30, 0, "%d %d", mAllText.size(), mNowText);
}

//==============================================
//内部プライベート関数
//==============================================
void Converse::nextText()
{
	string text = mAllText[mNowText];

	//最後の文章または規格外の文章が読み込まれたら終了
	if (text.size() < 2)
	{
		fin = true;
		return;
	}

	//会話者を設定
	mLeftNum = (char)(text[0]) - 48;
	mRightNum = (char)(text[1]) - 48;

	//ヘッダの切り落とし
	text.erase(text.begin(), text.begin() + 2);


	//文章を更新
	sController->addMessage(text);

	mNowText++;
}



}
}

