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
	�ŏ��Ȃ񂩃E���[���Ă���
	"Game Clear"
	�������ŉ�b������
	
	��b���I�������
	"Thank you for Playing"
	"X�L�[�Ń^�C�g����"


	���[�h���Ɉʒu�ύX
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

