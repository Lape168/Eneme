#pragma once
#include "DxLib.h"
#include "../Collision/Collision.h"

enum EnemyType
{
	NOMAL,
	SWORD,
	BOMB,
};

struct NomalEnemyData
{
	bool active;
	bool isTurn;
	bool isAir;
	int handle;
	VECTOR pos;
	VECTOR move;
	BoxCollision boxCollision;
};