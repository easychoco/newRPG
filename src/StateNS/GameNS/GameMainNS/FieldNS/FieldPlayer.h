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
	//内部クラス，パーティメンバーの処理
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

	//パーティメンバーへのポインタ
	PartyMember* next;

	//パーティメンバーを初期化したかどうか
	bool partyInitialized;
	
	//座標ベクトル
	Vector2* point;

	//敵にエンカウントしたかどうか
	bool mIsEncount;

	//内部では1000倍した値を保持する
	const int pointRate = MyData::vectorRate;

	//方向を決めるbitmaskで使用する
	const unsigned char f_right = 0b0001;
	const unsigned char f_left  = 0b0010;
	const unsigned char f_down  = 0b0100;
	const unsigned char f_up    = 0b1000;

	//キー入力のログ，仲間を動かすのに使う
	queue<unsigned char> inputLog;

	//画像の番号
	int mGraphNum;

	//画像
	int mImg[24];

	int mTime;

	float mSpeed;

	//==================
	// 内部private関数
	//==================
	//パーティメンバーを初期化
	void initializeParty(const array<int, 4>);

	//toCharacter.fileNameから画像の名前を生成
	const string getFileName(char*) const;

	//移動
	bool move(const FieldNS::Main*);

	//エンカウント
	void encount();

};




}
}
}
}