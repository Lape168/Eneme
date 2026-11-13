#include "Nomal.h"
#include "../Enemy/Enemy.Parameter.h"
#include "../Input/Input.h"
#include "../Player/Player.h"
#include <math.h>


#define NOMAL_ENEMY_MOVE_SPEED (5.5f)
#define NOMAL_ENEMY_DEFAULT_POS_X		(800.0f)
#define NOMAL_ENEMY_DEFAULT_POS_Y		(100.0f)
#define NOMAL_ENEMY_MAP_COLLISION_OFFSET (0.10f)

// 矩形判定の位置補正
#define NOMAL_ENEMY_BOX_COLLISION_OFFSET_X (15)
#define NOMAL_ENEMY_BOX_COLLISION_OFFSET_Y (15)
// 矩形判定のサイズ
#define NOMAL_ENEMY_BOX_COLLISION_WIDTH (45)
#define NOMAL_ENEMY_BOX_COLLISION_HEIGHT (50)

// ジャンプ力
#define NOMAL_ENEMY_JUMP_POWER (10.0f)

// 重力
#define NOMAL_ENEMY_GRAVITY (0.25f)

void CalcBoxCollision(NomalEnemyData nomalenemy, float& x, float& y, float& w, float& h);

NomalEnemyData g_NomalEnemyData = { 0 };
NomalEnemyData g_PrevNomalEnemyData = { 0 };

EnemyMotion g_EnemyMotion = { 0 };

void InitNomal()
{
	g_NomalEnemyData.pos.x = NOMAL_ENEMY_DEFAULT_POS_X;
	g_NomalEnemyData.pos.y = NOMAL_ENEMY_DEFAULT_POS_Y;
	g_NomalEnemyData.move.x = 0;
	g_NomalEnemyData.move.y = 0;
}

void StartNomal()
{
	// 矩形判定設定
	g_NomalEnemyData.boxCollision.posX = NOMAL_ENEMY_BOX_COLLISION_OFFSET_X;
	g_NomalEnemyData.boxCollision.posY = NOMAL_ENEMY_BOX_COLLISION_OFFSET_Y;
	g_NomalEnemyData.boxCollision.width = NOMAL_ENEMY_BOX_COLLISION_WIDTH;
	g_NomalEnemyData.boxCollision.height = NOMAL_ENEMY_BOX_COLLISION_HEIGHT;
}

void LoadNomal()
{
	g_EnemyMotion.walkR = LoadGraph("Data/Enemy/EnemyR.png");
	g_EnemyMotion.walkL = LoadGraph("Data/Enemy/EnemyL.png");
}

void StepNomal()
{
	g_NomalEnemyData.move.x = 0.0f;

	g_NomalEnemyData.move.y += NOMAL_ENEMY_GRAVITY;

	g_PrevNomalEnemyData = g_NomalEnemyData;

	if (IsInputKey(KEY_LEFT))
	{
		g_NomalEnemyData.move.x = -NOMAL_ENEMY_MOVE_SPEED / 2;
	}
	if (IsInputKey(KEY_RIGHT))
	{
		g_NomalEnemyData.move.x = NOMAL_ENEMY_MOVE_SPEED / 2;
	}
	if (IsInputKey(KEY_SPACE) && !g_NomalEnemyData.isAir)
	{
		g_NomalEnemyData.move.y -= NOMAL_ENEMY_JUMP_POWER;
	}

	PlayerData* player = GetPlayer();
	float dir = player->pos.x - g_NomalEnemyData.pos.x;

	float min = fabs(dir) < NOMAL_ENEMY_MOVE_SPEED / 5 ?
		fabs(dir) :
		NOMAL_ENEMY_MOVE_SPEED / 5;

	if (dir > 0)
	{
		g_NomalEnemyData.move.x += min;
	}
	else if (dir < 0)
	{
		g_NomalEnemyData.move.x -= min;
	}

}

void UpdateNomal()
{
	// 上昇しているもしくは落ちている場合は空中フラグを立てる
	if (g_NomalEnemyData.move.y < 0.0f || g_NomalEnemyData.move.y > NOMAL_ENEMY_GRAVITY)
	{
		g_NomalEnemyData.isAir = true;
	}

	g_NomalEnemyData.pos.x += g_NomalEnemyData.move.x;
	g_NomalEnemyData.pos.y += g_NomalEnemyData.move.y;
}

void DrawNomal()
{
	PlayerData* player = GetPlayer();
	if (player->pos.x < g_NomalEnemyData.pos.x)
	{
		DrawGraph(g_NomalEnemyData.pos.x, g_NomalEnemyData.pos.y, g_EnemyMotion.walkL, TRUE);
	}
	if (player->pos.x >= g_NomalEnemyData.pos.x)
	{
		DrawGraph(g_NomalEnemyData.pos.x, g_NomalEnemyData.pos.y, g_EnemyMotion.walkR, TRUE);
	}
}

void FinNomal()
{

}

NomalEnemyData* GetNomalEnemy()
{
	return &g_NomalEnemyData;
}

void NomalEnemyHitNormalBlockX(MapChipData mapChipData)
{
	NomalEnemyData nomalenemy = g_NomalEnemyData;
	BlockData* block = mapChipData.data;
	const float POS_OFFSET = NOMAL_ENEMY_MAP_COLLISION_OFFSET;
	const float SIZE_OFFSET = NOMAL_ENEMY_MAP_COLLISION_OFFSET * 2;

	// ターンフラグは前回のものにしないと反転した分ずれる
	nomalenemy.isTurn = g_PrevNomalEnemyData.isTurn;

	// Y移動を戻し、横に当たっているかチェック
	nomalenemy.pos.x = g_NomalEnemyData.pos.x;
	nomalenemy.pos.y = g_PrevNomalEnemyData.pos.y;

	// 当たり判定のボックス計算
	float x, y, w, h;
	CalcBoxCollision(nomalenemy, x, y, w, h);

	if (CheckSquareSquare(x + POS_OFFSET, y + POS_OFFSET, w - SIZE_OFFSET, h - SIZE_OFFSET,
		block->pos.x, block->pos.y, MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT))
	{
		// 左からあたったか
		if (nomalenemy.move.x > 0.0f)
		{
			// 左に押し出す
			g_NomalEnemyData.pos.x -= (x + w) - block->pos.x;
		}
		// 右からあたったか
		else if (nomalenemy.move.x < 0.0f)
		{
			// 右に押し出す
			g_NomalEnemyData.pos.x += (block->pos.x + MAP_CHIP_WIDTH) - x;
		}
	}
}

void NomalEnemyHitNormalBlockY(MapChipData mapChipData)
{
	NomalEnemyData nomalenemy = g_NomalEnemyData;
	BlockData* block = mapChipData.data;
	const float POS_OFFSET = NOMAL_ENEMY_MAP_COLLISION_OFFSET;
	const float SIZE_OFFSET = NOMAL_ENEMY_MAP_COLLISION_OFFSET * 2;

	// ターンフラグは前回のものにしないと反転した分ずれる
	nomalenemy.isTurn = g_PrevNomalEnemyData.isTurn;

	// 当たり判定のボックス計算
	float x, y, w, h;
	CalcBoxCollision(nomalenemy, x, y, w, h);

	// まだ当たっているなら縦に当たっている
	if (CheckSquareSquare(x + POS_OFFSET, y + POS_OFFSET, w - SIZE_OFFSET, h - SIZE_OFFSET,
		block->pos.x, block->pos.y, MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT))
	{
		// Y移動量を0にする
		g_NomalEnemyData.move.y = 0.0f;

		// 上からあたったか
		if (nomalenemy.move.y > 0.0f)
		{
			// 上に押し出す
			g_NomalEnemyData.pos.y -= (y + h) - block->pos.y;
			g_NomalEnemyData.isAir = false;
		}
		// 下からあたったか
		else if (nomalenemy.move.y < 0.0f)
		{
			// 下に押し出す
			g_NomalEnemyData.pos.y += (block->pos.y + MAP_CHIP_WIDTH) - y;
		}
	}
}


void CalcBoxCollision(NomalEnemyData nomalenemy, float& x, float& y, float& w, float& h)
{
	x = nomalenemy.isTurn ?
		nomalenemy.pos.x + NOMAL_ENEMY_WIDTH - nomalenemy.boxCollision.posX - nomalenemy.boxCollision.width :
		nomalenemy.pos.x + nomalenemy.boxCollision.posX;
	y = nomalenemy.pos.y + nomalenemy.boxCollision.posY;
	w = nomalenemy.boxCollision.width;
	h = nomalenemy.boxCollision.height;
}

void NomalEnemyHitPlayer()
{
	g_NomalEnemyData.active = false;
}

void BulletHitEnemy()
{
	g_NomalEnemyData.move.x = 0;
	g_NomalEnemyData.move.y = 0;
}
