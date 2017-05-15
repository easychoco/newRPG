#include "Converse.h"

#include "..\..\..\Data.h"
#include "..\..\..\KeyInput.h"
#include "BattleNS\BattleStringController.h"
#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{



Converse::Converse(char* textName)
{

	/*
	���͕��͊e�s�̐擪��[��][�E][����]�̔ԍ������邱��
	0�ŗE��
	1�ŉ��l
	[�b��]��0�œ��ߖ����C1�ŉE�𓧉߁C2�ō��𓧉߁C3�ŗ�������
	*/

	string name = "Data/Text/Converse/";
	name += textName;
	name += ".txt";

	std::ifstream fin(name);
	if (!fin)assert(!"Converse : file input error!");

	//�S���ǂݍ���
	while (!fin.eof())
	{
		string tmp;
		fin >> tmp;
		mAllText.push_back(tmp);
	}

	//�Ō�̍s��\�����邽�߂ɋ󔒍s��������
	mAllText.push_back("");
	fin.close();

	initialize();
}

Converse::~Converse()
{
	SAFE_DELETE(sController);
}

void Converse::initialize()
{


	toImage[0] = LoadGraph("Data/Image/Converse/player.png");
	toImage[1] = LoadGraph("Data/Image/Converse/king.png");

	bool isErr = (toImage[0] != -1) & (toImage[1] != -1) & (toImage[2] != -1);
	assert(isErr && "Converse : �摜�ǂݍ��݃G���[");

	mTalkerSide = 0;
	mLeftNum = 0;
	mRightNum = 0;

	mTime = 0;
	mNowText = 0;
	fin = false;
	mPrePush = true;

	sController = new StringController();

	nextText();
}

bool Converse::update()
{
	mTime++;

	sController->update();

	bool push_Z = !mPrePush && Input_Z();
	mPrePush = Input_Z();

	//Z�L�[�Ńe�L�X�g����
	if (!fin && push_Z)
	{
		nextText();
	}

	//fin��true���y�L�[��������Ă�����Converse���I���
	return fin && push_Z;
}

void Converse::draw() const
{
	//�A���t�@�`�����l���Ŕ����w�i��`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
	DrawBox(0, 0, 640, 480, MyData::WHITE, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//��b�҂�`��

	//�����𓧉�
	if(mTalkerSide & 0b10)SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);
	DrawGraph(0, 0, toImage[mLeftNum], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�E���𓧉�
	if (mTalkerSide & 0b01)SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);
	DrawTurnGraph(350, 0, toImage[mRightNum], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�e�L�X�g��`��
	sController->draw();
}

//==============================================
//�����v���C�x�[�g�֐�
//==============================================
void Converse::nextText()
{
	string text = mAllText[mNowText];

	//�Ō�̕��͂܂��͋K�i�O�̕��͂��ǂݍ��܂ꂽ��I��
	if (text.size() < 2)
	{
		fin = true;
		return;
	}

	//��b�҂�ݒ�

	mLeftNum = (int)(text[0]) - 48;
	mRightNum = (int)(text[1]) - 48;
	mTalkerSide = (int)(text[2]) - 48;

	//�w�b�_�̐؂藎�Ƃ�
	text.erase(text.begin(), text.begin() + 3);


	//���͂��X�V
	sController->addMessage(text);

	mNowText++;
}



}
}
}
