#include "KeyInput.h"
#include "DXLib.h"

const bool toBoolean[2]{ false, true };


bool Input_Z()
{
	return toBoolean[CheckHitKey(KEY_INPUT_Z)];
}

bool Input_X()
{
	return toBoolean[CheckHitKey(KEY_INPUT_X)];
}

bool Input_C()
{
	return toBoolean[CheckHitKey(KEY_INPUT_C)];
}

bool Input_V()
{
	return toBoolean[CheckHitKey(KEY_INPUT_V)];
}

bool Input_W()
{
	return toBoolean[CheckHitKey(KEY_INPUT_W)];
}

bool Input_A()
{
	return toBoolean[CheckHitKey(KEY_INPUT_A)];
}

bool Input_S()
{
	return toBoolean[CheckHitKey(KEY_INPUT_S)];
}

bool Input_D() 
{
	return toBoolean[CheckHitKey(KEY_INPUT_D)];
}

bool Input_UP()
{
	return toBoolean[CheckHitKey(KEY_INPUT_UP)];
}

bool Input_DOWN() 
{
	return toBoolean[CheckHitKey(KEY_INPUT_DOWN)];
}

bool Input_RIGHT()
{
	return toBoolean[CheckHitKey(KEY_INPUT_RIGHT)];

}

bool Input_LEFT()
{
	return toBoolean[CheckHitKey(KEY_INPUT_LEFT)];
}

bool Input_RETURN()
{
	return toBoolean[CheckHitKey(KEY_INPUT_RETURN)];
}

bool Input_BACK()
{
	return toBoolean[CheckHitKey(KEY_INPUT_BACK)];
}

bool Input_ESCAPE()
{
	return toBoolean[CheckHitKey(KEY_INPUT_ESCAPE)];
}

