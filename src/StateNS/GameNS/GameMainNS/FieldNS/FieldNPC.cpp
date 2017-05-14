#include "FieldNPC.h"

#include <cmath>



namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace FieldNS {

void NPC::talk(Vector2 _player)
{
	if ( abs(this->point.x - _player.x) < 16000 && abs(this->point.y - _player.y) < 16000 )
		this->talkEvent();
}

//============================
//åpè≥ÉNÉâÉX
//============================

//ñ°ï˚NPC
Ally::Ally(int _x, int _y)
{
	point = Vector2(_x, _y);
}

Ally::~Ally()
{

}

void Ally::update()
{

}

void Ally::draw() const
{

}

//============================
//ì‡ïîprivateä÷êî
//============================
void Ally::talkEvent()
{

}

//ìGNPC
Monster::Monster(int _x, int _y)
{
	point = Vector2(_x, _y);
}

Monster::~Monster()
{

}

void Monster::update()
{

}

void Monster::draw() const
{

}

//============================
//ì‡ïîprivateä÷êî
//============================
void Monster::talkEvent()
{

}





}
}
}
}