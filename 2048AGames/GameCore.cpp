#include "pch.h"
#include "GameCore.h"
#include <stdio.h>


GameCore::GameCore():initNumber(5), isChanged(true), score(0)
{
	int temp[MAPWIDE][MAPHEIGHT] = { 0 };
	memcpy(gameArray, temp, sizeof(int)*MAPWIDE*MAPHEIGHT);
	int i = 0;
	do 
	{
		Randomizer();
	} while (++i < initNumber);
}
GameCore::GameCore(int rNumber):isChanged(true), score(0)
{
	int temp[MAPWIDE][MAPHEIGHT] = { 0 };
	memcpy(gameArray, temp, sizeof(int)*MAPWIDE*MAPHEIGHT);
	int i = 0;
	do
	{
		Randomizer();
	} while (++i < rNumber);
}
GameCore::~GameCore()
{

}

int * GameCore::GetMap()
{
	return *gameArray;
}

void GameCore::Randomizer()
{
	int a = RANDOM(0, MAPWIDE);
	int b = RANDOM(0, MAPHEIGHT);
	if ((!IsThereBlank()) || (isChanged == false))
	{
		return;
	}
	while (true)
	{
		if (gameArray[a][b] == 0)
		{
			gameArray[a][b] = RANDOM(0, 10) == 0 ? 4 : 2;
			break;
		}
		a = RANDOM(0, MAPWIDE);
		b = RANDOM(0, MAPHEIGHT);
	}
}

bool GameCore::IsFail()
{
	if ((!IsThereBlank()) && (isChanged == false) && (!IsThereFusion()))
	{
		return true;
	}
	return false;
}

bool GameCore::IsThereFusion()
{
	int retainedMap[MAPWIDE][MAPHEIGHT] = { 0 };
	memcpy(retainedMap, gameArray, sizeof(int)*MAPWIDE*MAPWIDE);
	isNormalPoints = false;
	MoveUp(retainedMap);
	MoveDown(retainedMap);
	MoveLeft(retainedMap);
	MoveRight(retainedMap);
	for (int i = 0; i < MAPWIDE; ++i)
	{
		for (int j = 0; j < MAPHEIGHT; ++j)
		{
			if (retainedMap[i][j] != gameArray[i][j])
			{
				return true;
			}
		}
	}
	return false;
}

bool GameCore::IsThereBlank()
{
	for (int i = 0; i < MAPWIDE; ++i)
	{
		for (int j = 0; j < MAPHEIGHT; ++j)
		{
			if (gameArray[i][j] == 0)
			{
				return true;
			}
		}
	}

	return false;
}

void GameCore::Movement(Direction dir)
{
	isChanged = false;
	int retainedMap[MAPWIDE][MAPHEIGHT] = { 0 };
	memcpy(retainedMap, gameArray, sizeof(int)*MAPWIDE*MAPWIDE);
	isNormalPoints = true;
	switch (dir)
	{
	case Direction::up:
		MoveUp(gameArray);
		break;
	case Direction::down:
		MoveDown(gameArray);
		break;
	case Direction::right:
		MoveRight(gameArray);
		break;
	case Direction::left:
		MoveLeft(gameArray);
		break;
	}
	for (int i = 0; i < MAPWIDE; ++i)
	{
		for (int j = 0; j < MAPHEIGHT; ++j)
		{
			if (retainedMap[i][j] != gameArray[i][j])
			{
				isChanged = true;
			}
		}
	}
}

void GameCore::MoveUp(int mapArray[MAPWIDE][MAPHEIGHT])
{
	int array[MAPHEIGHT] = { 0 };
	for (int i = 0; i < MAPHEIGHT; ++i)
	{
		for (int a = 0; a < MAPWIDE; ++a)
		{
			array[a] = mapArray[a][i];
		}
		DataFusion(array);
		for (int b = 0; b < MAPWIDE; ++b)
		{
			mapArray[b][i] = array[b];
		}
	}
}

void GameCore::MoveDown(int mapArray[MAPWIDE][MAPHEIGHT])
{
	int array[MAPHEIGHT] = { 0 };
	for (int i = 0; i < MAPHEIGHT; ++i)
	{
		for (int a = MAPWIDE - 1; a >= 0; --a)
		{
			array[MAPWIDE - 1 - a] = mapArray[a][i];
		}
		DataFusion(array);
		for (int b = MAPWIDE - 1; b >= 0; --b)
		{
			mapArray[b][i] = array[MAPWIDE - 1 - b];
		}
	}
}

void GameCore::MoveLeft(int mapArray[MAPWIDE][MAPHEIGHT])
{
	int array[MAPWIDE] = { 0 };
	for (int i = 0; i < MAPWIDE; ++i)
	{
		for (int a = 0; a < MAPHEIGHT; ++a)
		{
			array[a] = mapArray[i][a];
		}
		DataFusion(array);
		for (int b = 0; b < MAPHEIGHT; ++b)
		{
			mapArray[i][b] = array[b];
		}
	}

}

void GameCore::MoveRight(int mapArray[MAPWIDE][MAPHEIGHT])
{
	int array[MAPWIDE] = { 0 };
	for (int i = 0; i < MAPWIDE; ++i)
	{
		for (int a = MAPHEIGHT - 1; a >= 0; --a)
		{
			array[MAPHEIGHT - 1 - a] = mapArray[i][a];
		}
		DataFusion(array);
		for (int b = MAPHEIGHT - 1; b >= 0; --b)
		{
			mapArray[i][b] = array[MAPHEIGHT - 1 - b];
		}
	}
}

void GameCore::DataFusion(int array[])
	{
		ZeroSuppression(array);

		for (int i = 0; i < MAPWIDE - 1; ++i)
		{
		if (array[i] != 0 && array[i] == array[i + 1])
		{
			array[i] = array[i] * 2;
			array[i + 1] = 0;
			if (isNormalPoints == true)
			{
				score += array[i];
			}
		}
	}
	ZeroSuppression(array);

}

void GameCore::ZeroSuppression(int array[])
{
	int idlePosition = 0;
	int temp[MAPWIDE] = {};
	for (int i = 0; i < MAPWIDE; ++i)
	{
		if (array[i] != 0)
		{
			temp[idlePosition++] = array[i];

		}
	}
	memcpy(array, temp, sizeof(int) * MAPWIDE);
}

void GameCore::Print()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);	//获取控制台句柄
	system("cls");
	SetConsoleTextAttribute(handle, FOREGROUND_RED);	//	设置输出颜色
	printf("score：%d\n", this->score);
	for (int i = 0; i < MAPHEIGHT; ++i)
	{
		for (int j = 0; j < MAPWIDE; ++j)
		{
			if (gameArray[i][j] != 0)
			{
				SetConsoleTextAttribute(handle, FOREGROUND_RED);	//	设置输出颜色
			}
			else
			{
				SetConsoleTextAttribute(handle, FOREGROUND_BLUE);
			}
			printf("%d\t", gameArray[i][j]);
		}
		printf("\n");
		printf("\n");
	}
	printf("\n");
}