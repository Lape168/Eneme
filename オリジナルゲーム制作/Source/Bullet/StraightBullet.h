#pragma once
#include "BulletParameter.h"

// 各ロジックごとの関数
void InitStraightBullet();
void LoadStraightBullet();
void StepStraightBullet();
void UpdateStraightBullet();
void DrawStraightBullet();
void FinStraightBullet();

// 発射関数（必ずBulletManagerでしか呼ばないこと）
void FireStraightBullet(StraightBulletType type, int life, float posX, float posY, float moveX, float moveY, float radius, BulletCollisionTag tag);

// 弾取得
StraightBulletData* GetStraightBullet();