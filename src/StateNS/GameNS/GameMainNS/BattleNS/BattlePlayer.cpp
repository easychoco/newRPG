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

bool Player::attack(StringController* _sController, const vector<Actor*>& _enemies)
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


		int max_num = ((mState == SELECT_MOVE) ? 3 : (int)_enemies.size() - 1);
		mCursorPos = max(mCursorPos, 0);
		mCursorPos = min(mCursorPos, max_num);

		//�s��������
		if (mState == SELECT_MOVE)mMove = mCursorPos;

		//����{�^��
		if (Input_Z())
		{
			//�s�������ʂȂ�Ώی����
			if (mState == SELECT_MOVE)
			{
				mCursorPos = 0;
				mState = SELECT_TARGET;
			}

			//�Ώی����ʂȂ玟��
			else if (mState == SELECT_TARGET)
			{
				//�U���Ώۂ�mCursorPos
				act = new Action(status.ID, _enemies[mCursorPos]->status.ID, toAction[mMove]);
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


void Player::draw(vector<Actor*> _enemies) const
{
	//DrawRotaGraph(_x, _y, 1.0, 0.0, mImg, true);

	//�s�����蕔���̕`��
	//�U���Ώی����ʂł��`�悳���
	DrawBox(210, 180, 320, 330, MyData::BLACK, true);

	DrawFormatString(230, 200, MyData::WHITE, "��������");
	DrawFormatString(230, 230, MyData::WHITE, "�܂ق�");
	DrawFormatString(230, 260, MyData::WHITE, "�Ƃ�����");
	DrawFormatString(230, 290, MyData::WHITE, "�ɂ���");//TODO -> "������"�̎���
	DrawCircle(220, 205 + mMove * 30, 5, MyData::WHITE);

	//�U���Ώی�����
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
// ����private�֐�
//========================================================================






}
}
}
}
