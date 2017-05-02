#pragma once

namespace StateNS {

class Parent;

namespace GameNS {


class Pause
{
public:
	Pause();
	~Pause();
	void initialize();
	bool update();
	void draw() const;

};




}
}