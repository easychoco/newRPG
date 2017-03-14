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
	assert(tmp == 0 && "player.png�ǂݍ��݃G���[!");

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
// ����private�֐�
//====================================
void Player::move()
{
	move(1.0f);
}

void Player::move(float _speed)
{
	//bitmask�p�̃t���O
	unsigned char fDirection = 0b0000;

	//KeyInput
	//�E
	if (Input_RIGHT())
	{
		fDirection |= f_right;
		//point->x += (int)(_speed * pointRate);
	}
	//��
	if (Input_LEFT())
	{
		//�E�L�[��������Ă����牟����Ă��Ȃ����Ƃɂ���
		if (fDirection & f_right)fDirection ^= f_right;
		else fDirection |= f_left;
		//point->x -= (int)(_speed * pointRate);
	}
	//��
	if (Input_DOWN())
	{
		fDirection |= f_down;
		//point->y += (int)(_speed * pointRate);
	}
	//��
	if (Input_UP()) 
	{
		//���L�[��������Ă����牟����Ă��Ȃ����Ƃɂ���
		if (fDirection & f_down)fDirection ^= f_down;
		else fDirection |= f_up;
		//point->y -= (int)(_speed * pointRate);
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
			point->x -= (int)(_speed * pointRate);

			//�摜�̔ԍ��w��
			mGraphNum = 3 + (mTime / 10) % 3;
		}
		//�E��
		else if (fDirection & f_right)
		{
			_speed *= 0.7071f;
			point->x += (int)(_speed * pointRate);
			mGraphNum = 15 + (mTime / 10) % 3;
		}
		//�^��
		else mGraphNum = (mTime / 10) % 3;

		//�^���Ɉړ�
		point->y += (int)(_speed * pointRate);
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
			point->x -= (int)(_speed * pointRate);
			//�摜�ԍ����w��
			mGraphNum = 9 + (mTime / 10) % 3;
		}
		//�E��
		else if (fDirection & f_right)
		{
			_speed *= 0.7071f;
			point->x += (int)(_speed * pointRate);
			mGraphNum = 21 + (mTime / 10) % 3;
		}
		//�^��
		else mGraphNum = 18 + (mTime / 10) % 3;

		//�^��Ɉړ�
		point->y -= (int)(_speed * pointRate);
	}

	//�^�E
	else if (fDirection & f_right)
	{
		point->x += (int)(_speed * pointRate);
		mGraphNum = 12 + (mTime / 10) % 3;
	}

	//�^��
	else if (fDirection & f_left)
	{
		point->x -= (int)(_speed * pointRate);
		mGraphNum = 6 + (mTime / 10) % 3;
	}



	//��ʊO�ɂ͂ݏo�����炾�߂�
	point->x = max(point->x, 0);
	point->x = min(point->x, (640 * pointRate)); //640�͉�ʂ̕�
	point->y = max(point->y, 0);
	point->y = min(point->y, (480 * pointRate)); //480�͉�ʂ̍���
}




}
}
}
}
