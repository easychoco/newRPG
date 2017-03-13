#include "FieldPlayer.h"

#include "..\..\..\..\Data.h"
#include "..\..\..\..\KeyInput.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace FieldNS{


Player::Player()
{
	initialize();
}

Player::~Player()
{

}

void Player::initialize()
{
	point = new Vector2{ 0, 0 };
}

void Player::update()
{

}

void Player::draw() const
{
	DrawFormatString(100, 20, MyData::WHITE, "Player");
	DrawCircle(point->x / 1000, point->y / 1000, 5, MyData::GREEN, true);
}




}
}
}
}
