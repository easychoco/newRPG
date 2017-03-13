#pragma once


namespace StateNS {

class Parent;


namespace GameNS{



class Child
{
public:
	virtual ~Child() {};
	virtual Child* update(Parent*) = 0;
	virtual void draw() const = 0;
};






}
}