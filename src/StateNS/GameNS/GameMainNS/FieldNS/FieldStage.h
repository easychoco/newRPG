#pragma once

#include "..\..\..\..\Data.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace FieldNS {


class Stage
{
public:
	Stage();
	~Stage();
	void initialize();
	void update();
	void draw(const Vector2* _player) const;
	bool canPass(int px, int py);
private:
	int mBackImg;

	//mapChip(32x32pixcels)
	int mapChip[112];

	//map(40x30chips)
	std::array< std::array<int, 40>, 30> mapData;

	//ƒ}ƒbƒv•`‰æ
	//”wŒi•`‰æ
	void drawBack(const Vector2*) const;

	//‘OŒi•`‰æ
	template<typename Arr>
	void drawMap(Arr, const Vector2*) const;

	class Chip
	{
	public:
		Chip(bool _canPass, int _enemyLevel) : canPass(_canPass), enemyLevel(_enemyLevel) {};
		~Chip() {};
		const bool canPass;//’Ê‚é‚±‚Æ‚ª‚Å‚«‚é‚©
		const int enemyLevel;//oŒ»‚·‚é“G‚ÌƒŒƒxƒ‹
	};

	const Chip chip[112] = 
	{
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip( true, 0),//“ƒ‚ÌŠK’i
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip( true, 0),//“ƒ‚ÌŠK’i
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip( true, 5),//“ƒ‚Ì’n–Ê
		Chip(false, 0),
		Chip( true, 0),//“ƒ‚ÌŠK’i
		Chip(false, 0),
		Chip( true, 3),//»”™‚Ì’n–Ê
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip( true, 4),//“y‚Ì’n–Ê
		Chip(false, 0),
		Chip(false, 0),
		Chip( true, 5),//“ƒ‚Ì’n–Ê
		Chip(false, 0),
		Chip( true, 0),//“ƒ‚ÌŠK’i
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip( true, 0),//‹´
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip( true, 2),//X‚Ì’n–Ê
		Chip( true, 2),//X‚Ì’n–Ê
		Chip( true, 2),//X‚Ì’n–Ê
		Chip( true, 2),//X‚Ì’n–Ê
		Chip( true, 2),//X‚Ì’n–Ê
		Chip( true, 2),//X‚Ì’n–Ê
		Chip( true, 4),//“y‚Ì’n–Ê
		Chip( true, 4),//“y‚Ì’n–Ê
		Chip( true, 4),//“y‚Ì’n–Ê
		Chip( true, 5),//“ƒ‚Ì’n–Ê
		Chip( true, 5),//“ƒ‚Ì’n–Ê
		Chip( true, 5),//“ƒ‚Ì’n–Ê
		Chip( true, 0),//‹´
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip(true , 1),//‘Œ´‚Ì’n–Ê
		Chip(true , 1),//‘Œ´‚Ì’n–Ê
		Chip(true , 1),//‘Œ´‚Ì’n–Ê
		Chip( true, 0),//‹´
		Chip( true, 0),//‹´
		Chip( true, 0),//‹´
		Chip(false, 0),
		Chip(false, 0),
		Chip(false, 0),
		Chip( true, 0),//‹´
	};



};




}
}
}
}