#include "FieldPlayer.h"
#include "FieldMain.h"
#include "..\CharacterData.h"

#include "..\..\..\..\KeyInput.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace FieldNS {


Player::Player(Vector2 _point)
{
	initialize(_point);
}

Player::~Player()
{
	SAFE_DELETE(point);
	while(!inputLog.empty())inputLog.pop();
	SAFE_DELETE(next);
	for(int i = 0; i < 24; i++)DeleteGraph(mImg[i]);
}

void Player::initialize(Vector2 _point)
{
	point =  (_point.x == 0) ? new Vector2{ 96000, 800000 } : new Vector2{ _point.x, _point.y };

	int tmp = LoadDivGraph(getFileName(toCharacter[0].fileName).c_str(), 24, 6, 4, 32, 32, mImg);
	assert(tmp == 0 && "move_player.png�ǂݍ��݃G���[!");

	mTime = 0;
	mIsEncount = false;
	mGraphNum = 0;
	mSpeed = 6.0f;

	next = NULL;
	partyInitialized = false;

}

void Player::update(const FieldNS::Main* _main)
{
	if (!partyInitialized)
	{
		initializeParty(_main->getParty());
		partyInitialized = true;

	}

	mIsEncount = false;

	mTime++;
	bool moved = move(_main);

	if (moved)
	{
		//�G���J�E���g����
		encount();

		//���t���[���x��čs��
		if (inputLog.size() > (unsigned)(32 / this->mSpeed))
		{
			//�p�[�e�B�����o�[���X�V
			next->update(_main, this, inputLog.front());
			inputLog.pop();
		}
	}
}

void Player::draw() const
{

	//���@�`��

	//���@��`�悷��x���W���w��
	int draw_x = (point->x / pointRate) % (MyData::MAP_WIDTH / 2 + 1);

	//�p�[�e�B�����o�[�`��
	if (next)next->draw(draw_x, point->y);


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
//�p�[�e�B�����o�[��������
void Player::initializeParty(const array<int, 4> _party)
{
	while (!inputLog.empty())inputLog.pop();
	SAFE_DELETE(next);
	next = new PartyMember(getFileName(toCharacter[_party[1]].fileName), *(this->point));
	next->next = new PartyMember(getFileName(toCharacter[_party[2]].fileName), *(this->point));
	next->next->next = new PartyMember(getFileName(toCharacter[_party[3]].fileName), *(this->point));
}

//toCharacter.fileName����摜�̖��O�𐶐�
const string Player::getFileName(char* _fileName) const
{
	string fileName = "Data/Image/move_";
	fileName += _fileName;
	fileName += ".png";

	return fileName;
}

//�ړ�
bool Player::move(const FieldNS::Main* _main)
{
	//bitmask�p�̃t���O
	unsigned char fDirection = 0b0000;

	//�ړ����x
	float speed = mSpeed;

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

	//�L�[���͂��Ȃ��Ȃ�return false
	if (!fDirection)
	{
		//�L�[��������Ă��Ȃ�������_�����̊G�ɂ���
		//�_�����̃L�����N�^�`�b�v�̔ԍ���1,4,7,10,...���
		if (mGraphNum % 3 != 1)mGraphNum = mGraphNum / 3 * 3 + 1;
		return false;
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
			speed *= 0.7071f;

			//���Ɉړ�
			dx = -(int)(speed * pointRate);

			//�摜�̔ԍ��w��
			mGraphNum = 3 + (mTime / 10) % 3;
		}
		//�E��
		else if (fDirection & f_right)
		{
			speed *= 0.7071f;
			dx = (int)(speed * pointRate);
			mGraphNum = 15 + (mTime / 10) % 3;
		}
		//�^��
		else mGraphNum = (mTime / 10) % 3;

		//�^���Ɉړ�
		dy = (int)(speed * pointRate);
	}

	//������ւ̈ړ�
	else if (fDirection & f_up)
	{
		//����
		if (fDirection & f_left)
		{
			//�΂߈ړ��̓X�s�[�h�_�E��
			//1/��2 = 0.70710678...
			speed *= 0.7071f;

			//���Ɉړ�
			dx = -(int)(speed * pointRate);
			//�摜�ԍ����w��
			mGraphNum = 9 + (mTime / 10) % 3;
		}
		//�E��
		else if (fDirection & f_right)
		{
			speed *= 0.7071f;
			dx = (int)(speed * pointRate);
			mGraphNum = 21 + (mTime / 10) % 3;
		}
		//�^��
		else mGraphNum = 18 + (mTime / 10) % 3;

		//�^��Ɉړ�
		dy = -(int)(speed * pointRate);
	}

	//�^�E
	else if (fDirection & f_right)
	{
		dx = (int)(speed * pointRate);
		mGraphNum = 12 + (mTime / 10) % 3;
	}

	//�^��
	else if (fDirection & f_left)
	{
		dx = -(int)(speed * pointRate);
		mGraphNum = 6 + (mTime / 10) % 3;
	}

	//�ʂ��Ȃ�ړ�
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

	//�ړ��̃��O��ۑ�
	inputLog.push(fDirection);

	//�ړ����Ă���̂�return true
	return true;
}

void Player::encount()
{
	static int encountTimer = 0;

	//���̊֐����Ă΂�邽�тɗ����ˑ��ŃJ�E���^�[�𑝂₷
	encountTimer += GetRand(1);

	//�^�C�}�[��60�𒴂�����G�ɃG���J�E���g
	if (encountTimer > 60)
	{
		mIsEncount = true;
		encountTimer = 0;
	}
}











//============================================================================================
// �����N���X(PartyMember)
//============================================================================================
Player::PartyMember::PartyMember(string _fileName, Vector2 _point)
{
	this->initialize(_fileName, _point);
}

Player::PartyMember::~PartyMember()
{
	SAFE_DELETE(point)
	while (!this->inputLog.empty())this->inputLog.pop();
	if(this->next)SAFE_DELETE(this->next);
	for (int i = 0; i < 12; i++)DeleteGraph(mImg[i]);

}

void Player::PartyMember::initialize(string _fileName, Vector2 _point)
{
	int tmp = LoadDivGraph(_fileName.c_str(), 12, 3, 4, 32, 32, this->mImg);
	assert(tmp == 0 && "�p�[�e�B�摜�ǂݍ��݃G���[!");

	this->next = NULL;
	this->point = new Vector2(_point);
	this->mGraphNum = 0;
	this->mTime = 0;
}

void Player::PartyMember::update(const FieldNS::Main* _main, const Player* _player, unsigned char _fDirection)
{
	this->mTime++;

	move(_main, _player, _fDirection);

	//���t���[���x��čs��
	if (this->inputLog.size() > (unsigned)(32 / _player->mSpeed))
	{
		//�p�[�e�B�����o�[���X�V
		if(next)next->update(_main, _player, this->inputLog.front());

		this->inputLog.pop();
	}

}

void Player::PartyMember::draw(int _px, int _py) const
{
	//���@�`��

	//���@��`�悷��x���W���w��
	int draw_x = (this->point->x / MyData::vectorRate) % (MyData::MAP_WIDTH / 2 + 1);

	//��ʈړ����ɕ`��ʒu�����������Ȃ�̂�h�~
	if (draw_x - _px > 400)draw_x = 0;
	if (_px - draw_x > 400)draw_x = 640;


	//���ɂ��Ă��郁���o�[��`��
	if (next)next->draw(_px, _py);

	//��[�ɂ���Ȃ�
	if (_py < MyData::CY * MyData::vectorRate)
		DrawRotaGraph(draw_x, this->point->y / MyData::vectorRate, 1.0, 0.0, this->mImg[mGraphNum], true);

	//���[�ɂ���Ȃ�
	else if (_py >(MyData::MAP_HEIGHT - MyData::CY) * MyData::vectorRate)
		DrawRotaGraph(draw_x, this->point->y / MyData::vectorRate - MyData::MAP_HEIGHT + 480, 1.0, 0.0, this->mImg[mGraphNum], true);

	//�ǂ���ł��Ȃ��Ȃ�
	else
	{
		int draw_y = MyData::CY + (this->point->y - _py) / MyData::vectorRate;
		DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImg[mGraphNum], true);
	}
}


//============================================================
//����private�֐�
//============================================================
void Player::PartyMember::move(const FieldNS::Main* _main, const Player* _player, const unsigned char _fDirection)
{
	//�ړ���
	int dx = 0;
	int dy = 0;

	//�ړ����x
	float speed = _player->mSpeed;

	//���͂ɍ��킹�Ĉړ��Ɖ摜�ύX
	if (_fDirection & _player->f_right)
	{
		//�E��
		if (_fDirection & _player->f_down)
		{
			//�΂߈ړ��̓X�s�[�h�_�E��
			//1/��2 = 0.70710678...
			speed *= 0.7071f;

			dy = (int)(speed * MyData::vectorRate);
		}
		//�E��
		else if (_fDirection & _player->f_up)
		{
			//�΂߈ړ��̓X�s�[�h�_�E��
			//1/��2 = 0.70710678...
			speed *= 0.7071f;

			dy = -(int)(speed * MyData::vectorRate);
		}

		//�E�Ɉړ�
		dx = (int)(speed * MyData::vectorRate);

		mGraphNum = 6 + mTime / 10 % 3;
	}
	else if (_fDirection & _player->f_left)
	{
		//����
		if (_fDirection & _player->f_down)
		{
			//�΂߈ړ��̓X�s�[�h�_�E��
			//1/��2 = 0.70710678...
			speed *= 0.7071f;

			dy = (int)(speed * MyData::vectorRate);
		}
		//����
		else if (_fDirection & _player->f_up)
		{
			//�΂߈ړ��̓X�s�[�h�_�E��
			//1/��2 = 0.70710678...
			speed *= 0.7071f;

			dy = -(int)(speed * MyData::vectorRate);
		}

		//���Ɉړ�
		dx = -(int)(speed * MyData::vectorRate);

		mGraphNum = 3 + mTime / 10 % 3;
	}
	//��
	else if (_fDirection & _player->f_down)
	{
		dy = (int)(speed * MyData::vectorRate);
		mGraphNum = 0 + mTime / 10 % 3;
	}
	//��
	else if (_fDirection & _player->f_up)
	{
		dy = -(int)(speed * MyData::vectorRate);
		mGraphNum = 9 + mTime / 10 % 3;
	}


	//�ʂ��Ȃ�ړ�
	if (_main->canPass(point->x + dx, point->y))
	{
		point->x += dx;
	}
	if (_main->canPass(point->x, point->y + dy))
	{
		point->y += dy;
	}

	//��ʊO�ɂ͂ݏo�����炾�߂�
	this->point->x = max(point->x, 0);
	this->point->x = min(point->x, (MyData::MAP_WIDTH * MyData::vectorRate) - 1);
	this->point->y = max(point->y, 0);
	this->point->y = min(point->y, (MyData::MAP_HEIGHT * MyData::vectorRate) - 1);


	//�ړ��̃��O��ۑ�
	inputLog.push(_fDirection);
}




}
}
}
}
