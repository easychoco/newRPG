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
	//�摜�ǂݍ���
	mBackImg = LoadGraph("Data/Image/FieldBack.png");
	int tmp = LoadDivGraph("Data/Image/MapChip.png", 112, 16, 7, 32, 32, mapChip);

	assert(mBackImg != 0 && "FieldStage�摜�ǂݍ��݃G���[");
	assert(tmp == 0 && "�}�b�v�摜�ǂݍ��݃G���[");


	//�}�b�v�f�[�^�ǂݍ���
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
	//�����ɃA�j���[�V����
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
// ����private�֐�
//========================================================================
void Stage::drawBack(const Vector2* _player) const
{
	//�摜�̕`��ʒu
	//DrawGraph�֐����g������C�摜�̍���ɍ��킹��
	int draw_x = (_player->x < 640 * MyData::vectorRate) ? 0 : -640;

	//���@���^�񒆂ɂ���Ƃ�
	int draw_y = 240 - _player->y / MyData::vectorRate;

	//���[
	if (_player->y / MyData::vectorRate > MyData::MAP_HEIGHT - MyData::CY)draw_y = -480;

	//��[
	else if (_player->y / MyData::vectorRate < MyData::CY)draw_y = 0;


	DrawGraph(draw_x, draw_y, mBackImg, true);
}

//�}�b�v�`�b�v���ς���Ă��Ή��\
//�������Ƀ}�b�v�`�b�v�ւ̃|�C���^�������Ă��邽�߂�template���g�p
template<typename Arr>
void Stage::drawMap(Arr _mapData, const Vector2* _player) const
{
	//�}�b�v�`�������ۂɁC���@�̈ʒu�ˑ��ŕ`��ʒu��y���W���ς��
	//���@���^�񒆂ɂ���Ƃ�
	int draw_y = _player->y / MyData::vectorRate - MyData::CY;

	//���[
	if (_player->y / MyData::vectorRate > MyData::MAP_HEIGHT - MyData::CY)draw_y = MyData::MAP_HEIGHT - 480;

	//��[
	else if (_player->y / MyData::vectorRate < MyData::CY)draw_y = 0;


	//�E���ƍ����̃}�b�v�ɂ���Ƃ���for�������ϐ���x�͈̔͂��ς��
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
