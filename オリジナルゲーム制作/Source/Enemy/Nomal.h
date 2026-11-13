#pragma once
#include "../Map/MapChip.h"
#include "../Collision/Collision.h"
#include "Enemy.Parameter.h"

// “G‚ÌƒTƒCƒY
#define NOMAL_ENEMY_WIDTH	(72.0f)
#define NOMAL_ENEMY_HEIGHT	(72.0f)
#define NOMAL_ENEMY_RADIUS	(36.0f)

void InitNomal();
void StartNomal();
void LoadNomal();
void StepNomal();
void UpdateNomal();
void DrawNomal();
void FinNomal();

NomalEnemyData* GetNomalEnemy();

// “–‚½‚è”»’è
void NomalEnemyHitNormalBlockX(MapChipData mapChipData);
void NomalEnemyHitNormalBlockY(MapChipData mapChipData);

void BulletHitEnemy();