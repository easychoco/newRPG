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

}

void Player::update()
{

}

void Player::draw() const
{
	DrawFormatString(100, 20, MyData::WHITE, "Player");
}




}
}
}
}
