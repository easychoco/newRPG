#include "BattlePlayer.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace BattleNS {

Player::Player(Status _s) : 
Actor(_s) 
{
	initialize(); 
};

Player::~Player()
{

}

void initialize()
{

}

bool Player::attack()
{
	act = new Action(status.ID, 1, Action::Actions::ACT_ATTACK);
	return true;
}


void Player::draw(int _x, int _y) const
{
	DrawRotaGraph(_x, _y, 1.0, 0.0, mImg, true);
}


//========================================================================
// ì‡ïîprivateä÷êî
//========================================================================





}
}
}
}
