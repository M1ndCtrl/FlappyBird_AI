/*#include "Controller.h"
#include "Player.h"
#include "GameControl.h"
#include <Windows.h>
#include <iostream>

//0x44	D key
//0x51	Q key
//0x53	S key
//0x5A	Z key
//VK_ESCAPE
//VK_SPACE

void Controller::BeginPlay(GameControl* GameC)
{
	GC = GameC;
	APlayer = GC->GetPlayer();
}

void Controller::CheckInput()
{
	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		APlayer->SetVelocity(-1 * VelocityChange);
		Beep(1000,10);
		//std::cout << "space key is down.";
	}

	if (GetKeyState(VK_ESCAPE) & 0x8000)
	{
		GC->Stop();
		//std::cout << "esc key is down.";
	}
}

int Controller::GetInput()
{
	return Input;
}

void Controller::ClearInput()
{
	Input = 0;
}*/




#include "Controller.h"
#include "Player.h"
#include "GameControl.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <random>
#include <sstream>



//0x44	D key
//0x51	Q key
//0x53	S key
//0x5A	Z key
//VK_ESCAPE
//VK_SPACE

void Controller::BeginPlay(GameControl* GameC)
{
	GC = GameC;
	/*APlayer = new Player;
	PlayerActive = true;

	APlayer->BeginPlay(Ctrl);

	AController = Ctrl;*/

	AWall = GC->GetWall();
	AWall2 = GC->GetWall2();
	APlayer = GC->GetPlayer();

	LoadModel();

	//ChangeParameters();
}





void Controller::SafeModel()
{
	unsigned int NewScore = GC->GetScore();
	//if (NewScore >= OldScore)
	//{

	std::vector<float>OutputList;
	OutputList.push_back(NewScore);
	OutputList.push_back(ParametersX);
	OutputList.push_back(ParametersY);

	for (int i = 0; i < Parameters.size(); ++i)
	{
		for (int j = 0; j < Parameters[i].size(); ++j)
		{
			OutputList.push_back(Parameters[i][j]);
		}
	}


	std::ofstream file("AIValues.txt");
	if (file.is_open())
	{
		for (const float& num : OutputList)
		{
			file << num << " ";
		}



		//file << a << " " << b << " " << c << " " << d << " " << e << " " << f << " "
			//<< g << " " << NewScore << " " << "\n";
		file.close();
	}
	else
	{
		std::cerr << "Error: Unable to open file for saving model\n";
	}
	//}
}

int Controller::GetHighScore()
{
	return OldScore;
}

/*void Controller::PlayerDead()
{
	unsigned int Score = GC->GetScore();
	GC->AddScore(ScoreCouple(Score, AController));
	delete APlayer;
	PlayerActive = false;
	//std::cout << Score << " ";
}*/

/*GameControl* Controller::GetGC()
{
	return GC;
}*/

//void Controller::AddPlayerGravity()
//{
//	if (PlayerActive)
//	{
//		APlayer->Gravity();
//	}
//}

void Controller::LoadModel()
{
	std::ifstream file("AIValues.txt");

	if (file.is_open())
	{
		std::string line;
		std::getline(file, line);

		// Close the file
		file.close();


		std::istringstream iss(line);
		float Number;
		while (iss >> Number)
		{
			InputList.push_back(Number);
		}
		OldScore = InputList[0];
		ParametersX = InputList[1];
		ParametersY = InputList[2];


		if (ParametersX <= 0)
		{
			ParametersX = 7;
		}
		if (ParametersY <= 0)
		{
			ParametersY = 3;
		}


		int count = 3;

		for (int i = 0; i < ParametersY; ++i)
		{
			std::vector<float> empty{};
			Parameters.push_back(empty);


			for (int j = 0; j < ParametersX; ++j)
			{
				//float Num = InputList[count] + GenerateRandomChange();


				float num = InputList[count];

				Parameters[i].push_back(num);
				++count;


			}
		}


		std::vector<float> empty{};
		Parameters.push_back(empty);

		Parameters[3].push_back(InputList[count]);

	}
	else
	{
		std::cerr << "Error: Unable to open file for saving model\n";
	}
}

float Controller::GenerateRandomChange()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	//std::uniform_int_distribution<> distrib(-1,1);
	std::uniform_real_distribution<float> distrib(-1 * ChangeAmount, ChangeAmount);

	float RandomValue = distrib(gen);


	return RandomValue;
}

void Controller::ChangeParameters()
{

	for (int i = 0; i < Parameters.size(); ++i)
	{
		for (int j = 0; j < Parameters[i].size(); ++j)
		{
			Parameters[i][j] += GenerateRandomChange();
		}
	}

}

float Controller::CheckNode(std::vector<int>Values, std::vector<float>ParameterList, float Output)
{
	//calculate
	float Sum{ 0 };
	for (int i = 0; i < Values.size(); ++i)
	{
		ParameterList[i] *= Values[i];
		Sum += ParameterList[i];
	}
	Sum += ParameterList[ParameterList.size() - 1];

	//check
	if (Sum <= 0)
	{
		return Output;
	}
	else {
		return 0.0f;
	}


}





void Controller::CheckInput()
{
	

	//int Xp = APlayer->GetX();
	int Yp = APlayer->GetY();
	int Xw1 = AWall->GetX();
	int Yw1 = AWall->GetY();
	int Xw2 = AWall2->GetX();
	int Yw2 = AWall2->GetY();
	

	float Jump{ 0 };
	std::vector<int> Values = { Yp,Xw1,Yw1,Xw2,Yw2 };

	for (int i = 0; i < Parameters.size() - 1; ++i)
	{
		std::vector<float> NoWeight(Parameters[i].begin() + 1, Parameters[i].begin() + 6 + 1);
		Jump += CheckNode(Values, NoWeight, Parameters[i][0]);
	}
	if (Jump <= Parameters[Parameters.size() - 1][0])
	{
		APlayer->SetVelocity(-1 * VelocityChange);
		//std::cout << "jump" << std::endl;
	}






	//float Jump = a * Xp + b * Yp + c + Xw1 + d * Yw1 + e * Xw2 + f * Yw2 + g;

	/*
	if (Jump<=0)
	{
		APlayer->SetVelocity(-1 * VelocityChange);
		//std::cout << "jump" << std::endl;
	}
	*/

	/*
	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		APlayer->SetVelocity(-1 * VelocityChange);

		//Beep(1000,10);
		//std::cout << "space key is down.";
	}*/

	if (GetKeyState(VK_ESCAPE) & 0x8000)
	{
		//GC->SetEsc();
		GC->Stop();
		//std::cout << "esc key is down.";
	}
}




