#pragma once

#include "BattleActor.h"
#include "..\..\..\..\Data.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace BattleNS {

class Enemy : public Actor
{
public:
	//status, exp
	Enemy(Status, int);
	~Enemy();
	void initialize();
	void setData(char* filename, int x, int y);
	bool attack(StringController*, const vector<Actor*>& _players, const vector<Actor*>&);
	void draw(vector<Actor*>, vector<Actor*>) const;
	int getDrawX() { return draw_x; }

private:
	int mImg;

	int draw_x;
	int draw_y;

};


//�G�̐��\
namespace EnemySpec
{
	//�G�̎푰�l
	struct Status
	{
		const int ID;
		char* filename;
		char* name;
		int h;
		int a;
		int b;
		int c;
		int d;
		int s;
	};

	const std::array< Status, 5> e_spec1
	{
		Status{ 0, "Data/Image/enemy/1_1.png", "�X���C��", 20, 20, 20, 20, 20, 20 },
		Status{ 1, "Data/Image/enemy/1_2.png", "�����X���C��", 20, 15, 25, 15, 25, 20 },
		Status{ 2, "Data/Image/enemy/1_3.png", "�ƂтƂ��", 20, 25, 20, 15, 10, 30 },
		Status{ 3, "Data/Image/enemy/1_4.png", "�t���ς̐�", 30, 10, 20, 10, 30, 20 },
		Status{ 4, "Data/Image/enemy/1_5.png", "�t�F�A���[", 20, 20, 10, 20, 30, 20 },
	};

	const std::array< Status, 5> e_spec2
	{
		Status{ 0, "Data/Image/enemy/2_1.png", "�A�N�A", 15, 5, 25, 30, 25, 20 },
		Status{ 1, "Data/Image/enemy/2_2.png", "�t���A", 20, 10, 15, 30, 15, 30 },
		Status{ 2, "Data/Image/enemy/2_3.png", "�o�[��", 30, 10, 20, 30, 20, 10 },
		Status{ 3, "Data/Image/enemy/2_4.png", "���񂫂�", 20, 40, 20, 0, 20, 20 },
		Status{ 4, "Data/Image/enemy/2_5.png", "�Ԃ���", 30, 30, 20, 0, 20, 20 },
	};

	const std::array< Status, 5> e_spec3
	{
		Status{ 0, "Data/Image/enemy/3_1.png", "�K���K��", 20, 20, 20, 20, 20, 20 },
		Status{ 1, "Data/Image/enemy/3_2.png", "�R����p�s���X", 20, 40, 0, 20, 0, 40 },
		Status{ 2, "Data/Image/enemy/3_3.png", "�~�C��", 30, 20, 25, 15, 25, 5 },
		Status{ 3, "Data/Image/enemy/3_4.png", "�A�k�r��", 20, 15, 30, 5, 30, 20 },
		Status{ 4, "Data/Image/enemy/3_5.png", "�U���g", 10, 5, 30, 20, 30, 25 },
	};

	const std::array< Status, 5> e_spec4
	{
		Status{ 0, "Data/Image/enemy/4_1.png", "�N�����s", 20, 10, 15, 25, 25, 25 },
		Status{ 1, "Data/Image/enemy/4_2.png", "�E�B�b�`", 15, 10, 10, 40, 20, 25 },
		Status{ 2, "Data/Image/enemy/4_3.png", "�d����m", 10, 30, 10, 20, 10, 40 },
		Status{ 3, "Data/Image/enemy/4_4.png", "���R�m", 23, 23, 23, 23, 23, 23 },
		Status{ 4, "Data/Image/enemy/4_5.png", "����", 20, 20, 20, 20, 20, 20 },
	};

	const std::array< Status, 5> e_spec5
	{
		Status{ 0, "Data/Image/enemy/5_1.png", "�e�̈ē��l", 30, 10, 30, 10, 30, 10 },
		Status{ 1, "Data/Image/enemy/5_2.png", "���g��", 25, 10, 10, 30, 30, 15 },
		Status{ 2, "Data/Image/enemy/5_3.png", "�h���S��", 40, 30, 10, 10, 10, 20 },
		Status{ 3, "Data/Image/enemy/5_4.png", "�b�R�m", 20, 40, 40, 5, 5, 10 },
		Status{ 4, "Data/Image/enemy/5_5.png", "�N���t�^�[", 25, 25, 25, 25, 25, 25 },
	};

	const std::array< std::array< Status, 5>, 5> toEneStatus
	{
		e_spec1,
		e_spec2,
		e_spec3,
		e_spec4,
		e_spec5,
	};

}

using EnemySpec::toEneStatus;













}
}
}
}