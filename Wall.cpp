#include "Wall.h"
#include "GameControl.h"
#include "Window.h"
#include <cstdlib> 
#include <ctime> 

void Wall::BeginPlay(GameControl* GameC)
{
	GC = GameC;
	AWindow = GC->GetWindow();
	WindowHeight = AWindow->GetHeight();
	srand((unsigned)time(0));
	SetGapHeight();
	AWindow->AddWallLocation(Location({ x,GapHeight,'W' }));



	
}

void Wall::SetGapHeight()
{
	GapHeight = rand() % (WindowHeight-10) + 5;
	x = AWindow->GetWidth()-1;
	AWindow->AddWallLocation(Location({ x,GapHeight,'W' }));
	AWindow->RemoveWallLocation();
	
}

int Wall::GetX()
{
	return x;
}

int Wall::GetY()
{
	return GapHeight;
}

void Wall::MoveWall()
{
	if (x-5 > 0)
	{
		x -= 3;
		AWindow->AddWallLocation(Location({ x,GapHeight,'W' }));
		AWindow->RemoveWallLocation();

	}
	else {
		SetGapHeight();
	}
}
