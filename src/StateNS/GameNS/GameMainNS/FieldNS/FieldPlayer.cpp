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
	assert(tmp == 0 && "move_player.png読み込みエラー!");

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
		//エンカウント処理
		encount();

		//数フレーム遅れて行動
		if (inputLog.size() > (unsigned)(32 / this->mSpeed))
		{
			//パーティメンバーを更新
			next->update(_main, this, inputLog.front());
			inputLog.pop();
		}
	}
}

void Player::draw() const
{

	//自機描画

	//自機を描画するx座標を指定
	int draw_x = (point->x / pointRate) % (MyData::MAP_WIDTH / 2 + 1);

	//パーティメンバー描画
	if (next)next->draw(draw_x, point->y);


	//上端にいるなら
	if(point->y < MyData::CY * pointRate)
		DrawRotaGraph(draw_x, point->y / pointRate, 1.0, 0.0, mImg[mGraphNum], true);

	//下端にいるなら
	else if (point->y > (MyData::MAP_HEIGHT - MyData::CY) * pointRate)
		DrawRotaGraph(draw_x, point->y / pointRate - MyData::MAP_HEIGHT + 480, 1.0, 0.0, mImg[mGraphNum], true);

	//どちらでもないなら
	else
		DrawRotaGraph(draw_x, MyData::CY, 1.0, 0.0, mImg[mGraphNum], true);
}

//========================================================================
// 内部private関数
//========================================================================
//パーティメンバーを初期化
void Player::initializeParty(const array<int, 4> _party)
{
	while (!inputLog.empty())inputLog.pop();
	SAFE_DELETE(next);
	next = new PartyMember(getFileName(toCharacter[_party[1]].fileName), *(this->point));
	next->next = new PartyMember(getFileName(toCharacter[_party[2]].fileName), *(this->point));
	next->next->next = new PartyMember(getFileName(toCharacter[_party[3]].fileName), *(this->point));
}

//toCharacter.fileNameから画像の名前を生成
const string Player::getFileName(char* _fileName) const
{
	string fileName = "Data/Image/move_";
	fileName += _fileName;
	fileName += ".png";

	return fileName;
}

//移動
bool Player::move(const FieldNS::Main* _main)
{
	//bitmask用のフラグ
	unsigned char fDirection = 0b0000;

	//移動速度
	float speed = mSpeed;

	//KeyInput
	//右
	if (Input_RIGHT())
	{
		fDirection |= f_right;
	}
	//左
	if (Input_LEFT())
	{
		//右キーが押されていたら押されていないことにする
		if (fDirection & f_right)fDirection ^= f_right;
		else fDirection |= f_left;
	}

	//下
	if (Input_DOWN())
	{
		fDirection |= f_down;
	}
	//上
	if (Input_UP()) 
	{
		//下キーが押されていたら押されていないことにする
		if (fDirection & f_down)fDirection ^= f_down;
		else fDirection |= f_up;
	}

	//キー入力がないならreturn false
	if (!fDirection)
	{
		//キーが押されていなかったら棒立ちの絵にする
		//棒立ちのキャラクタチップの番号が1,4,7,10,...より
		if (mGraphNum % 3 != 1)mGraphNum = mGraphNum / 3 * 3 + 1;
		return false;
	}


	//移動と画像番号指定
	int dx = 0;
	int dy = 0;

	//下方向への移動
	if (fDirection & f_down)
	{
		//左下
		if (fDirection & f_left)
		{
			//斜め移動はスピードダウン
			//1/√2 = 0.70710678...
			speed *= 0.7071f;

			//左に移動
			dx = -(int)(speed * pointRate);

			//画像の番号指定
			mGraphNum = 3 + (mTime / 10) % 3;
		}
		//右下
		else if (fDirection & f_right)
		{
			speed *= 0.7071f;
			dx = (int)(speed * pointRate);
			mGraphNum = 15 + (mTime / 10) % 3;
		}
		//真下
		else mGraphNum = (mTime / 10) % 3;

		//真下に移動
		dy = (int)(speed * pointRate);
	}

	//上方向への移動
	else if (fDirection & f_up)
	{
		//左上
		if (fDirection & f_left)
		{
			//斜め移動はスピードダウン
			//1/√2 = 0.70710678...
			speed *= 0.7071f;

			//左に移動
			dx = -(int)(speed * pointRate);
			//画像番号を指定
			mGraphNum = 9 + (mTime / 10) % 3;
		}
		//右上
		else if (fDirection & f_right)
		{
			speed *= 0.7071f;
			dx = (int)(speed * pointRate);
			mGraphNum = 21 + (mTime / 10) % 3;
		}
		//真上
		else mGraphNum = 18 + (mTime / 10) % 3;

		//真上に移動
		dy = -(int)(speed * pointRate);
	}

	//真右
	else if (fDirection & f_right)
	{
		dx = (int)(speed * pointRate);
		mGraphNum = 12 + (mTime / 10) % 3;
	}

	//真左
	else if (fDirection & f_left)
	{
		dx = -(int)(speed * pointRate);
		mGraphNum = 6 + (mTime / 10) % 3;
	}

	//通れるなら移動
	if (_main->canPass(point->x + dx, point->y))
	{
		point->x += dx;
	}
	if (_main->canPass(point->x, point->y + dy))
	{
		point->y += dy;
	}


	//画面外にはみ出したらだめよ
	point->x = max(point->x, 0);
	point->x = min(point->x, (MyData::MAP_WIDTH * pointRate) - 1);
	point->y = max(point->y, 0);
	point->y = min(point->y, (MyData::MAP_HEIGHT * pointRate) - 1);

	//移動のログを保存
	inputLog.push(fDirection);

	//移動しているのでreturn true
	return true;
}

void Player::encount()
{
	static int encountTimer = 0;

	//この関数が呼ばれるたびに乱数依存でカウンターを増やす
	encountTimer += GetRand(1);

	//タイマーが60を超えたら敵にエンカウント
	if (encountTimer > 60)
	{
		mIsEncount = true;
		encountTimer = 0;
	}
}











//============================================================================================
// 内部クラス(PartyMember)
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
	assert(tmp == 0 && "パーティ画像読み込みエラー!");

	this->next = NULL;
	this->point = new Vector2(_point);
	this->mGraphNum = 0;
	this->mTime = 0;
}

void Player::PartyMember::update(const FieldNS::Main* _main, const Player* _player, unsigned char _fDirection)
{
	this->mTime++;

	move(_main, _player, _fDirection);

	//数フレーム遅れて行動
	if (this->inputLog.size() > (unsigned)(32 / _player->mSpeed))
	{
		//パーティメンバーを更新
		if(next)next->update(_main, _player, this->inputLog.front());

		this->inputLog.pop();
	}

}

void Player::PartyMember::draw(int _px, int _py) const
{
	//自機描画

	//自機を描画するx座標を指定
	int draw_x = (this->point->x / MyData::vectorRate) % (MyData::MAP_WIDTH / 2 + 1);

	//画面移動時に描画位置がおかしくなるのを防止
	if (draw_x - _px > 400)draw_x = 0;
	if (_px - draw_x > 400)draw_x = 640;


	//後ろについてくるメンバーを描画
	if (next)next->draw(_px, _py);

	//上端にいるなら
	if (_py < MyData::CY * MyData::vectorRate)
		DrawRotaGraph(draw_x, this->point->y / MyData::vectorRate, 1.0, 0.0, this->mImg[mGraphNum], true);

	//下端にいるなら
	else if (_py >(MyData::MAP_HEIGHT - MyData::CY) * MyData::vectorRate)
		DrawRotaGraph(draw_x, this->point->y / MyData::vectorRate - MyData::MAP_HEIGHT + 480, 1.0, 0.0, this->mImg[mGraphNum], true);

	//どちらでもないなら
	else
	{
		int draw_y = MyData::CY + (this->point->y - _py) / MyData::vectorRate;
		DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImg[mGraphNum], true);
	}
}


//============================================================
//内部private関数
//============================================================
void Player::PartyMember::move(const FieldNS::Main* _main, const Player* _player, const unsigned char _fDirection)
{
	//移動量
	int dx = 0;
	int dy = 0;

	//移動速度
	float speed = _player->mSpeed;

	//入力に合わせて移動と画像変更
	if (_fDirection & _player->f_right)
	{
		//右下
		if (_fDirection & _player->f_down)
		{
			//斜め移動はスピードダウン
			//1/√2 = 0.70710678...
			speed *= 0.7071f;

			dy = (int)(speed * MyData::vectorRate);
		}
		//右上
		else if (_fDirection & _player->f_up)
		{
			//斜め移動はスピードダウン
			//1/√2 = 0.70710678...
			speed *= 0.7071f;

			dy = -(int)(speed * MyData::vectorRate);
		}

		//右に移動
		dx = (int)(speed * MyData::vectorRate);

		mGraphNum = 6 + mTime / 10 % 3;
	}
	else if (_fDirection & _player->f_left)
	{
		//左下
		if (_fDirection & _player->f_down)
		{
			//斜め移動はスピードダウン
			//1/√2 = 0.70710678...
			speed *= 0.7071f;

			dy = (int)(speed * MyData::vectorRate);
		}
		//左上
		else if (_fDirection & _player->f_up)
		{
			//斜め移動はスピードダウン
			//1/√2 = 0.70710678...
			speed *= 0.7071f;

			dy = -(int)(speed * MyData::vectorRate);
		}

		//左に移動
		dx = -(int)(speed * MyData::vectorRate);

		mGraphNum = 3 + mTime / 10 % 3;
	}
	//下
	else if (_fDirection & _player->f_down)
	{
		dy = (int)(speed * MyData::vectorRate);
		mGraphNum = 0 + mTime / 10 % 3;
	}
	//上
	else if (_fDirection & _player->f_up)
	{
		dy = -(int)(speed * MyData::vectorRate);
		mGraphNum = 9 + mTime / 10 % 3;
	}


	//通れるなら移動
	if (_main->canPass(point->x + dx, point->y))
	{
		point->x += dx;
	}
	if (_main->canPass(point->x, point->y + dy))
	{
		point->y += dy;
	}

	//画面外にはみ出したらだめよ
	this->point->x = max(point->x, 0);
	this->point->x = min(point->x, (MyData::MAP_WIDTH * MyData::vectorRate) - 1);
	this->point->y = max(point->y, 0);
	this->point->y = min(point->y, (MyData::MAP_HEIGHT * MyData::vectorRate) - 1);


	//移動のログを保存
	inputLog.push(_fDirection);
}




}
}
}
}
