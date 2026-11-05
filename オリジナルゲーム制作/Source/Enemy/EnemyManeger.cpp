#include "EnemyManager.h"
#include "../Enemy/Nomal.h"

int g_EnemySpawnTimer = 0;

void InitEnemy()
{
	// エネミー出現タイマーを初期化
	g_EnemySpawnTimer = 0;

	InitNomal();
}

void LoadEnemy()
{
	// 各エネミーをロード
	LoadNomal();
}

void StepEnemy()
{
	// 各エネミーをステップ
	StepNomal();
}

void UpdateEnemy()
{
	// 各エネミーを更新
	UpdateNomal();
}

void DrawEnemy()
{
	// 各エネミーを描画
	DrawNomal();
}

void FinEnemy()
{
	// 各エネミーを終了
	FinNomal();
}