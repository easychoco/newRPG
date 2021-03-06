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
	bool canPass(int _px, int _py) const;
	int getEnemyLevel(const Vector2*) const;

private:
	int mBackImg;

	//mapChip(32x32pixcels)
	int mapChip[112];

	//map(40x30chips)
	std::array< std::array<int, 40>, 30> mapData;

	//マップ描画
	//背景描画
	void drawBack(const Vector2*) const;

	//前景描画
	template<typename Arr>
	void drawMap(Arr, const Vector2*) const;

	class Chip
	{
	public:
		Chip(bool _canPass, int _enemyLevel) : canPass(_canPass), enemyLevel(_enemyLevel) {};
		~Chip() {};
		const bool canPass;//通ることができるか
		const int enemyLevel;//出現する敵のレベル
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
		Chip( true, 0),//塔の階段
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
		Chip( true, 0),//塔の階段
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
		Chip( true, 5),//塔の地面
		Chip(false, 0),
		Chip( true, 0),//塔の階段
		Chip(false, 0),
		Chip( true, 3),//砂漠の地面
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip( true, 4),//土の地面
		Chip(false, 0),
		Chip(false, 0),
		Chip( true, 5),//塔の地面
		Chip(false, 0),
		Chip( true, 0),//塔の階段
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
		Chip( true, 0),//橋
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip( true, 2),//森の地面
		Chip( true, 2),//森の地面
		Chip( true, 2),//森の地面
		Chip( true, 2),//森の地面
		Chip( true, 2),//森の地面
		Chip( true, 2),//森の地面
		Chip( true, 4),//土の地面
		Chip( true, 4),//土の地面
		Chip( true, 4),//土の地面
		Chip( true, 5),//塔の地面
		Chip( true, 5),//塔の地面
		Chip( true, 5),//塔の地面
		Chip( true, 0),//橋
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(true , 1),//草原の地面
		Chip(true , 1),//草原の地面
		Chip(true , 1),//草原の地面
		Chip( true, 0),//橋
		Chip( true, 0),//橋
		Chip( true, 0),//橋
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip( true, 0),//橋
	};



};




}
}
}
}