#pragma once
#include "../Map/MapChip.h"
#include "../Collision/Collision.h"
#include "Enemy.Parameter.h"

// 敵のサイズ
#define SWORD_ENEMY_WIDTH	(72.0f)
#define SWORD_ENEMY_HEIGHT	(72.0f)
#define SWORD_ENEMY_RADIUS	(36.0f)

// 矩形判定のサイズ
constexpr auto SWORD_ENEMY_BOX_COLLISION_WIDTH = (45);
constexpr auto SWORD_ENEMY_BOX_COLLISION_HEIGHT = (50);

void InitSwordEnemy();
void StartSwordEnemy();
void LoadSwordEnemy();
void StepSwordEnemy();
void UpdateSwordEnemy();
void DrawSwordEnemy();
void FinSwordEnemy();

SwordEnemyData* GetSwordEnemy();

// 当たり判定
void SwordEnemyHitNormalBlockX(MapChipData mapChipData);
void SwordEnemyHitNormalBlockY(MapChipData mapChipData);

void BulletHitSwordEnemy();