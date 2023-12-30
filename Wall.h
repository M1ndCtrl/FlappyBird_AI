#pragma once

class GameControl;
class Window;


class Wall {
private:
	GameControl* GC;
	Window* AWindow;
	int GapHeight;
	int WindowHeight;
	int x{0};

public:
	void BeginPlay(GameControl* GameC);
	void SetGapHeight();
	int GetX();
	int GetY();
	void MoveWall();
};