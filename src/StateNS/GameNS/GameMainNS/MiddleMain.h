#pragma once

#include "GameMainChild.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class MiddleChild;
namespace BattleNS 
{
	class StringController;
}

class MiddleMain : public Child
{
public:
	MiddleMain(GameScene, int arg);//arg �͓G���x���C�܂��͊l���o���l
	~MiddleMain();
	void initialize(int);
	Child* update(GameParent*);
	void draw() const;

private:
	MiddleChild* mChild;
	GameScene nextScene;
	int arg;
};

//MiddleMain�ł���State��Child
class MiddleChild
{
public:
	virtual ~MiddleChild() {};
	virtual void update() = 0;
	virtual void draw() const = 0;
	bool goNext() { return mGoNext; }
protected :
	bool mGoNext = false;
};

class ToBattle : public MiddleChild
{
public:
	ToBattle(int _arg);
	~ToBattle();
	void initialize(int);
	void update();
	void draw() const;
private:
	int mTime;

	//�G���x��
	int arg;
};

class ToField : public MiddleChild
{
public:
	ToField(int _arg);
	~ToField();
	void initialize(int);
	void update();
	void draw() const;
private:
	int mTime;

	int mImg;
	int mBackImg;

	//�o���l
	int arg;

	//�o�g���ɏ��������ǂ���
	bool win;

	//���b�Z�[�W�`��
	BattleNS::StringController* sController;

	//�o���l�Ƃ��X�e�[�^�X�\��
	void drawResult(int x, int y, int img) const;
};



}
}
}