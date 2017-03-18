#include "DxLib.h"
#include "KeyInput.h"
#include "Parent.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(TRUE);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();
	SetMainWindowText("RPG(‰¼Ì)");

	Parent* parent = new Parent();

	while (!ProcessMessage() && !Input_ESCAPE())
	{
		ClearDrawScreen();

		parent->update();
		parent->draw();

		ScreenFlip();
	}

	InitGraph();

	DxLib_End();
	return 0;
}