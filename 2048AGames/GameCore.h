#pragma once
#include "Direction.h"
#include <stdlib.h>
#include <windows.h>
#define MAPWIDE 4
#define MAPHEIGHT 4
#define RANDOM(__begin,__end) ((rand()+__begin)%__end)	//	�������ֵ

class GameCore 
{
public:
	GameCore();
	GameCore(int rNumber);
	~GameCore();

	int* GetMap();
	/************************************************************************/
	/* ���ܣ��Ե�ͼ����Ԫ�ؽ����ƶ�����			                            */
	/* ����������ö�٣�Direction��											*/
	/************************************************************************/
	void Movement(Direction dir);
	//���ͼ�������Ͷ�������
	void Randomizer();
	//��Ϸ�Ƿ�ʧ��
	bool IsFail();
	//���µ�ͼ����
	void Print();
	
private:
	//�ж��Ƿ�����ں� ���ڷ���true
	bool IsThereFusion();
	//�ж��Ƿ���ڿհ� ���ڷ���true
	bool IsThereBlank();
	//�����ں� 
	void MoveUp(int mapArray[MAPWIDE][MAPHEIGHT]);
	//�����ں�
	void MoveDown(int mapArray[MAPWIDE][MAPHEIGHT]);
	//�����ں�
	void MoveLeft(int mapArray[MAPWIDE][MAPHEIGHT]);
	//�����ں�
	void MoveRight(int mapArray[MAPWIDE][MAPHEIGHT]);
	/************************************************************************/
	/* ���ܣ�������Ԫ����ͬ��Ԫ�غϲ�������                                 */
	/* ������һά����													    */
	/************************************************************************/
	bool isNormalPoints = true;
	void DataFusion(int array[]);
	/************************************************************************/
	/* ���ܣ�������Ԫ��Ϊ���Ԫ�������ƶ�                                   */
	/* ������һά����													    */
	/************************************************************************/
	void ZeroSuppression(int array[]);
	//��Ϸ����
	int gameArray[MAPHEIGHT][MAPWIDE];
	//��ʼ�������
	int initNumber;
	//�Ƿ��ƶ� �ɹ� �ɹ�Ϊtrue
	bool isChanged;
	//��Ϸ������
	int score;

protected:
	
};
