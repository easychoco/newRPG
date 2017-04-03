#include "FieldStage.h"

#include "..\..\..\..\Data.h"
#include "..\..\..\..\KeyInput.h"

#include <fstream>


namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace FieldNS{


Stage::Stage()
{
	initialize();
}

Stage::~Stage()
{

}

void Stage::initialize()
{
	//画像読み込み
	mBackImg = LoadGraph("Data/Image/FieldBack.png");
	int tmp = LoadDivGraph("Data/Image/MapChip.png", 112, 16, 7, 32, 32, mapChip);

	assert(mBackImg != 0 && "FieldStage画像読み込みエラー");
	assert(tmp == 0 && "マップ画像読み込みエラー");


	//マップデータ読み込み
	std::ifstream fin("Data/Text/stage.txt");
	for (unsigned y = 0; y < mapData.size(); y++)
	{
		for (unsigned x = 0; x < mapData[0].size(); x++)
		{
			fin >> mapData[y][x];
		}
	}

	fin.close();
}

void Stage::update()
{
	//ここにアニメーション
}

void Stage::draw(const Vector2* _player) const
{
	drawBack(_player);
	drawMap(mapData, _player);
}

bool Stage::canPass(int _px, int _py) const
{
	return chip[mapData[_py / MyData::vectorRate / 32][_px / MyData::vectorRate / 32]].canPass;
}

int Stage::getEnemyLevel(const Vector2* _player) const
{
	return chip[mapData[_player->y / MyData::vectorRate / 32][_player->x / MyData::vectorRate / 32]].enemyLevel;
}

//========================================================================
// 内部private関数
//========================================================================
void Stage::drawBack(const Vector2* _player) const
{
	//画像の描画位置
	//DrawGraph関数を使うから，画像の左上に合わせる
	int draw_x = (_player->x < 640 * MyData::vectorRate) ? 0 : -640;

	//自機が真ん中にいるとき
	int draw_y = 240 - _player->y / MyData::vectorRate;

	//下端
	if (_player->y / MyData::vectorRate > MyData::MAP_HEIGHT - MyData::CY)draw_y = -480;

	//上端
	else if (_player->y / MyData::vectorRate < MyData::CY)draw_y = 0;


	DrawGraph(draw_x, draw_y, mBackImg, true);
}

//マップチップが変わっても対応可能
//第一引数にマップチップへのポインタを持ってくるためにtemplateを使用
template<typename Arr>
void Stage::drawMap(Arr _mapData, const Vector2* _player) const
{
	//マップ描画をする際に，自機の位置依存で描画位置のy座標が変わる
	//自機が真ん中にいるとき
	int draw_y = _player->y / MyData::vectorRate - MyData::CY;

	//下端
	if (_player->y / MyData::vectorRate > MyData::MAP_HEIGHT - MyData::CY)draw_y = MyData::MAP_HEIGHT - 480;

	//上端
	else if (_player->y / MyData::vectorRate < MyData::CY)draw_y = 0;


	//右側と左側のマップにいるときでfor文内部変数のxの範囲が変わる
	int x_sub = (_player->x / MyData::vectorRate < MyData::MAP_WIDTH / 2) ? 0 : mapData[0].size() / 2;

	for (unsigned y = 0; y < mapData.size(); y++)
	{
		for (unsigned x = x_sub; x < x_sub + mapData[0].size() / 2; x++)
		{
			DrawGraph((x % (mapData[0].size() / 2)) * 32, y * 32 - draw_y, mapChip[_mapData[y][x]], true);
		}
	}
}





}
}
}
}
