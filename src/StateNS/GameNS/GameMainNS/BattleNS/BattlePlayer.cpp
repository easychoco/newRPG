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
	//���̊֐��͊e�^�[���̏��߂ɂ��Ă΂��
	//act�̓^�[�����ƂɐV�������邩��,�ȑO�̂��̂�delete
	SAFE_DELETE(act);

	mState = SELECT_MOVE;
	mMove = mCursorPos = 0;
	mPrePush = true;
	mFirstCome = true;
}

bool Player::attack(StringController* _sController, const vector<Actor*>& _enemies, const vector<Actor*>& _players)
{
	//���߂ė����Ƃ��̏���
	if (mFirstCome)
	{
		string s_tmp = status.name;
		s_tmp += "�͂ǂ�����H";
		_sController->addMessage(s_tmp);
		mFirstCome = false;
	}

	//�O�̃t���[���ŃL�[��������Ă��Ȃ����
	if (!mPrePush) {

		//�J�[�\���ړ�
		if (Input_UP())mCursorPos--;
		if (Input_DOWN())mCursorPos++;

		int max_num = (mState == SELECT_MOVE) ? 4 : 
			(toAction[mMove] == Action::Actions::ACT_RECOVER) ? (int)_players.size() : 
			(int)_enemies.size();

		//�J�[�\�����͈͂���͂ݏo���Ȃ��悤�ɒ���
		mCursorPos = (mCursorPos + max_num) % max_num;

		//�s��������
		if (mState == SELECT_MOVE)mMove = mCursorPos;

		//����{�^��
		if (Input_Z())
		{
			//�s�������ʂȂ�Ώی����
			if (mState == SELECT_MOVE)
			{
				//������Ȃ瑁��return
				if (toAction[mMove] == Action::Actions::ACT_ESCAPE)
				{
					act = new Action(status.ID, status.ID, Action::Actions::ACT_ESCAPE);
					return true;
				}

				//�����Ȃ��Ȃ�
				mCursorPos = 0;
				mState = SELECT_TARGET;
			}

			//�Ώی����ʂȂ玟��
			else if (mState == SELECT_TARGET)
			{
				if (toAction[mMove] == Action::Actions::ACT_RECOVER)
				{
					//�񕜑Ώۂ�mCursorPos
					act = new Action(status.ID, _players[mCursorPos]->status.ID, Action::Actions::ACT_RECOVER);
				}
				else
				{
					//�U���Ώۂ�mCursorPos
					act = new Action(status.ID, _enemies[mCursorPos]->status.ID, toAction[mMove]);
				}
				//�s�������܂�������return true
				return true;
			}
		}

		//X�Ŗ߂�
		if (Input_X())
		{
			mState = SELECT_MOVE;
			mCursorPos = 0;
		}
	}

	//prepush���X�V
	mPrePush = (Input_UP() | Input_DOWN() | Input_Z());
	return false;
}

void Player::draw(vector<Actor*> _enemies, vector<Actor*> _players) const
{
	//DrawRotaGraph(_x, _y, 1.0, 0.0, mImg, true);

	//�s�����蕔���̕`��
	//�U���Ώی����ʂł��`�悳���
	DrawBox(210, 180, 320, 330, MyData::BLACK, true);

	DrawFormatString(230, 200, MyData::WHITE, "��������");
	DrawFormatString(230, 230, MyData::WHITE, "�܂ق�");
	DrawFormatString(230, 260, MyData::WHITE, "�����ӂ�");
	DrawFormatString(230, 290, MyData::WHITE, "�ɂ���");
	DrawCircle(220, 205 + mMove * 30, 5, MyData::WHITE);

	//�U���Ώی�����
	if (mState == SELECT_TARGET)
	{
		DrawBox(330, 180, 420, 330, MyData::BLACK, true);
		DrawCircle(340, 205 + 30 * mCursorPos, 5, MyData::WHITE);

		int i = 0;

		//�񕜂Ȃ�
		if (toAction[mMove] == Action::Actions::ACT_RECOVER)
		{
			for (auto &player : _players)
			{
				DrawFormatString(350, 195 + 30 * i, MyData::GREEN, "%s", player->status.name.c_str());
				i++;
			}
		}
		else
		{
			for (auto &enemy : _enemies)
			{
				DrawFormatString(350, 200 + 30 * i, MyData::RED, "%s", enemy->status.name.c_str());
				i++;
			}
		}
	}

}


//========================================================================
// ����private�֐�
//========================================================================






}
}
}
}
