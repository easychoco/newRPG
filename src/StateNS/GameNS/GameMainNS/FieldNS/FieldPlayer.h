#pragma once

#include "..\..\..\..\Data.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace FieldNS{

class Main;

class Player
{
public:
	Player(Vector2);
	~Player();
	void initialize(Vector2);
	void update(const FieldNS::Main*);
	void draw() const;
	const Vector2* getVector2() const { return point; }
	bool isEncount() const { return mIsEncount; };

private:
	//�����N���X�C�p�[�e�B�����o�[�̏���
	class PartyMember
	{
	public:
		PartyMember(string fileName, Vector2);
		~PartyMember();
		void update(const FieldNS::Main*, const Player*, const unsigned char);
		void draw(int py) const;
		PartyMember* next;
	private:
		void initialize(string, Vector2);

		int mGraphNum;
		int mImg[12];
		int mTime;

		Vector2* point;
		queue<unsigned char> inputLog;

		void move(const FieldNS::Main* _main, const Player*, unsigned char);
	};

	//�p�[�e�B�����o�[�ւ̃|�C���^
	PartyMember* next;

	//�p�[�e�B�����o�[���������������ǂ���
	bool partyInitialized;
	
	//���W�x�N�g��
	Vector2* point;

	//�G�ɃG���J�E���g�������ǂ���
	bool mIsEncount;

	//�����ł�1000�{�����l��ێ�����
	const int pointRate = MyData::vectorRate;

	//���������߂�bitmask�Ŏg�p����
	const unsigned char f_right = 0b0001;
	const unsigned char f_left  = 0b0010;
	const unsigned char f_down  = 0b0100;
	const unsigned char f_up    = 0b1000;

	//�L�[���͂̃��O�C���Ԃ𓮂����̂Ɏg��
	queue<unsigned char> inputLog;

	//�摜�̔ԍ�
	int mGraphNum;

	//�摜
	int mImg[24];

	int mTime;

	float mSpeed;

	//==================
	// ����private�֐�
	//==================
	//�p�[�e�B�����o�[��������
	void initializeParty(const array<int, 4>);

	//toCharacter.fileName����摜�̖��O�𐶐�
	const string getFileName(char*) const;

	//�ړ�
	bool move(const FieldNS::Main*);

	//�G���J�E���g
	void encount();

};




}
}
}
}