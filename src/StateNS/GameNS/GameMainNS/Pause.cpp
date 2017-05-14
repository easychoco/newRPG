#include "Pause.h"
#include "GameMain.h"

#include "..\..\..\Data.h"
#include "..\..\..\KeyInput.h"

#include <fstream>


namespace StateNS {
namespace GameNS {
namespace GameMainNS {


Pause::Pause()
{
	initialize();
}

Pause::~Pause()
{
	SAFE_DELETE(child);
}

void Pause::initialize()
{
	child = new Home();
}

bool Pause::update(GameMain* _gameMain)
{
	PauseChild* next = child->update(_gameMain);

	if (child != next)
	{
		SAFE_DELETE(child);
		child = next;
	}

	//return true��Pause����
	return child->finPause();
}

void Pause::draw() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
	DrawBox(0, 0, 640, 480, MyData::WHITE, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	child->draw();
}


//==============================================
//�����v���C�x�[�g�N���X
//==============================================

//�t�@�C������p�[�e�B����ǂݍ���
void Pause::PauseChild::setParty()
{
	std::ifstream fin("Data/Text/PlayerData.txt");

	//�t�@�C���ǂݍ��݃G���[
	if (!fin)
	{
		assert(!"File Input Error!");
		exit(0);
	}

	for (auto& c : party)
	{
		fin >> c.ID >> c.name >> c.exp;
	}
}

//-----------------------------------------
//Home
//-----------------------------------------
Pause::Home::Home()
{
	mCursorPos = 0;
	isFin = false;
	initialized = false;
}

Pause::Home::~Home()
{

}

void Pause::Home::initialize()
{
	mCursorPos = 0;
	mMenuImg = LoadGraph("Data/Image/PauseHome.png");
	mCursorImg = LoadGraph("Data/Image/PauseCursor.png");
	assert((mMenuImg | mCursorImg) != -1 && "PauseHome�摜�ǂݍ��݃G���[!");

	mTime = 0;

	//�t�@�C������p�[�e�B����ǂݍ���
	setParty();

	for (int i = 0; i < 4; i++)
	{
		//�p�[�e�B��move�摜�ǂݍ���
		LoadDivGraph(getFileName(toCharacter[party[i].ID].fileName).c_str(), 12, 3, 4, 32, 32, mPartyImg[i]);
	}

	isFin = false;
	initialized = true;

}


Pause::PauseChild* Pause::Home::update(GameMain* _gameMain)
{
	Pause::PauseChild* next = this;

	if (!initialized)initialize();

	mTime++;

	//key Input
	if (!prePush)
	{
		if (Input_UP())
		{
			mCursorPos--;
		}
		if (Input_DOWN())
		{
			mCursorPos++;
		}
		//����
		if (Input_Z())
		{
			//�V�[�P���X�J��
			switch (mCursorPos)
			{
			case 0: next = new PartyChange(); break;
			case 1: next = new Config(); break;
			case 2: next = new Save(); break;
			case 3: next = new Load(); break;
			case 4: isFin = true; break;
			}
		}
		mCursorPos = (mCursorPos + 5) % 5;
	}

	prePush = Input_UP() || Input_DOWN() || Input_Z();

	return next;
}

void Pause::Home::draw() const
{
	DrawGraph(0, 0, mMenuImg, true);
	DrawGraph(-5, 25 + mCursorPos * 60, mCursorImg, true);

	drawParty();
	drawMessage();
}

bool Pause::Home::finPause() const
{
	//for Debug
	return isFin;
}

string Pause::Home::getFileName(char* _fileName)
{
	string ret = "Data/Image/move_";
	ret += _fileName;
	ret += ".png";
	return ret;
}

void Pause::Home::drawParty() const
{
	drawChara(0, 320, 20);
	drawChara(1, 480, 20);
	drawChara(2, 320, 240);
	drawChara(3, 480, 240);
}

void Pause::Home::drawChara(int _ID, int _x, int _y) const
{
	DrawGraph(_x, _y, mPartyImg[_ID][mTime / 10 % 3], true);

	DrawFormatString(_x - 20, _y + 50, MyData::BLACK, "Lv.%d", party[_ID].exp / 100 + 1);
	DrawFormatString(_x - 20, _y + 70, MyData::BLACK, party[_ID].name.c_str());
}

void Pause::Home::drawMessage() const
{
	//�g�`��
	DrawBox(10, 350, 630, 470, MyData::WHITE, false);
	DrawBox(13, 353, 627, 467, MyData::WHITE, false);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
	DrawBox(15, 355, 625, 465, MyData::WHITE, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	//�����`��
	DrawString(30, 370, toString[mCursorPos], MyData::BLACK);
}


//-----------------------------------------
//PartyChange
//-----------------------------------------
Pause::PartyChange::PartyChange()
{
	initialize();
}

Pause::PartyChange::~PartyChange()
{

}

void Pause::PartyChange::initialize()
{
	mTime = 0;
	mSelectedChara = 0;
	mNowSelect = 0;
	drawNum = (int)sqrt(CharacterData::CharaNumber) + 1;
	pEdit = PartyEdit::EDIT_PARTY;

	//�摜�ǂݍ���
	for (int i = 0; i < CharacterData::CharaNumber; i++)
	{
		mUpImg[i] = LoadGraph(getUpFileName(toCharacter[i].fileName).c_str());
		LoadDivGraph(getMoveFileName(toCharacter[i].fileName).c_str(), 12, 3, 4, 32, 32, mMoveImg[i]);
	}

	//�t�@�C������p�[�e�B����ǂݍ���
	setParty();

}

Pause::PauseChild* Pause::PartyChange::update(GameMain* _gameMain)
{
	Pause::PauseChild* next = this;

	mTime++;

	//�p�[�e�B�ύX

	//Key Input
	if (!prePush)
	{
		if (Input_Z())
		{
			editParty(_gameMain);
		}
		if (Input_X())
		{
			next = new Home();
		}
		if (Input_RIGHT())
		{
			if (pEdit == EDIT_PARTY)mSelectedChara++;
			else mNowSelect++;
		}
		if (Input_LEFT())
		{
			if(pEdit == EDIT_PARTY)mSelectedChara--;
			else mNowSelect--;
		}
		if (Input_UP())
		{
			if(mNowSelect - drawNum >= 0)
				mNowSelect -= drawNum;
		}
		if (Input_DOWN())
		{
			if(mNowSelect + drawNum < CharacterData::CharaNumber)
				mNowSelect += drawNum;
		}
		mSelectedChara = (mSelectedChara + 4) % 4;
		mNowSelect = (mNowSelect + CharacterData::CharaNumber) % CharacterData::CharaNumber;
	}

	prePush = Input_Z() || Input_X() || Input_RIGHT() || Input_LEFT() || Input_UP() || Input_DOWN();

	return next;
}

void Pause::PartyChange::draw() const
{
	//�����G��`��
	drawStatus();

	//�`�����N�^�[������`��
	for (int i = 0; i < CharacterData::CharaNumber; i++)
	{
		drawChara(i, 240 + (i % drawNum + 1) * (400 / (drawNum + 1)), (i / drawNum + 1) * (350 / (drawNum + 1)) );
	}

	//�p�[�e�B��`��
	drawParty();

	//�I��g��`��
	int frame_x{ 0 }, frame_y{ 0 };
	switch (pEdit)
	{
	case EDIT_CHARA:
	{
		frame_x = 240 + (mNowSelect % drawNum + 1) * (400 / (drawNum + 1));
		frame_y = (mNowSelect / drawNum + 1) * (350 / (drawNum + 1));
		break;
	}
	case EDIT_PARTY:
	{
		frame_x = 300 + 80 * mSelectedChara;
		frame_y = 400;
		break;
	}
	}
	DrawBox(300 + 80 * mSelectedChara, 400, 332 + 80 * mSelectedChara, 432, MyData::RED, false);
	DrawBox(frame_x, frame_y, frame_x + 32, frame_y + 32, MyData::YELLOW, false);
}

bool Pause::PartyChange::finPause() const
{
	return false;
}


//====================================================================
//����private�֐�
//====================================================================

//�p�[�e�B�������
void Pause::PartyChange::editParty(GameMain* _gameMain)
{
	switch (pEdit)
	{
	case EDIT_PARTY:
	{
		//�E�҂�I��ł��Ȃ�������L�����I����
		if (mSelectedChara != 0)
		{
			mNowSelect = 0;
			pEdit = EDIT_CHARA;
		}
		break;
	}
	case EDIT_CHARA:
	{
		//�I�񂾃p�[�e�B����������΃p�[�e�B�����o�[�I����
		if (checkParty())
		{
			pEdit = EDIT_PARTY;
			mSelectedChara = 0;
			std::array<int, 4> nextParty
			{
				party[0].ID,
				party[1].ID,
				party[2].ID,
				party[3].ID,
			};
			_gameMain->changeParty();
		}
		break;
	}
	}
}

//�p�[�e�B�����������`�F�b�N
bool Pause::PartyChange::checkParty()
{
	//�ς���Ă��Ȃ�������
	if (mNowSelect == party[mSelectedChara].ID)return true;

	//�����L�������܂܂�Ă�����
	for (auto p : party)
	{
		if (p.ID == mNowSelect)return false;
	}

	//�����łȂ���Γ���ւ�
	party[mSelectedChara].ID = mNowSelect;
	party[mSelectedChara].name = toCharacter[mNowSelect].charaName;

	//�Z�[�u�f�[�^��������
	save();

	return true;
}

void Pause::PartyChange::save()
{
	std::ofstream fout("Data/Text/PlayerData.txt");
	assert(fout && "PlayerData.txt�ǂݍ��݃G���[");
	for (auto p : party)
	{
		fout << p.ID << " " << p.name << " " << p.exp << std::endl;
	}
}

//�L�����N�^�[�̕����Ă���A�j���[�V������`��
void Pause::PartyChange::drawChara(int _ID, int _x, int _y) const
{
	DrawGraph(_x, _y, mMoveImg[_ID][mTime / 10 % 3], true);
}

//�L�����N�^�[�̏ڂ����X�e�[�^�X��`��
void Pause::PartyChange::drawStatus() const
{
	//�I�𒆂̃L�����N�^�[���擾
	int charaNum = ((pEdit == EDIT_CHARA) ? mNowSelect : party[mSelectedChara].ID);

	//�����G��`��
	DrawGraph(0, 0, mUpImg[charaNum], true);

	//�g��`��
	DrawBox(10, 250, 240, 470, MyData::WHITE, false);
	DrawBox(13, 253, 237, 467, MyData::WHITE, false);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
	DrawBox(15, 255, 235, 465, MyData::WHITE, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	DrawString(20, 260, "�̗�", MyData::BLACK);
	DrawString(20, 290, "�U��", MyData::BLACK);
	DrawString(20, 320, "�h��", MyData::BLACK);
	DrawString(20, 350, "���@", MyData::BLACK);
	DrawString(20, 380, "���h", MyData::BLACK);
	DrawString(20, 410, "����", MyData::BLACK);
	DrawString(20, 440, "��", MyData::BLACK);

	DrawBox(80, 260, 80 + toCharacter[charaNum].s.h * 3, 280, MyData::GREEN, true);
	DrawBox(80, 290, 80 + toCharacter[charaNum].s.a * 3, 310, MyData::GREEN, true);
	DrawBox(80, 320, 80 + toCharacter[charaNum].s.b * 3, 340, MyData::GREEN, true);
	DrawBox(80, 350, 80 + toCharacter[charaNum].s.c * 3, 370, MyData::GREEN, true);
	DrawBox(80, 380, 80 + toCharacter[charaNum].s.d * 3, 400, MyData::GREEN, true);
	DrawBox(80, 410, 80 + toCharacter[charaNum].s.s * 3, 430, MyData::GREEN, true);

	int h = toCharacter[charaNum].s.h;
	int a = toCharacter[charaNum].s.a;
	int c = toCharacter[charaNum].s.c;
	DrawBox(80, 440, 80 + (max(h - abs(a - c), min(a, c))) * 3, 460, MyData::GREEN, true);
}

void Pause::PartyChange::drawParty() const
{
	//�g��`��
	DrawBox(250, 350, 630, 470, MyData::WHITE, false);
	DrawBox(253, 353, 627, 467, MyData::WHITE, false);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
	DrawBox(255, 355, 625, 465, MyData::GLAY, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	//�p�[�e�B�����o�[��`��
	drawChara(party[0].ID, 300, 400);
	drawChara(party[1].ID, 380, 400);
	drawChara(party[2].ID, 460, 400);
	drawChara(party[3].ID, 540, 400);

}

string Pause::PartyChange::getUpFileName(char* _fileName)
{
	string ret = "Data/Image/up_";
	ret += _fileName;
	ret += ".png";
	return ret;
}

string Pause::PartyChange::getMoveFileName(char* _fileName)
{
	string ret = "Data/Image/move_";
	ret += _fileName;
	ret += ".png";
	return ret;
}



//-----------------------------------------
//Config
//-----------------------------------------
Pause::Config::Config()
{
	initialize();
}

Pause::Config::~Config()
{

}

void Pause::Config::initialize()
{

}

Pause::PauseChild* Pause::Config::update(GameMain* _gameMain)
{
	return this;
}

void Pause::Config::draw() const
{
	DrawFormatString(0, 0, MyData::BLACK, "Config");
}

bool Pause::Config::finPause() const
{
	return false;
}

//-----------------------------------------
//Save
//-----------------------------------------
Pause::Save::Save()
{
	initialize();
}

Pause::Save::~Save()
{

}

void Pause::Save::initialize()
{
	setParty();
}

Pause::PauseChild* Pause::Save::update(GameMain* _gameMain)
{
	WaitTimer(300);
	WaitKey();
	prePush = true;
	return new Home();
}

void Pause::Save::draw() const
{
	//�g�`��
	DrawBox(100, 150, 540, 320, MyData::BLACK, false);
	DrawBox(103, 153, 537, 317, MyData::BLACK, false);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
	DrawBox(105, 155, 535, 315, MyData::BLACK, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	DrawString(115, 165, "�����܂ł̃f�[�^���Z�[�u���܂��D", MyData::WHITE);
	DrawString(115, 195, "�����̂킩�镶������͂��Ă��������D", MyData::WHITE);

	char fileName[11];
	KeyInputString(115, 230, 10, fileName, false);

	string saveName = "Data/SaveData/";
	saveName += fileName;
	saveName += ".txt";
	std::ifstream fin;
	fin.open(saveName);
	if (fin)
	{
		DrawFormatString(115, 260, MyData::WHITE, "%s �͊��ɑ��݂��܂��D", fileName);
		DrawFormatString(115, 290, MyData::WHITE, "�����L�[�������Ǝ��ցD", fileName);
		fin.close();
		return;
	}
	std::ofstream fout(saveName);
	for (auto p : party)
	{
		fout << p.ID << " " << p.name << " " << p.exp << std::endl;
	}

	DrawFormatString(115, 260, MyData::WHITE, "%s �ɃZ�[�u���܂����D", fileName);
	DrawFormatString(115, 290, MyData::WHITE, "�����L�[�������Ǝ��ցD", fileName);

}

bool Pause::Save::finPause() const
{
	return false;
}

//-----------------------------------------
//Load
//-----------------------------------------
Pause::Load::Load()
{
	initialize();
}

Pause::Load::~Load()
{

}

void Pause::Load::initialize()
{

}

Pause::PauseChild* Pause::Load::update(GameMain* _gameMain)
{
	WaitTimer(300);
	WaitKey();

	setParty();
	_gameMain->changeParty();
	prePush = true;
	return new Home();
}

void Pause::Load::draw() const
{
	//�g�`��
	DrawBox(100, 150, 540, 320, MyData::BLACK, false);
	DrawBox(103, 153, 537, 317, MyData::BLACK, false);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
	DrawBox(105, 155, 535, 315, MyData::BLACK, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	DrawString(115, 165, "�Z�[�u�f�[�^�����[�h���܂��D", MyData::WHITE);
	DrawString(115, 195, "�����̃Z�[�u�����t�@�C��������͂��Ă��������D", MyData::WHITE);

	char fileName[11];
	KeyInputString(115, 230, 10, fileName, false);

	string saveName = "Data/SaveData/";
	saveName += fileName;
	saveName += ".txt";

	// �R�s�[�����I�[�v������
	std::ifstream fin(saveName);
	if (!fin)
	{
		DrawFormatString(115, 260, MyData::WHITE, "%s �݂͂���܂���ł����D", fileName);
		DrawFormatString(115, 290, MyData::WHITE, "�����L�[�������Ǝ��ցD", fileName);
		fin.close();
		return;
	}

	// �R�s�[����I�[�v������
	std::ofstream fout("Data/Text/PlayerData.txt");

	// �R�s�[
	fout << fin.rdbuf() << std::flush;
	
	DrawFormatString(115, 260, MyData::WHITE, "%s �����[�h���܂����D", fileName);
	DrawFormatString(115, 290, MyData::WHITE, "�����L�[�������Ǝ��ցD", fileName);
}

bool Pause::Load::finPause() const
{
	return false;
}




}
}
}
