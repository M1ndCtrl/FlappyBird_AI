#pragma once
#include <windows.h>
#include "GameControl.h"
#include <vector>

class GameControl;
class Coin;
class Wall;


//1550
//830

class Window
{
public:
	//get functions:
	int GetHeight();
	int GetWidth();
	LPCSTR GetName();
	std::vector<Location> GetWallLocations();
	std::vector<Location> GetAllLocations();

	//set functions
	void SetSize();
	void SetName(LPCSTR Name);
	void RemoveWallLocation();



	//other functions
	void BeginPlay(GameControl* GameC);
	void Draw();
	void AddWallLocation(Location loc);
	void CheckWindow();
	void Stop();
	bool AreLocationsEqual(const Location& loc1, const Location& loc2);

private:
	LPCSTR WindowName;
	GameControl* GC;
	std::vector<Location> WallLocations;
	std::vector<Location> AllLocations;

	int Width{153};
	int Height{37};
	void DrawToBuffer();
	void DrawToScreen();
	char** buffer;

	Player* APlayer;
	Wall* AWall;
};

