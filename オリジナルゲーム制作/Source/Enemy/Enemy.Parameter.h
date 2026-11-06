#pragma once
#include "DxLib.h"

enum EnemyType
{
	NOMAL,
	SWORD,
	BOMB,
};

struct NomalEnemyData
{
	bool active;
	int handle;
	VECTOR pos;
	VECTOR move;
};