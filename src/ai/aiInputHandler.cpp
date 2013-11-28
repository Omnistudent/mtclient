
#include "game.h"
#include "ai/aiInputHandler.h"
	AIInputHandler::AIInputHandler()
	{
		leftdown = false;
		rightdown = false;
		leftclicked = false;
		rightclicked = false;
		leftreleased = false;
		rightreleased = false;
		keydown.clear();
	}
	bool AIInputHandler::isKeyDown(const KeyPress &keyCode)
	{
		return keydown[keyCode];
	}
	bool AIInputHandler::  wasKeyDown(const KeyPress &keyCode)
	{
		return false;
	}
	v2s32 AIInputHandler:: getMousePos()
	{
		v2s32 mousep = v2s32(0,0);
		return mousep;
	}
	void AIInputHandler:: setMousePos(s32 x, s32 y)
	{
		mousepos = v2s32(0,0);
	}

	bool AIInputHandler:: getLeftState()
	{
		return false;
		//return leftdown;
	}
	bool AIInputHandler:: getRightState()
	{
		return false;
		//return rightdown;
	}

	bool AIInputHandler:: getLeftClicked()
	{
		return false;
		//return leftclicked;
	}
	bool AIInputHandler:: getRightClicked()
	{
		return false;
		//return rightclicked;
	}
	void AIInputHandler:: resetLeftClicked()
	{
		//leftclicked = false;
	}
	void AIInputHandler:: resetRightClicked()
	{
		//rightclicked = false;
		//rightclicked = false;
	}

	bool AIInputHandler:: getLeftReleased()
	{
		//return leftreleased;
		return false;
	}
	bool AIInputHandler:: getRightReleased()
	{
		return false;
		//return rightreleased;
	}
	void AIInputHandler:: resetLeftReleased()
	{
		leftreleased = false;
	}
	void AIInputHandler:: resetRightReleased()
	{
		rightreleased = false;
	}

	s32 AIInputHandler:: getMouseWheel()
	{
		return 0;
	}


//private:
//	KeyList keydown;
//	v2s32 mousepos;
//	v2s32 mousespeed;
//	bool leftdown;
//	bool rightdown;
//	bool leftclicked;
//	bool rightclicked;
//	bool leftreleased;
//	bool rightreleased;


