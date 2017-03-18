#pragma once
#include "..\GameMainChild.h"
#include "..\..\..\..\Data.h"

#include <string>
#include <vector>


namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace BattleNS {

class Stage;
class Actor;
class Action;
class ActionController;
class StringController;
class BattleChild;

class Main : public Child
{
public:
	Main();
	~Main();
	void initialize();
	void update(GameParent*);
	void draw() const;
	GameScene changeScene();
	void addAction(Action* a);

protected:
	Stage* stage;

	ActionController* aController;
	StringController* sController;

	GameScene mNext;
	BattleChild* mChild;
	int mTime;


	//�v���C���[�ƓG���ꏏ�ɓ����Ă���z��
	vector<Actor*> actors;

	void addActor();

};

//========================================================================
// �o�g�����̏��
//========================================================================
class BattleChild
{
public:
	virtual ~BattleChild() {};
	virtual BattleChild* update(Main*) = 0;
	virtual void draw() const = 0;
};

//========================================================================
//�o�g���ł̍s�������ʃN���X
//State�p�^�[������
//========================================================================
class Decide : public BattleChild
{
public:
	Decide(vector<Actor*>& vec_act);
	~Decide();
	void initialize(vector<Actor*> vec_act);
	BattleChild* update(Main*);
	void draw() const;
private:
	//�s�������߂�Ƃ��̃L���[
	//���g�̓v���C���[�ƓG���s�����ɓ����Ă���
	queue<Actor*> act_que;
};

//========================================================================
//�o�g���ł̍s�����s�N���X
//State�p�^�[������
//========================================================================
class Battle : public BattleChild
{
public:
	Battle();
	~Battle();
	void initialize();
	BattleChild* update(Main*);
	void draw() const;
};

}
}
}
}