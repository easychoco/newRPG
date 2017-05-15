#pragma once

#include "..\..\..\Data.h"

//本来はDBに書くべきこと
namespace MonsterData {




}



//敵の性能
//DBに書くべき内容
namespace EnemySpec
{
	//敵の種族値
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
		Status{ 0, "Data/Image/enemy/1_1.png", "スライム", 20, 20, 20, 20, 20, 20 },
		Status{ 1, "Data/Image/enemy/1_2.png", "かたスライム", 20, 15, 25, 15, 25, 20 },
		Status{ 2, "Data/Image/enemy/1_3.png", "とびとんび", 20, 25, 20, 15, 10, 30 },
		Status{ 3, "Data/Image/enemy/1_4.png", "葉っぱの精", 30, 10, 20, 10, 30, 20 },
		Status{ 4, "Data/Image/enemy/1_5.png", "フェアリー", 20, 20, 10, 20, 30, 20 },
	};

	const std::array< Status, 5> e_spec2
	{
		Status{ 0, "Data/Image/enemy/2_1.png", "アクア", 15, 5, 25, 30, 25, 20 },
		Status{ 1, "Data/Image/enemy/2_2.png", "フレア", 20, 10, 15, 30, 15, 30 },
		Status{ 2, "Data/Image/enemy/2_3.png", "バーム", 30, 10, 20, 30, 20, 10 },
		Status{ 3, "Data/Image/enemy/2_4.png", "もんきぃ", 20, 40, 20, 0, 20, 20 },
		Status{ 4, "Data/Image/enemy/2_5.png", "ぶうぅ", 30, 30, 20, 0, 20, 20 },
	};

	const std::array< Status, 5> e_spec3
	{
		Status{ 0, "Data/Image/enemy/3_1.png", "ガワガワ", 20, 20, 20, 20, 20, 20 },
		Status{ 1, "Data/Image/enemy/3_2.png", "燃えるパピルス", 20, 40, 0, 20, 0, 40 },
		Status{ 2, "Data/Image/enemy/3_3.png", "ミイラ", 30, 20, 25, 15, 25, 5 },
		Status{ 3, "Data/Image/enemy/3_4.png", "アヌビン", 20, 15, 30, 5, 30, 20 },
		Status{ 4, "Data/Image/enemy/3_5.png", "ザント", 10, 5, 30, 20, 30, 25 },
	};

	const std::array< Status, 5> e_spec4
	{
		Status{ 0, "Data/Image/enemy/4_1.png", "クランピ", 20, 10, 15, 25, 25, 25 },
		Status{ 1, "Data/Image/enemy/4_2.png", "ウィッチ", 15, 10, 10, 40, 20, 25 },
		Status{ 2, "Data/Image/enemy/4_3.png", "妖精戦士", 10, 30, 10, 20, 10, 40 },
		Status{ 3, "Data/Image/enemy/4_4.png", "竜騎士", 23, 23, 23, 23, 23, 23 },
		Status{ 4, "Data/Image/enemy/4_5.png", "流賊", 20, 20, 20, 20, 20, 20 },
	};

	const std::array< Status, 5> e_spec5
	{
		Status{ 0, "Data/Image/enemy/5_1.png", "影の案内人", 30, 10, 30, 10, 30, 10 },
		Status{ 1, "Data/Image/enemy/5_2.png", "怨使い", 25, 10, 10, 30, 30, 15 },
		Status{ 2, "Data/Image/enemy/5_3.png", "ドラゴン", 40, 30, 10, 10, 10, 20 },
		Status{ 3, "Data/Image/enemy/5_4.png", "獣騎士", 20, 40, 40, 5, 5, 10 },
		Status{ 4, "Data/Image/enemy/5_5.png", "クラフター", 25, 25, 25, 25, 25, 25 },
	};

	const std::array< std::array< Status, 5>, 5> toEneStatus
	{
		e_spec1,
		e_spec2,
		e_spec3,
		e_spec4,
		e_spec5,
	};

	struct SymbolData
	{
		int Lv;
		Status status;
	};

	const array< SymbolData, 5> toMonster
	{
		//能力値はmaxで50にしよう
		SymbolData{ 8, Status{ 0, "Data/Image/enemy/2_5.png", "ぶうぅ", 30, 10, 30, 10, 30, 10 } },
		SymbolData{ 13, Status{ 1, "Data/Image/enemy/s_2.png", "デスコーピオン", 25, 30, 30, 10, 10, 15 } },
		SymbolData{ 18, Status{ 2, "Data/Image/enemy/s_3.png", "ニャフィンクス", 40, 10, 20, 10, 20, 20 } },
		SymbolData{ 20, Status{ 3, "Data/Image/enemy/s_4.png", "ガーゴイル", 20, 20, 10, 20, 10, 40 } },
		SymbolData{ 35, Status{ 4, "Data/Image/enemy/s_5.png", "魔神", 20, 20, 20, 20, 20, 20 } },
	};


}

using EnemySpec::toEneStatus;
using EnemySpec::toMonster;
