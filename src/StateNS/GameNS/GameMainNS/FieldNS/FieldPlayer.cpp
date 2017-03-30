#include "FieldPlayer.h"
#include "FieldMain.h"

#include "..\..\..\..\Data.h"
#include "..\..\..\..\KeyInput.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace FieldNS {


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
	point = new Vector2{ 96000, 800000 };
	
	int tmp = LoadDivGraph("Data/Image/player.png", 24, 6, 4, 32, 32, mImg);
	assert(tmp == 0 && "player.png�ǂݍ��݃G���[!");

	mTime = 0;
	mGraphNum = 0;
}

void Player::update(const FieldNS::Main* _main)
{
	mTime++;
	move(5.0f, _main);
}

void Player::draw() const
{
	//DrawFormatString(100, 20, MyData::WHITE, "Player");
	//DrawFormatString(180, 20, MyData::WHITE, "%d", mGraphNum);
	
	//���@�`��

	//���@��`�悷��x���W���w��
	int draw_x = (point->x / pointRate) % (MyData::MAP_WIDTH / 2 + 1);

	//��[�ɂ���Ȃ�
	if(point->y < MyData::CY * pointRate)
		DrawRotaGraph(draw_x, point->y / pointRate, 1.0, 0.0, mImg[mGraphNum], true);

	//���[�ɂ���Ȃ�
	else if (point->y > (MyData::MAP_HEIGHT - MyData::CY) * pointRate)
		DrawRotaGraph(draw_x, point->y / pointRate - MyData::MAP_HEIGHT + 480, 1.0, 0.0, mImg[mGraphNum], true);

	//�ǂ���ł��Ȃ��Ȃ�
	else
		DrawRotaGraph(draw_x, MyData::CY, 1.0, 0.0, mImg[mGraphNum], true);

}

//========================================================================
// ����private�֐�
//========================================================================
void Player::move(const FieldNS::Main* _main)
{
	move(1.0f, _main);
}

void Player::move(float _speed, const FieldNS::Main* _main)
{
	//bitmask�p�̃t���O
	unsigned char fDirection = 0b0000;

	//KeyInput
	//�E
	if (Input_RIGHT())
	{
		fDirection |= f_right;
	}
	//��
	if (Input_LEFT())
	{
		//�E�L�[��������Ă����牟����Ă��Ȃ����Ƃɂ���
		if (fDirection & f_right)fDirection ^= f_right;
		else fDirection |= f_left;
	}

	//��
	if (Input_DOWN())
	{
		fDirection |= f_down;
	}
	//��
	if (Input_UP()) 
	{
		//���L�[��������Ă����牟����Ă��Ȃ����Ƃɂ���
		if (fDirection & f_down)fDirection ^= f_down;
		else fDirection |= f_up;
	}

	//�L�[���͂��Ȃ��Ȃ�return
	if (!fDirection)
	{
		//�L�[��������Ă��Ȃ�������_�����̊G�ɂ���
		//�_�����̃L�����N�^�`�b�v�̔ԍ���1,4,7,10,...���
		if (mGraphNum % 3 != 1)mGraphNum = mGraphNum / 3 * 3 + 1;
		return;
	}


	//�ړ��Ɖ摜�ԍ��w��
	int dx = 0;
	int dy = 0;

	//�������ւ̈ړ�
	if (fDirection & f_down)
	{
		//����
		if (fDirection & f_left)
		{
			//�΂߈ړ��̓X�s�[�h�_�E��
			//1/��2 = 0.70710678...
			_speed *= 0.7071f;

			//���Ɉړ�
			dx = -(int)(_speed * pointRate);

			//�摜�̔ԍ��w��
			mGraphNum = 3 + (mTime / 10) % 3;
		}
		//�E��
		else if (fDirection & f_right)
		{
			_speed *= 0.7071f;
			dx = (int)(_speed * pointRate);
			mGraphNum = 15 + (mTime / 10) % 3;
		}
		//�^��
		else mGraphNum = (mTime / 10) % 3;

		//�^���Ɉړ�
		dy = (int)(_speed * pointRate);
	}

	//������ւ̈ړ�
	else if (fDirection & f_up)
	{
		//����
		if (fDirection & f_left)
		{
			//�΂߈ړ��̓X�s�[�h�_�E��
			//1/��2 = 0.70710678...
			_speed *= 0.7071f;

			//���Ɉړ�
			dx = -(int)(_speed * pointRate);
			//�摜�ԍ����w��
			mGraphNum = 9 + (mTime / 10) % 3;
		}
		//�E��
		else if (fDirection & f_right)
		{
			_speed *= 0.7071f;
			dx = (int)(_speed * pointRate);
			mGraphNum = 21 + (mTime / 10) % 3;
		}
		//�^��
		else mGraphNum = 18 + (mTime / 10) % 3;

		//�^��Ɉړ�
		dy = -(int)(_speed * pointRate);
	}

	//�^�E
	else if (fDirection & f_right)
	{
		dx = (int)(_speed * pointRate);
		mGraphNum = 12 + (mTime / 10) % 3;
	}

	//�^��
	else if (fDirection & f_left)
	{
		dx = -(int)(_speed * pointRate);
		mGraphNum = 6 + (mTime / 10) % 3;
	}

	if (_main->canPass(point->x + dx, point->y))
	{
		point->x += dx;
	}
	if (_main->canPass(point->x, point->y + dy))
	{
		point->y += dy;
	}


	//��ʊO�ɂ͂ݏo�����炾�߂�
	point->x = max(point->x, 0);
	point->x = min(point->x, (MyData::MAP_WIDTH * pointRate) - 1);
	point->y = max(point->y, 0);
	point->y = min(point->y, (MyData::MAP_HEIGHT * pointRate) - 1);
}




}
}
}
}
