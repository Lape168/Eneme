#pragma once
#include "DxLib.h"
#include "BulletParameter.h"

// íeëSëÃÇÃèàóù
void InitBullet();
void LoadBullet();
void StepBullet();
void UpdateBullet();
void DrawBullet();
void FinBullet();

// íeî≠éÀ
void RequestFireBullet(StraightBulletType type, int life, float posX, float posY, float moveX, float moveY, BoxCollision boxcollision, BulletCollisionTag tag);