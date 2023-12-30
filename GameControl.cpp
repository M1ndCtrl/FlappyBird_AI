#include "GameControl.h"
#include <iostream>
#include "Window.h"
#include "Controller.h"
#include "Player.h"
#include <chrono>
#include<thread>
#include <fstream>
#include "Wall.h"








int main()
{
	GameControl GCObj;
	GameControl* GC = &GCObj;

	GC->StartUp(GC);
	return 0;
}
void GameControl::StartUp(GameControl* GameC)
{
	GC = GameC;

	//variabelen
	LPCSTR WindowName{ "SmallGame" };



	//create objects
	Window WindowObj;
	AWindow = &WindowObj;
	Player PlayerObj;
	APlayer = &PlayerObj;
	Controller ControllerObj;
	AController = &ControllerObj;
	Wall WallObj;
	AWall = &WallObj;
	Wall WallObj2;
	AWall2 = &WallObj2;

	


	//Setup commands
	AWindow->SetName(WindowName);
	AWindow->BeginPlay(GC);
	APlayer->BeginPlay(GC);
	AController->BeginPlay(GC);
	AWall->BeginPlay(GC);

	/*while (StopVar == 0)
	 {

		AController->CheckInput();
		APlayer->Gravity();
		AWindow->Draw();
		Sleep(10);

	}*/


	//start Input thread loop
	//std::thread InputThread(&GameControl::InputLoop, this);

	//start GameLoop
	GameControl::GameLoop();

	//wait until both stopped
	//InputThread.join();

	system("cls");
	system("Color 07");
	std::cout << "You're dead" << std::endl;
	//GameControl::CompareScore();
	Score = 2*LoopCount * 3 / AWindow->GetWidth()+15;
	//Score = LoopCount;
	std::cout << "your score is: " << Score  << std::endl;
	Sleep(1000);
	AWindow->Stop();
	std::cout << "Closing Game" << std::endl;
	Sleep(500);
}

void GameControl::Stop()
{
	StopVar = 1;
}




void GameControl::GameLoop()
{
	while (StopVar == 0)
	{
		//auto Start = std::chrono::high_resolution_clock::now();
		Sleep(50);

		if (StopVar == 0)
		{
			AController->CheckInput();
		}
		//game stuff
		//AController->CheckInput();
		if (StopVar == 0)
		{
			APlayer->Gravity();
		}
		AWall->MoveWall();
		LoopCount++;
		if (LoopCount == (AWindow->GetWidth()/6)) 
		{
			AWall2->BeginPlay(GC);
		}
		else if (LoopCount > (AWindow->GetWidth() / 6))
		{
			AWall2->MoveWall();
		}


		AWindow->Draw();



		/*auto End = std::chrono::high_resolution_clock::now();
		auto ElapsedMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(End - Start).count();
		int SleepDuration = 1000 / TargetFrameRate - static_cast<int>(ElapsedMilliseconds);
		if (SleepDuration > 0)
		{
			Sleep(SleepDuration);
		}*/
	}

}

void GameControl::InputLoop()
{
	while (StopVar == 0)
	{
		AController->CheckInput();
		Sleep(50);
	}
}

void GameControl::CompareScore()
{


}

Player* GameControl::GetPlayer()
{
	return APlayer;
}

Window* GameControl::GetWindow()
{
	return AWindow;
}

GameControl* GameControl::GetGameControl()
{
	return GC;
}

Wall* GameControl::GetWall()
{
	return AWall;
}

Wall* GameControl::GetWall2()
{
	return AWall2;
}

int GameControl::GetScore()
{
	return LoopCount;
}
