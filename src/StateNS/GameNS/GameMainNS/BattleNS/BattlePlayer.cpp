#include "BattlePlayer.h"

#include "..\..\..\..\KeyInput.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace BattleNS {

Player::Player(Status _s) : 
Actor(_s) 
{
	initialize(); 
};

Player::~Player()
{

}

void Player::initialize()
{
	mState = SELECT_MOVE;
	mMove = mCursorPos = 0;
	mPrePush = true;
}

bool Player::attack()
{
	//前のフレームでキーが押されていなければ
	if (!mPrePush) {

		//カーソル移動
		if (Input_UP())mCursorPos--;
		if (Input_DOWN())mCursorPos++;

		mCursorPos = max(mCursorPos, 0);
		mCursorPos = min(mCursorPos, 3);

		//行動決定場面
		if (mState == SELECT_MOVE)mMove = mCursorPos;

		//決定ボタン
		if (Input_Z())
		{
			//行動決定画面なら対象決定へ
			if (mState == SELECT_MOVE)
			{
				mCursorPos = 0;
				mState = SELECT_TARGET;
			}

			//対象決定画面なら次へ
			else if (mState == SELECT_TARGET)
			{
				//攻撃対象はmCursorPos
				act = new Action(status.ID, mCursorPos, toAction[mMove]);
				return true;
			}
		}

		//Xで戻る
		if (Input_X())
			mState = SELECT_MOVE;
	}

	//prepushを更新
	mPrePush = (Input_UP() | Input_DOWN() | Input_Z());

	return false;
}


void Player::draw(int _x, int _y) const
{
	DrawRotaGraph(_x, _y, 1.0, 0.0, mImg, true);

	//行動決定部分の描画
	//攻撃対象決定画面でも描画される
	DrawBox(150, 180, 300, 330, MyData::BLACK, true);

	DrawFormatString(200, 200, MyData::WHITE, "こうげき");
	DrawFormatString(200, 230, MyData::WHITE, "まほう");
	DrawFormatString(200, 260, MyData::WHITE, "とくしゅ");
	DrawFormatString(200, 290, MyData::WHITE, "にげる");//TODO -> "逃げる"の実装
	DrawCircle(190, 205 + mMove * 30, 5, MyData::WHITE);

	//攻撃対象決定画面
	if (mState == SELECT_TARGET)
	{
		DrawBox(310, 180, 400, 330, MyData::BLACK, true);
		DrawFormatString(330, 200, MyData::WHITE, "てき %d", mCursorPos);
	}

}


//========================================================================
// 内部private関数
//========================================================================






}
}
}
}
