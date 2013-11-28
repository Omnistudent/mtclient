#include "game.h"
class AIInputHandler : public InputHandler
{

public:
	AIInputHandler();
	virtual bool isKeyDown(const KeyPress &keyCode);
	virtual bool wasKeyDown(const KeyPress &keyCode);
	virtual v2s32 getMousePos();
	virtual void setMousePos(s32 x, s32 y);
	virtual bool getLeftState();
	virtual bool getRightState();
	virtual bool getLeftClicked();
	virtual bool getRightClicked();
	virtual void resetLeftClicked();
	virtual void resetRightClicked();
	virtual bool getLeftReleased();
	virtual bool getRightReleased();
	virtual void resetLeftReleased();
	virtual void resetRightReleased();

	virtual s32 getMouseWheel();


private:
	KeyList keydown;
	v2s32 mousepos;
	v2s32 mousespeed;
	bool leftdown;
	bool rightdown;
	bool leftclicked;
	bool rightclicked;
	bool leftreleased;
	bool rightreleased;

};
