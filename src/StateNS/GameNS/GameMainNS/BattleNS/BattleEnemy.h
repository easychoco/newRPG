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
		Status{ 4, "Data/Image/enemy/2_5.png", "�Ԃ���", 20, 40, 20, 0, 20, 20 },
	};

	const std::array< Status, 5> e_spec3
	{
		Status{ 0, "Data/Image/enemy/", "", 20, 20, 20, 20, 20, 20 },
		Status{ 1, "Data/Image/enemy/", "", 20, 20, 20, 20, 20, 20 },
		Status{ 2, "Data/Image/enemy/", "", 20, 20, 20, 20, 20, 20 },
		Status{ 3, "Data/Image/enemy/", "", 20, 20, 20, 20, 20, 20 },
		Status{ 4, "Data/Image/enemy/", "", 20, 20, 20, 20, 20, 20 },
	};

	const std::array< Status, 5> e_spec4
	{
		Status{ 0, "Data/Image/enemy/", "", 20, 20, 20, 20, 20, 20 },
		Status{ 1, "Data/Image/enemy/", "", 20, 20, 20, 20, 20, 20 },
		Status{ 2, "Data/Image/enemy/", "", 20, 20, 20, 20, 20, 20 },
		Status{ 3, "Data/Image/enemy/", "", 20, 20, 20, 20, 20, 20 },
		Status{ 4, "Data/Image/enemy/", "", 20, 20, 20, 20, 20, 20 },
	};

	const std::array< Status, 5> e_spec5
	{
		Status{ 0, "Data/Image/enemy/", "", 20, 20, 20, 20, 20, 20 },
		Status{ 1, "Data/Image/enemy/", "", 20, 20, 20, 20, 20, 20 },
		Status{ 2, "Data/Image/enemy/", "", 20, 20, 20, 20, 20, 20 },
		Status{ 3, "Data/Image/enemy/", "", 20, 20, 20, 20, 20, 20 },
		Status{ 4, "Data/Image/enemy/", "", 20, 20, 20, 20, 20, 20 },
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