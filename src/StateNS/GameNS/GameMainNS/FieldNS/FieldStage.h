#pragma once

#include "..\..\..\..\Data.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace FieldNS {


class Stage
{
public:
	Stage();
	~Stage();
	void initialize();
	void update();
	void draw(const Vector2* _player) const;
	bool canPass(int px, int py);
private:
	int mBackImg;

	//mapChip(32x32pixcels)
	int mapChip[112];

	//map(40x30chips)
	std::array< std::array<int, 40>, 30> mapData;

	//�}�b�v�`��
	//�w�i�`��
	void drawBack(const Vector2*) const;

	//�O�i�`��
	template<typename Arr>
	void drawMap(Arr, const Vector2*) const;

	class Chip
	{
	public:
		Chip(bool _canPass, int _enemyLevel) : canPass(_canPass), enemyLevel(_enemyLevel) {};
		~Chip() {};
		const bool canPass;//�ʂ邱�Ƃ��ł��邩
		const int enemyLevel;//�o������G�̃��x��
	};

	const Chip chip[112] = 
	{
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip( true, 0),//���̊K�i
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip( true, 0),//���̊K�i
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip( true, 5),//���̒n��
		Chip(false, 0),
		Chip( true, 0),//���̊K�i
		Chip(false, 0),
		Chip( true, 3),//�����̒n��
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip( true, 4),//�y�̒n��
		Chip(false, 0),
		Chip(false, 0),
		Chip( true, 5),//���̒n��
		Chip(false, 0),
		Chip( true, 0),//���̊K�i
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip( true, 0),//��
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip( true, 2),//�X�̒n��
		Chip( true, 2),//�X�̒n��
		Chip( true, 2),//�X�̒n��
		Chip( true, 2),//�X�̒n��
		Chip( true, 2),//�X�̒n��
		Chip( true, 2),//�X�̒n��
		Chip( true, 4),//�y�̒n��
		Chip( true, 4),//�y�̒n��
		Chip( true, 4),//�y�̒n��
		Chip( true, 5),//���̒n��
		Chip( true, 5),//���̒n��
		Chip( true, 5),//���̒n��
		Chip( true, 0),//��
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(true , 1),//�����̒n��
		Chip(true , 1),//�����̒n��
		Chip(true , 1),//�����̒n��
		Chip( true, 0),//��
		Chip( true, 0),//��
		Chip( true, 0),//��
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip( true, 0),//��
	};



};




}
}
}
}