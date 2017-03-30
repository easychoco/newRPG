#pragma once
#include "..\GameMainChild.h"
#include "..\GameMain.h"
#include "..\..\..\..\Data.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {

class GameMain;

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
	Main(const GameMain*);
	~Main();
	void initialize(vector<GameMainNS::GameMain::Status>);
	Child* update(const GameMain*);
	void draw() const;

private:
	Stage* stage;

	ActionController* aController;
	StringController* sController;

	GameScene mNext;
	BattleChild* mChild;
	int mTime;
	int mFinTime = 0;

	//�v���C���[�ƓG���ꏏ�ɓ����Ă���z��
	vector<Actor*> actors;

	//�v���C���[�̔z��
	vector<Actor*> players;

	//�G�̔z��
	vector<Actor*> enemies;

	//Actor�̔z����쐬
	void addActor(vector<GameMainNS::GameMain::Status>);

	//�v���C���[�̃X�e�[�^�X��`�悷��
	void drawStatus(int, int, const vector<Actor*>&) const;

	//�o�g�����I��������𔻒肷��
	bool finBattle() const;

	//HP���v�Z����
	int calcHP(int, int) const;

	//�\�͒l���v�Z����
	int calcStatus(int, int) const;

};

//========================================================================
// �o�g�����̏��
//========================================================================
class BattleChild
{
public:
	virtual ~BattleChild() {};
	virtual BattleChild* update(ActionController*, StringController*, vector<Actor*>) = 0;
	virtual void draw(ActionController*) const = 0;
	virtual bool goField() const = 0;
};

//========================================================================
//�o�g���ł̍s�������ʃN���X
//State�p�^�[������
//========================================================================
class Decide : public BattleChild
{
public:
	Decide(vector<Actor*>);
	~Decide();
	void initialize(vector<Actor*>&);
	BattleChild* update(ActionController*, StringController*, vector<Actor*>);
	void draw(ActionController*) const;
	bool goField() const { return false; }
private:
	int doneNum = 0;

	//�s�������߂�Ƃ��̃L���[
	//���g�̓v���C���[�ƓG���s�����ɓ����Ă���
	queue<Actor*> act_que;

	vector<Actor*> enemies;
	vector<Actor*> players;

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
	BattleChild* update(ActionController*, StringController*, vector<Actor*>);
	void draw(ActionController*) const;
	bool goField() const { return false; }

private:
	//�o�g�����I�������
	bool finBattle(const vector<Actor*>) const;
};


//========================================================================
//�o�g����̃��U���g���
//State�p�^�[������
//========================================================================
class Result : public BattleChild
{
public:
	Result();
	~Result();
	void initialize();
	BattleChild* update(ActionController*, StringController*, vector<Actor*>);
	void draw(ActionController*) const;
	bool goField() const;

private:
	int mImg;
	int mBackImg;
	int mTime;

	void drawResult(int, int, int) const;

};



}
}
}
}