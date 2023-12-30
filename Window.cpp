#include <iostream>
#include "Window.h"
#include <algorithm>
#include "Player.h"
#include "Wall.h"
#include <windows.h> 



//get functions
int Window::GetHeight()
{
	return Height;
}

LPCSTR Window::GetName()
{
	return WindowName;
}

std::vector<Location> Window::GetWallLocations()
{
	return WallLocations;
}

int Window::GetWidth()
{
	return Width;
}



std::vector<Location> Window::GetAllLocations()
{
	return AllLocations;
}

//Set functions
void Window::SetSize()
{
	//LPCSTR WindowName = "SmallGame";
	HWND cmdWindow = FindWindowA(nullptr, WindowName);
	SetForegroundWindow(cmdWindow);
	HWND hwnd = GetForegroundWindow();
	ShowWindow(hwnd, SW_MAXIMIZE);
	std::cout << "setting window";
	Sleep(1000);
	system("cls");
	RECT desktopRect;
	GetWindowRect(hwnd, &desktopRect);

	const int screenWidth = desktopRect.right - desktopRect.left;
	const int screenHeight = desktopRect.bottom - desktopRect.top;

	//Width = round(screenWidth / 10.1);
	//Height = round(screenHeight / 22);

	buffer = new char* [Height];
	for (int i = 0; i < Height; ++i)
	{
		buffer[i] = new char[Width];
	}
	for (int row = 0; row < Height; ++row) {
		for (int col = 0; col < Width; ++col) {
			buffer[row][col] = ' ';
		}
	}

}

void Window::SetName(LPCSTR Name)
{
	WindowName = Name;
}

void Window::RemoveWallLocation()
{
	WallLocations.erase(WallLocations.begin());

}




//Begin functions
void Window::BeginPlay(GameControl* GameC)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(consoleHandle, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);

	SetConsoleTitleA(WindowName);
	Window::SetSize();
	system("cls");

	GC = GameC;
	APlayer = GC->GetPlayer();
	AWall = GC->GetWall();
	system("Color 03");

}

//Debug function
void Window::CheckWindow()
{
	//system("cls");
	std::cout << std::endl << std::endl << "  ";
	for (int row = 1; row < Height; ++row) {
		for (int col = 1; col < Width; ++col) {

			std::cout << "X";
		}
		std::cout << std::endl << "  ";
	}
}

//Draw functions
void Window::Draw()
{
	//system("cls");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD topLeft = { 0, 0 };
	SetConsoleCursorPosition(hConsole, topLeft);
	Window::DrawToBuffer();

	Window::DrawToScreen();
	//Sleep(50);


}

void Window::AddWallLocation(Location loc)
{
	WallLocations.push_back(loc);
}

void Window::DrawToBuffer()
{
	
	for (const auto& loc : WallLocations)
	{
		for (int i = loc.x - 5; i < loc.x; i++)
		{
			for (int j = 0; j < loc.y - 5; j++)
			{
				buffer[j][i] = '|';
			}
			for (int j = loc.y + 5; j < Height; j++)
			{
				buffer[j][i] = '|';
			}
		}
	}
	const Location loc = APlayer->GetPlayerLoc();//Location({APlayer->GetX(),APlayer->GetY(),'P'});
	buffer[loc.y][loc.x] = '@';
	buffer[loc.y][loc.x + 1] = '<';
	//const Location WallLoc = Location({ AWall->GetX(),AWall->GetY(),'W' });
	
	/*AllLocations = WallLocations;
	AllLocations.push_back(loc);*/
}

void Window::DrawToScreen()
{

	for (int i = 0; i < Width + 2; ++i)
	{
		std::cout << "#";
	}
	std::cout << std::endl;
	for (int i = 0; i < Height; ++i) {
		for (int j = 0; j < Width; ++j) {

			
			std::cout << buffer[i][j];
			
		}
		std::cout << std::endl;
	}
	for (int i = 0; i < Width + 1; ++i)
	{
		std::cout << "#";
	}
	for (int row = 0; row < Height; ++row) {
		for (int col = 0; col < Width; ++col) {
			buffer[row][col] = ' ';
		}
	}
	
	const Location Wallloc = Location({ AWall->GetX(),AWall->GetY(),'W' });
	

}



//Stop functions
void Window::Stop()
{
	system("cls");
	for (int i = 0; i < Height; ++i) {
		delete[] buffer[i];
	}
	delete[] buffer;
	std::cout << "buffer deleted" << std::endl;

}

// other
bool Window::AreLocationsEqual(const Location& loc1, const Location& loc2)
{
	return loc1.x == loc2.x && loc1.y == loc2.y;
}

/*	for (int row = 1; row < Height; ++row) {
		for (int col = 1; col < Width; ++col) {

			Location TargetLocation(col,row );
			auto it = std::find_if(PlayerLocations.begin(), PlayerLocations.end(), [this,&TargetLocation](const Location& loc) {
				return Window::AreLocationsEqual(loc, TargetLocation);
				});

			if (it != PlayerLocations.end()) {
				buffer[TargetLocation.y][TargetLocation.x] = '#';
			}
			else {
				buffer[TargetLocation.y][TargetLocation.x] = ' ';
			}
		}

	}*/
