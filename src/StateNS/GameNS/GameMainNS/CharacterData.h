#pragma once

#include "..\..\..\Data.h"

//–{—ˆ‚ÍDB‚É‘‚­‚×‚«‚±‚Æ
namespace CharacterData {

//Ÿ‚ÌƒŒƒxƒ‹‚Ü‚Å‚Ìexp
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
};

const int CharaNumber = 5;

const array< CharaData, CharaNumber> toCharacter
{
	CharaData{ 0, Status{ 20, 20, 20, 20, 20, 20 }, "play" },
	CharaData{ 1, Status{ 15,  5, 10, 40, 20, 30 }, "magic" },
	CharaData{ 2, Status{ 30, 30, 30, 10, 10, 10 }, "monq" },
	CharaData{ 3, Status{ 40, 10, 20, 10, 20, 20 }, "heal" },
	CharaData{ 4, Status{ 20, 40, 10, 0, 10, 40 }, "neko" }
};

}

using CharacterData::toCharacter;