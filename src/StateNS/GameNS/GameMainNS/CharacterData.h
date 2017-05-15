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

const int CharaNumber = 9;

const array< CharaData, CharaNumber> toCharacter
{
	//�\�͒l��max��50�ɂ��悤
	CharaData{ 0, Status{ 20, 30, 10, 30, 10, 20 }, "play", "�䂤����" },
	CharaData{ 1, Status{ 20, 20, 20, 20, 20, 20 }, "heroine", "����" },
	CharaData{ 2, Status{ 15,  5, 10, 40, 20, 30 }, "magic", "�܂ق�����" },
	CharaData{ 3, Status{ 15, 40, 20,  5, 10, 30 }, "monq", "�����Ƃ���" },
	CharaData{ 4, Status{ 10,  0, 10, 50, 20, 30 }, "magi", "�܂ǂ���" },
	CharaData{ 5, Status{ 50, 10, 20, 10, 20, 10 }, "healer", "���񂶂�" },
	CharaData{ 6, Status{ 40, 10, 30, 10, 30,  0 }, "elf", "�G���t" },
	CharaData{ 7, Status{ 20, 40, 10, 0, 10, 40 }, "neko", "�˂�" },
	CharaData{ 8, Status{ 25, 25, 25, 25, 25, 25 }, "king", "��������" },
};

}

using CharacterData::toCharacter;