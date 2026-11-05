#pragma once
#include "DxLib.h"

enum EnemyType
{
	NOMAL,
	SWORD,
	BOMB,
};

struct EnemyData
{
	bool active;
	int handle;
	VECTOR pos;
	VECTOR move;
};