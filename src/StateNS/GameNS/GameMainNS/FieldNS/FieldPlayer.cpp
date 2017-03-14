#include "FieldPlayer.h"

#include "..\..\..\..\Data.h"
#include "..\..\..\..\KeyInput.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace FieldNS{


Player::Player()
{
	initialize();
}

Player::~Player()
{
	SAFE_DELETE(point);
}

void Player::initialize()
{
	point = new Vector2{ 0, 0 };
	
	int tmp = LoadDivGraph("Data/player.png", 24, 6, 4, 32, 32, mImg);
	assert(tmp == 0 && "player.png読み込みエラー!");

	mTime = 0;
	mGraphNum = 0;
}

void Player::update()
{
	mTime++;
	move(3.0f);
}

void Player::draw() const
{
	DrawFormatString(100, 20, MyData::WHITE, "Player");
	DrawFormatString(150, 20, MyData::WHITE, "%d", mGraphNum);
	//DrawCircle(point->x / pointRate, point->y / pointRate, 16, MyData::GREEN, true);
	DrawRotaGraph(point->x / pointRate, point->y / pointRate, 1.0, 0.0, mImg[mGraphNum], true);
}

//====================================
// 内部private関数
//====================================
void Player::move()
{
	move(1.0f);
}

void Player::move(float _speed)
{
	//bitmask用のフラグ
	unsigned char fDirection = 0b0000;

	//KeyInput
	//右
	if (Input_RIGHT())
	{
		fDirection |= f_right;
		//point->x += (int)(_speed * pointRate);
	}
	//左
	if (Input_LEFT())
	{
		//右キーが押されていたら押されていないことにする
		if (fDirection & f_right)fDirection ^= f_right;
		else fDirection |= f_left;
		//point->x -= (int)(_speed * pointRate);
	}
	//下
	if (Input_DOWN())
	{
		fDirection |= f_down;
		//point->y += (int)(_speed * pointRate);
	}
	//上
	if (Input_UP()) 
	{
		//下キーが押されていたら押されていないことにする
		if (fDirection & f_down)fDirection ^= f_down;
		else fDirection |= f_up;
		//point->y -= (int)(_speed * pointRate);
	}

	//キー入力がないならreturn
	if (!fDirection)
	{
		//キーが押されていなかったら棒立ちの絵にする
		//棒立ちのキャラクタチップの番号が1,4,7,10,...より
		if (mGraphNum % 3 != 1)mGraphNum = mGraphNum / 3 * 3 + 1;
		return;
	}


	//移動と画像番号指定
	//下方向への移動
	if (fDirection & f_down)
	{
		//左下
		if (fDirection & f_left)
		{
			//斜め移動はスピードダウン
			//1/√2 = 0.70710678...
			_speed *= 0.7071f;

			//左に移動
			point->x -= (int)(_speed * pointRate);

			//画像の番号指定
			mGraphNum = 3 + (mTime / 10) % 3;
		}
		//右下
		else if (fDirection & f_right)
		{
			_speed *= 0.7071f;
			point->x += (int)(_speed * pointRate);
			mGraphNum = 15 + (mTime / 10) % 3;
		}
		//真下
		else mGraphNum = (mTime / 10) % 3;

		//真下に移動
		point->y += (int)(_speed * pointRate);
	}

	//上方向への移動
	else if (fDirection & f_up)
	{
		//左上
		if (fDirection & f_left)
		{
			//斜め移動はスピードダウン
			//1/√2 = 0.70710678...
			_speed *= 0.7071f;

			//左に移動
			point->x -= (int)(_speed * pointRate);
			//画像番号を指定
			mGraphNum = 9 + (mTime / 10) % 3;
		}
		//右上
		else if (fDirection & f_right)
		{
			_speed *= 0.7071f;
			point->x += (int)(_speed * pointRate);
			mGraphNum = 21 + (mTime / 10) % 3;
		}
		//真上
		else mGraphNum = 18 + (mTime / 10) % 3;

		//真上に移動
		point->y -= (int)(_speed * pointRate);
	}

	//真右
	else if (fDirection & f_right)
	{
		point->x += (int)(_speed * pointRate);
		mGraphNum = 12 + (mTime / 10) % 3;
	}

	//真左
	else if (fDirection & f_left)
	{
		point->x -= (int)(_speed * pointRate);
		mGraphNum = 6 + (mTime / 10) % 3;
	}



	//画面外にはみ出したらだめよ
	point->x = max(point->x, 0);
	point->x = min(point->x, (640 * pointRate)); //640は画面の幅
	point->y = max(point->y, 0);
	point->y = min(point->y, (480 * pointRate)); //480は画面の高さ
}




}
}
}
}
