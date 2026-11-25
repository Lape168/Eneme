#pragma once
#include "../Map/MapChip.h"
#include "../Collision/Collision.h"
#include "Enemy.Parameter.h"

// 敵のサイズ
#define NOMAL_ENEMY_WIDTH	(72.0f)
#define NOMAL_ENEMY_HEIGHT	(72.0f)
#define NOMAL_ENEMY_RADIUS	(36.0f)

// 矩形判定のサイズ
constexpr auto NOMAL_ENEMY_BOX_COLLISION_WIDTH = (45);
constexpr auto NOMAL_ENEMY_BOX_COLLISION_HEIGHT = (50);

void InitNomalEnemy();
void StartNomalEnemy();
void LoadNomalEnemy();
void StepNomalEnemy();
void UpdateNomalEnemy();
void DrawNomalEnemy();
void FinNomalEnemy();

NomalEnemyData* GetNomalEnemy();

// 当たり判定
void NomalEnemyHitNormalBlockX(MapChipData mapChipData);
void NomalEnemyHitNormalBlockY(MapChipData mapChipData);

void BulletHitNomalEnemy();