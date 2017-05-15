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

	//セーブデータ初期化
	std::ofstream fout("Data/Text/PlayerData.txt");
	fout << "0 ゆうしゃ 0" << std::endl;
	fout << "1 せんし 0" << std::endl;
	fout << "2 まほうつかい 0" << std::endl;
	fout << "3 かくとうか 0" << std::endl;
}

void Parent::initialize()
{
	mChild = new StateNS::Title();
}

void Parent::update()
{
	Child* next = mChild->update(this);

	//遷移
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

