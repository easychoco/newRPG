#pragma once

#include "..\..\..\Data.h"

//本来はDBに書くべきこと
namespace CharacterData {

//次のレベルまでのexp
const int nextExp = 100;

struct Status
{
	int h, a, b, c, d, s;
};

struct CharaData
{
	int ID;
	Status s;
	char* fileName;
	char* charaName;
};

const int CharaNumber = 9;

const array< CharaData, CharaNumber> toCharacter
{
	//能力値はmaxで50にしよう
	CharaData{ 0, Status{ 20, 30, 10, 30, 10, 20 }, "play", "ゆうしゃ" },
	CharaData{ 1, Status{ 20, 20, 20, 20, 20, 20 }, "heroine", "せんし" },
	CharaData{ 2, Status{ 15,  5, 10, 40, 20, 30 }, "magic", "まほうつかい" },
	CharaData{ 3, Status{ 15, 40, 20,  5, 10, 30 }, "monq", "かくとうか" },
	CharaData{ 4, Status{ 10,  0, 10, 50, 20, 30 }, "magi", "まどうし" },
	CharaData{ 5, Status{ 50, 10, 20, 10, 20, 10 }, "healer", "けんじゃ" },
	CharaData{ 6, Status{ 40, 10, 30, 10, 30,  0 }, "elf", "エルフ" },
	CharaData{ 7, Status{ 20, 40, 10, 0, 10, 40 }, "neko", "ねこ" },
	CharaData{ 8, Status{ 25, 25, 25, 25, 25, 25 }, "king", "おうさま" },
};

}

using CharacterData::toCharacter;