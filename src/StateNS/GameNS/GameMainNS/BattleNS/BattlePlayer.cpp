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
	//�O�̃t���[���ŃL�[��������Ă��Ȃ����
	if (!mPrePush) {

		//�J�[�\���ړ�
		if (Input_UP())mCursorPos--;
		if (Input_DOWN())mCursorPos++;

		mCursorPos = max(mCursorPos, 0);
		mCursorPos = min(mCursorPos, 3);

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
				act = new Action(status.ID, mCursorPos, toAction[mMove]);
				return true;
			}
		}

		//X�Ŗ߂�
		if (Input_X())
			mState = SELECT_MOVE;
	}

	//prepush���X�V
	mPrePush = (Input_UP() | Input_DOWN() | Input_Z());

	return false;
}


void Player::draw(int _x, int _y) const
{
	DrawRotaGraph(_x, _y, 1.0, 0.0, mImg, true);

	//�s�����蕔���̕`��
	//�U���Ώی����ʂł��`�悳���
	DrawBox(150, 180, 300, 330, MyData::BLACK, true);

	DrawFormatString(200, 200, MyData::WHITE, "��������");
	DrawFormatString(200, 230, MyData::WHITE, "�܂ق�");
	DrawFormatString(200, 260, MyData::WHITE, "�Ƃ�����");
	DrawFormatString(200, 290, MyData::WHITE, "�ɂ���");//TODO -> "������"�̎���
	DrawCircle(190, 205 + mMove * 30, 5, MyData::WHITE);

	//�U���Ώی�����
	if (mState == SELECT_TARGET)
	{
		DrawBox(310, 180, 400, 330, MyData::BLACK, true);
		DrawFormatString(330, 200, MyData::WHITE, "�Ă� %d", mCursorPos);
	}

}


//========================================================================
// ����private�֐�
//========================================================================






}
}
}
}
