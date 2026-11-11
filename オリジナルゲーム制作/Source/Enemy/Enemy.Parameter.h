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

struct EnemyMotion
{
	int walkR;									//右方向の移動
	int jump_upR;								//右方向のジャンプの上り
	int jump_fallR;								//右方向のジャンプの下り
	int walkL;									//左方向の移動
	int jump_upL;								//左方向のジャンプの上り
	int jump_fallL;								//左方向のジャンプの下り
};