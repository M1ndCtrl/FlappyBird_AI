/*#pragma once
#include <queue>

class GameControl;
class Player;

class Controller
{
public:
	void CheckInput();
	void BeginPlay(GameControl* GameC);
	int GetInput();
	void ClearInput();
private:
	int Input;
	GameControl* GC;
	Player* APlayer;
	int VelocityChange{ 2 };
};*/

#pragma once
#include <queue>
#include <iostream>


class GameControl;
class Player;
class Wall;

class Controller
{
public:
	void CheckInput();
	void BeginPlay(GameControl* GameC);
	void SafeModel();
	int GetHighScore();
	//void PlayerDead();
	//GameControl* GetGC();
	//void AddPlayerGravity();

private:
	int Input;
	GameControl* GC;
	Player* APlayer;
	Wall* AWall;
	Wall* AWall2;
	Controller* AController;
	int VelocityChange{ 2 };
	bool PlayerActive{ false };

	/*
	aXp + bYp
	+ cXw1 + dYw1
	+ eXw2 + fYw2
	+ g = 0


	float a  {0};
	float b  {0};
	float c  {0};
	float d  {0};
	float e  {0};
	float f  {0};
	float g  {0};
	*/

	/*
	a,b,c,d,e,f
	a,b,c,d,e,f
	a,b,c,d,e,f
	*/

	std::vector<std::vector<float>> Parameters;
	std::vector < float> InputList;

	std::vector<float>AllAIValues;
	int ParametersX;
	int ParametersY;

	unsigned int OldScore{};

	void LoadModel();

	float GenerateRandomChange();

	void ChangeParameters();

	float ChangeAmount{ 1 };

	float CheckNode(std::vector<int>Values, std::vector<float>ParameterList, float Output);



};



