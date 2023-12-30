#pragma once
#include "GameControl.h"



//class GameControl;
class Window;


class Player
{
private:
	int x{ 30 };
	int y{ 10 };
	Location PlayerLoc{ 30,5,'P' };
	int Velocity{ 0 };
	GameControl* GC;
	Window* AWindow;
	Wall* AWall;
	int DeltaY{ 1 };
	void CheckLocation();

public:
	void AddY(int i);
	void AddX(int i);
	int GetY();
	int GetX();
	Location GetPlayerLoc();
	void BeginPlay(GameControl* GameC);
	void Gravity();
	void SetVelocity(int vel);
};

