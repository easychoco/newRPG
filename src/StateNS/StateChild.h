#pragma once

class Parent;
using GrandParent = Parent ;

namespace StateNS{


class Child {
public:
	~Child() {};
	//返り値は次のシーケンス
	virtual Child* update(const GrandParent*) = 0;
	virtual void draw() const = 0;
};



}