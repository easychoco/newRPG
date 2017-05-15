#include "Parent.h"
#include "StateNS\Title.h"
#include "StateNS\StateParent.h"

#include "Data.h"

#include<fstream>

Parent::Parent()
{
	mChild = 0;
	initialize();
}

Parent::~Parent()
{
	SAFE_DELETE(mChild);

	//�Z�[�u�f�[�^������
	std::ofstream fout("Data/Text/PlayerData.txt");
	fout << "0 �䂤���� 0" << std::endl;
	fout << "1 ���� 0" << std::endl;
	fout << "2 �܂ق����� 0" << std::endl;
	fout << "3 �����Ƃ��� 0" << std::endl;
}

void Parent::initialize()
{
	mChild = new StateNS::Title();
}

void Parent::update()
{
	Child* next = mChild->update(this);

	//�J��
	if (mChild != next)
	{
		SAFE_DELETE(mChild);
		mChild = next;
	}

	next = 0;
}

void Parent::draw() const
{
	mChild->draw();
}

