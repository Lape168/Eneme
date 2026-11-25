#include "EnemyManager.h"
#include "../Enemy/Nomal.h"
#include "../Enemy/SwordEnemy.h"

void InitEnemy()
{
	InitNomalEnemy();
	InitSwordEnemy();
}

void StartEnemy()
{
	StartNomalEnemy();
	StartSwordEnemy();
}

void LoadEnemy()
{
	// 各エネミーをロード
	LoadNomalEnemy();
	LoadSwordEnemy();
}

void StepEnemy()
{
	// 各エネミーをステップ
	StepNomalEnemy();
	StepSwordEnemy();
}

void UpdateEnemy()
{
	// 各エネミーを更新
	UpdateNomalEnemy();
	UpdateSwordEnemy();
}

void DrawEnemy()
{
	// 各エネミーを描画
	DrawNomalEnemy();
	DrawSwordEnemy();
}

void FinEnemy()
{
	// 各エネミーを終了
	FinNomalEnemy();
	FinSwordEnemy();
}