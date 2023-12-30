#include "Player.h"
#include "Window.h"
#include "GameControl.h"
#include <windows.h> 
#include"iostream"






void Player::CheckLocation()
{
	if (0 <= x && x <= AWindow->GetWidth() - 1 && 0 <= y && y <= AWindow->GetHeight() - 1)
	{
		
		for (Location loc : AWindow->GetWallLocations())
		{
			int WallX = loc.x;
			int WallY = loc.y;
			if (WallX-8 <= x && x <= WallX-3 && (0 <= y && y <= (WallY - 5) || (WallY + 5) <= y && y <= AWindow->GetHeight()))
			{
				//system("Color 42");
				
				GC->Stop();
			}
			else
			{
				PlayerLoc = { x,y,'P' };
			}
		}
	}
	else
	{
		//SetVelocity(0);
		//AddY(AWindow->GetHeight() - 1 - y);
		//system("cls");
		
		GC->Stop();
	}


}


void Player::AddY(int i)
{
	y += i;
	Player::CheckLocation();

}

void Player::AddX(int i)
{
	x += i;
}

int Player::GetY()
{
	return y;
}

int Player::GetX()
{
	return x;
}

Location Player::GetPlayerLoc()
{
	return PlayerLoc;
}

void Player::BeginPlay(GameControl* GameC)
{
	GC = GameC;
	AWindow = GC->GetWindow();
	AWall = GC->GetWall();

}





void Player::Gravity()
{
	AddY(Velocity);
	Velocity++;
	/*if (y >= AWindow->GetHeight()-2)
	{
		SetVelocity(0);
	}*/


}

void Player::SetVelocity(int vel)
{
	Velocity = vel;
}
