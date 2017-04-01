#include "BattlePlayer.h"
#include "BattleStringController.h"

#include "..\..\..\..\KeyInput.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace BattleNS {


Player::Player(Status _s, int _exp) : 
Actor(_s, _exp)
{
	initialize(); 
};

Player::~Player()
{
	SAFE_DELETE(act);
}

void Player::initialize()
{
	//この関数は各ターンの初めにも呼ばれる
	//actはターンごとに新しくするから,以前のものはdelete
	SAFE_DELETE(act);

	mState = SELECT_MOVE;
	mMove = mCursorPos = 0;
	mPrePush = true;
	mFirstCome = true;
}

bool Player::attack(StringController* _sController, const vector<Actor*>& _enemies)
{
	//初めて来たときの処理
	if (mFirstCome)
	{
		string s_tmp = status.name;
		s_tmp += "はどうする？";
		_sController->addMessage(s_tmp);
		mFirstCome = false;
	}

	//前のフレームでキーが押されていなければ
	if (!mPrePush) {

		//カーソル移動
		if (Input_UP())mCursorPos--;
		if (Input_DOWN())mCursorPos++;


		int max_num = ((mState == SELECT_MOVE) ? 3 : (int)_enemies.size() - 1);
		mCursorPos = max(mCursorPos, 0);
		mCursorPos = min(mCursorPos, max_num);

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
				act = new Action(status.ID, _enemies[mCursorPos]->status.ID, toAction[mMove]);
				return true;
			}
		}

		//Xで戻る
		if (Input_X())
		{
			mState = SELECT_MOVE;
			mCursorPos = 0;
		}
	}

	//prepushを更新
	mPrePush = (Input_UP() | Input_DOWN() | Input_Z());
	return false;
}


void Player::draw(vector<Actor*> _enemies) const
{
	//DrawRotaGraph(_x, _y, 1.0, 0.0, mImg, true);

	//行動決定部分の描画
	//攻撃対象決定画面でも描画される
	DrawBox(210, 180, 320, 330, MyData::BLACK, true);

	DrawFormatString(230, 200, MyData::WHITE, "こうげき");
	DrawFormatString(230, 230, MyData::WHITE, "まほう");
	DrawFormatString(230, 260, MyData::WHITE, "とくしゅ");
	DrawFormatString(230, 290, MyData::WHITE, "にげる");//TODO -> "逃げる"の実装
	DrawCircle(220, 205 + mMove * 30, 5, MyData::WHITE);

	//攻撃対象決定画面
	if (mState == SELECT_TARGET)
	{
		DrawBox(330, 180, 420, 330, MyData::BLACK, true);
		DrawCircle(340, 205 + 30 * mCursorPos, 5, MyData::WHITE);

		int i = 0;
		for (auto &enemy : _enemies)
		{
			unsigned color = ((enemy->status.isEnemy) ? MyData::RED : MyData::GREEN);
			DrawFormatString(350, 200 + 30 * i, color, "%s", enemy->status.name.c_str());
			i++;
		}
	}

}


//========================================================================
// 内部private関数
//========================================================================






}
}
}
}
