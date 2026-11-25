#include "EnemyManager.h"
#include "../Enemy/Nomal.h"
#include "../Enemy/Sword.h"

void InitEnemy()
{
	InitNomal();
	InitSword();
}

void StartEnemy()
{
	StartNomal();
	StartSword();
}

void LoadEnemy()
{
	// 各エネミーをロード
	LoadNomal();
	LoadSword();
}

void StepEnemy()
{
	// 各エネミーをステップ
	StepNomal();
	StepSword();
}

void UpdateEnemy()
{
	// 各エネミーを更新
	UpdateNomal();
	UpdateSword();
}

void DrawEnemy()
{
	// 各エネミーを描画
	DrawNomal();
	DrawSword();
}

void FinEnemy()
{
	// 各エネミーを終了
	FinNomal();
	FinSword();
}