#pragma once

namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace FieldNS{


class Stage
{
public:
	Stage();
	~Stage();
	void initialize();
	void update();
	void draw() const;
private:
	int mBackImg;
};




}
}
}
}