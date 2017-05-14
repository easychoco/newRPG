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

const int CharaNumber = 7;

const array< CharaData, CharaNumber> toCharacter
{
	//能力値はmaxで50にしよう
	CharaData{ 0, Status{ 20, 20, 20, 20, 20, 20 }, "play", "ゆうしゃ" },
	CharaData{ 1, Status{ 15,  5, 10, 40, 20, 30 }, "magic", "まほうつかい" },
	CharaData{ 2, Status{ 30, 30, 30, 10, 10, 10 }, "monq", "かくとうか" },
	CharaData{ 3, Status{ 40, 10, 20, 10, 20, 20 }, "heal", "けんじゃ" },
	CharaData{ 4, Status{ 20, 40, 10, 0, 10, 40 }, "neko", "ねこ" },
	CharaData{ 5, Status{ 40, 10, 20, 10, 20, 20 }, "healer", "けんじゃ" },
	CharaData{ 6, Status{ 20, 0, 10, 40, 10, 40 }, "doctor", "いしゃ" }
};

}

using CharacterData::toCharacter;