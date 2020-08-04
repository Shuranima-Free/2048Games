#pragma once
#include "Direction.h"
#include <stdlib.h>
#include <windows.h>
#define MAPWIDE 4
#define MAPHEIGHT 4
#define RANDOM(__begin,__end) ((rand()+__begin)%__end)	//	产生随机值

class GameCore 
{
public:
	GameCore();
	GameCore(int rNumber);
	~GameCore();

	int* GetMap();
	/************************************************************************/
	/* 功能：对地图数组元素进行移动操作			                            */
	/* 参数：方向枚举（Direction）											*/
	/************************************************************************/
	void Movement(Direction dir);
	//向地图数组随机投放随机数
	void Randomizer();
	//游戏是否失败
	bool IsFail();
	//更新地图函数
	void Print();
	
private:
	//判断是否存在融合 存在返回true
	bool IsThereFusion();
	//判断是否存在空白 存在返回true
	bool IsThereBlank();
	//向上融合 
	void MoveUp(int mapArray[MAPWIDE][MAPHEIGHT]);
	//向下融合
	void MoveDown(int mapArray[MAPWIDE][MAPHEIGHT]);
	//向左融合
	void MoveLeft(int mapArray[MAPWIDE][MAPHEIGHT]);
	//向右融合
	void MoveRight(int mapArray[MAPWIDE][MAPHEIGHT]);
	/************************************************************************/
	/* 功能：对数组元素相同的元素合并并消亡                                 */
	/* 参数：一维数组													    */
	/************************************************************************/
	bool isNormalPoints = true;
	void DataFusion(int array[]);
	/************************************************************************/
	/* 功能：对数组元素为零的元素往后移动                                   */
	/* 参数：一维数组													    */
	/************************************************************************/
	void ZeroSuppression(int array[]);
	//游戏数组
	int gameArray[MAPHEIGHT][MAPWIDE];
	//初始随机数量
	int initNumber;
	//是否移动 成功 成功为true
	bool isChanged;
	//游戏虽获分数
	int score;

protected:
	
};
