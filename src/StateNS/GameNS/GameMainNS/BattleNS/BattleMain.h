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
	Main(Vector2, int);
	~Main();
	void initialize(int);
	Child* update(const GameMain*);
	void draw() const;

private:
	Stage* stage;

	ActionController* aController;
	StringController* sController;

	BattleChild* mChild;
	int mTime;
	int mFinTime = 0;
	
	//�v���C���[�̃t�B�[���h�ł̈ʒu
	const Vector2 mPlayerPos;

	//�v���C���[�ƓG���ꏏ�ɓ����Ă���z��
	vector<Actor*> actors;

	//�v���C���[�̔z��
	vector<Actor*> players;

	//�G�̔z��
	vector<Actor*> enemies;

	//Actor�̔z����쐬
	void addActor(int);

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

class FirstAnimation : public BattleChild
{
public:
	FirstAnimation(vector<Actor*>);
	~FirstAnimation();
	void initialize();
	BattleChild* update(ActionController*, StringController*, vector<Actor*>);
	void draw(ActionController*) const;
	bool goField() const { return false; }
private:
	int mTime;

	//�o�g���J�n���̃A�j���[�V����
	//Strategy
	class AnimeChild
	{
	public:
		virtual ~AnimeChild() {};
		virtual void draw(int) const = 0;
	};

	class Anime1 : public AnimeChild
	{
	public:
		Anime1() {};
		~Anime1() {};
		void draw(int _time)  const;
	};

	class Anime2 : public AnimeChild
	{
	public:
		Anime2() {};
		~Anime2() {};
		void draw(int _time)  const;
	};

	class Anime3 : public AnimeChild
	{
	public:
		Anime3() {};
		~Anime3() {};
		void draw(int _time)  const;
	};

	class Anime4 : public AnimeChild
	{
	public:
		Anime4() {};
		~Anime4() {};
		void draw(int _time)  const;
	};

	AnimeChild* mChild;
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
	int mFinTime = 0;

	//�o�g�����I�������
	bool finBattle(const vector<Actor*>) const;

	//�o�g���I����̃��b�Z�[�W���o��
	void updateMessage(StringController*, bool);

	//�o�g���œ�����o���l���v�Z
	int calcExp(vector<Actor*>);
};

//========================================================================
//�o�g����̃��U���g���
//State�p�^�[������
//========================================================================
class Result : public BattleChild
{
public:
	Result(int);
	~Result();
	void initialize(vector<Actor*>);
	BattleChild* update(ActionController*, StringController*, vector<Actor*>);
	void draw(ActionController*) const;
	bool goField() const;

private:
	class ResultStatus
	{
	public:
		ResultStatus(Actor*, int);
		~ResultStatus() { DeleteGraph(mImg); };
		void initialize(Actor*, int);
		void update();
		void draw(int, int) const;

		//�Z�[�u�p�̕�������쐬
		string getSaveString();

		//���ɍs���Ă�����(���x���A�b�v�̃A�j���[�V�����͏I�������)
		bool goNext() const;

	private:
		//�Z�[�u�p
		int ID;
		std::string name;

		int mTime;
		int mImg;

		int mAllExp;
		int mNowExp;
		int mAfterExp;

		bool mLevelUp;
		int mLevelTime;
	};

	bool initialized;
	int mImg;
	int mBackImg;
	int mTime;
	const int mGetExp;

	vector< ResultStatus* > players{};

	//�O���f�[�^�ɃZ�[�u
	void saveData();
};





}
}
}
}