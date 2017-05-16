#include "Clear.h"
#include "..\StateParent.h"

#include "..\..\Data.h"
#include "..\..\KeyInput.h"

namespace StateNS {
namespace GameNS {

Clear::Clear()
{

}

Clear::~Clear()
{

}

void Clear::initialize()
{

}

Child* Clear::update(StateNS::Parent* _parent)
{
	Child* next = this;

	/*
	最初なんかウワーってくる
	"Game Clear"
	時限式で会話をする
	
	会話が終わったら
	"Thank you for Playing"
	"Xキーでタイトルへ"


	ロード時に位置変更
	*/

	

	if (Input_V())
	{
		_parent->moveTo(_parent->NextSequence::SEQ_TITLE);
	}

	return next;
}

void Clear::draw() const
{
	DrawFormatString(0, 0, MyData::WHITE, "Clear");
}






}
}

