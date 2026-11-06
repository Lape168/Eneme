#include "Nomal.h"
#include "../Enemy/Enemy.Parameter.h"

NomalEnemyData g_NomalEnemyData = { 0 };

void InitNomal()
{
	g_NomalEnemyData.handle = 0;
	g_NomalEnemyData.pos.x = 0;
	g_NomalEnemyData.pos.y = 0;
	g_NomalEnemyData.move.x = 0;
	g_NomalEnemyData.move.y = 0;
}

void LoadNomal()
{
	g_NomalEnemyData.handle = LoadGraph("Data/Enemy/EnemyR.png");
}

void StepNomal()
{

}

void UpdateNomal()
{

}

void DrawNomal()
{

}

void FinNomal()
{

}
