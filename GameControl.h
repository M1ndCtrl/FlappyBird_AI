#pragma once
#include "Wall.h"

class Window;
class Player;
class Window;
class Controller;
class Coin;
class Wall;

struct Location {
	int x;
	int y;
	char what;
	Location(int x, int y, char what) : x(x), y(y), what(what) {}
};


class GameControl {
public:
	Player* GetPlayer();
	Window* GetWindow();
	GameControl* GetGameControl();
	Wall* GetWall();
	Wall* GetWall2();

	int GetScore();

	void StartUp(GameControl* GameC);
	void Stop();


private:
	Player* APlayer;
	Window* AWindow;
	Controller* AController;
	GameControl* GC;
	Wall* AWall;
	Wall* AWall2;

	int StopVar{ 0 };
	void GameLoop();
	void InputLoop();
	void CompareScore();
	int HighScore;
	unsigned int LoopCount{ 0 };
	unsigned int Score{};
	const int TargetFrameRate{ 10 };

};
