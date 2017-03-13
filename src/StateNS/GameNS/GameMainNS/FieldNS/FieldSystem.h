#pragma once

namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace FieldNS{


class GameSystem
{
public:
	GameSystem();
	~GameSystem();
	void initialize();
	void update();
	void draw() const;

};




}
}
}
}