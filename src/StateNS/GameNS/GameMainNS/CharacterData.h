#pragma once

#include "..\..\..\Data.h"

//�{����DB�ɏ����ׂ�����
namespace CharacterData {

//���̃��x���܂ł�exp
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
	//�\�͒l��max��50�ɂ��悤
	CharaData{ 0, Status{ 20, 20, 20, 20, 20, 20 }, "play", "�䂤����" },
	CharaData{ 1, Status{ 15,  5, 10, 40, 20, 30 }, "magic", "�܂ق�����" },
	CharaData{ 2, Status{ 30, 30, 30, 10, 10, 10 }, "monq", "�����Ƃ���" },
	CharaData{ 3, Status{ 40, 10, 20, 10, 20, 20 }, "heal", "���񂶂�" },
	CharaData{ 4, Status{ 20, 40, 10, 0, 10, 40 }, "neko", "�˂�" },
	CharaData{ 5, Status{ 40, 10, 20, 10, 20, 20 }, "healer", "���񂶂�" },
	CharaData{ 6, Status{ 20, 0, 10, 40, 10, 40 }, "doctor", "������" }
};

}

using CharacterData::toCharacter;