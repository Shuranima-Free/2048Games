// 2048AGames.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "GameCore.h"
#include <conio.h>
using namespace std;

//输入键位和游戏键位的转换
void ASpecializedTransformation(char ch);
//游戏对象
GameCore *game;
int main(int argc, char **argv)
{
	game = new GameCore(2);
	while (true)
	{
		game->Print();
		game->Print();
		char ch = _getch();
		if (ch == 'q')
		{
			break;
		}
		ASpecializedTransformation(ch);
		if (game->IsFail())
		{
			printf(("亲爱的朋友，你挂了!\n"));
			break;
		}
		if (ch == 'w' || ch == 's' || ch == 'a' || ch == 'd')
		{
			game->Randomizer();
		}
	}
	delete game;

	getchar();
}
void ASpecializedTransformation(char ch)
{
	switch (ch)
	{
	case 'w':
		game->Movement(Direction::up);
		break;
	case 's':
		game->Movement(Direction::down);
		break;
	case 'a':
		game->Movement(Direction::left);
		break;
	case 'd':
		game->Movement(Direction::right);
		break;
	}
}
