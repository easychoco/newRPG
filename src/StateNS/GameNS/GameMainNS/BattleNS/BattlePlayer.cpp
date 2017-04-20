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

	LoadDivGraph("Data/Image/pointer.png", 4, 4, 1, 32, 32, mPointerImg);

	mState = SELECT_MOVE;
	mTime = 0;
	mMove = mCursorPos = 0;
	mPrePush = true;
	mFirstCome = true;
}

bool Player::attack(StringController* _sController, const vector<Actor*>& _enemies, const vector<Actor*>& _players)
{
	//初めて来たときの処理
	if (mFirstCome)
	{
		string s_tmp = status.name;
		s_tmp += "はどうする？";
		_sController->addMessage(s_tmp);
		mFirstCome = false;
	}

	mTime++;

	//前のフレームでキーが押されていなければ
	if (!mPrePush) {

		//カーソル移動
		if (Input_UP())mCursorPos--;
		if (Input_DOWN())mCursorPos++;

		int max_num = (mState == SELECT_MOVE) ? 4 : 
			(toAction[mMove] == Action::Actions::ACT_RECOVER) ? (int)_players.size() : 
			(int)_enemies.size();

		//カーソルが範囲からはみ出さないように調整
		mCursorPos = (mCursorPos + max_num) % max_num;

		//行動決定場面
		if (mState == SELECT_MOVE)mMove = mCursorPos;

		//決定ボタン
		if (Input_Z())
		{
			//行動決定画面なら対象決定へ
			if (mState == SELECT_MOVE)
			{
				//逃げるなら早期return
				if (toAction[mMove] == Action::Actions::ACT_ESCAPE)
				{
					act = new Action(status.ID, status.ID, Action::Actions::ACT_ESCAPE);
					return true;
				}

				//逃げないなら
				mCursorPos = 0;
				mState = SELECT_TARGET;
			}

			//対象決定画面なら次へ
			else if (mState == SELECT_TARGET)
			{
				if (toAction[mMove] == Action::Actions::ACT_RECOVER)
				{
					//回復対象はmCursorPos
					act = new Action(status.ID, _players[mCursorPos]->status.ID, Action::Actions::ACT_RECOVER);
				}
				else
				{
					//攻撃対象はmCursorPos
					act = new Action(status.ID, _enemies[mCursorPos]->status.ID, toAction[mMove]);
				}
				//行動が決まったからreturn true
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

void Player::draw(vector<Actor*> _enemies, vector<Actor*> _players) const
{
	//DrawRotaGraph(_x, _y, 1.0, 0.0, mImg, true);

	//行動決定部分の描画
	//攻撃対象決定画面でも描画される
	DrawBox(270, 180, 380, 330, MyData::BLACK, true);

	DrawFormatString(290, 200, MyData::WHITE, "こうげき");
	DrawFormatString(290, 230, MyData::WHITE, "まほう");
	DrawFormatString(290, 260, MyData::WHITE, "かいふく");
	DrawFormatString(290, 290, MyData::WHITE, "にげる");
	DrawCircle(280, 205 + mMove * 30, 5, MyData::WHITE);

	//攻撃対象決定画面
	if (mState == SELECT_TARGET)
	{
		DrawBox(390, 180, 540, 330, MyData::BLACK, true);
		DrawCircle(400, 205 + 30 * mCursorPos, 5, MyData::WHITE);

		int i = 0;

		//回復なら
		if (toAction[mMove] == Action::Actions::ACT_RECOVER)
		{
			for (auto &player : _players)
			{
				DrawFormatString(410, 195 + 30 * i, MyData::GREEN, "%s", player->status.name.c_str());
				i++;
			}
		}
		else
		{
			//敵なら
			for (auto &enemy : _enemies)
			{
				DrawFormatString(410, 200 + 30 * i, MyData::RED, "%s", enemy->status.name.c_str());
				i++;
			}

			//カーソル描画
			DrawRotaGraph(_enemies[mCursorPos]->getDrawX(), 20 + (mTime / 5 % 5), 1.0, 0.0, mPointerImg[mTime / 3 % 4], true);

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
