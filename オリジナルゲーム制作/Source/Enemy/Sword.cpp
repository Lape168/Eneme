#include "Sword.h"
#include "../Enemy/Enemy.Parameter.h"
#include "../Input/Input.h"
#include "../Player/Player.h"
#include <math.h>

//ソード敵関連
#define SWORD_ENEMY_MOVE_SPEED (5.5f)
#define SWORD_ENEMY_DEFAULT_POS_X		(100.0f)
#define SWORD_ENEMY_DEFAULT_POS_Y		(300.0f)
#define SWORD_ENEMY_MAP_COLLISION_OFFSET (0.10f)
#define SWORD_ENEMY_FROZEN_TIME (600)

// ジャンプ力
#define SWORD_ENEMY_JUMP_POWER (10.0f)

// 重力
#define SWORD_ENEMY_GRAVITY (0.5f)

void CalcBoxCollisionB(SwordEnemyData swordenemy, float& x, float& y, float& w, float& h);

SwordEnemyData g_SwordEnemyData = { 0 };
SwordEnemyData g_PrevSwordEnemyData = { 0 };

SwordEnemyMotion g_EnemyMotion = { 0 };

void InitSword()
{
	g_SwordEnemyData.pos.x = SWORD_ENEMY_DEFAULT_POS_X;
	g_SwordEnemyData.pos.y = SWORD_ENEMY_DEFAULT_POS_Y;
	g_SwordEnemyData.move.x = 0;
	g_SwordEnemyData.move.y = 0;
	g_SwordEnemyData.frozenTime = 0; 
}

void StartSword()
{
	// 矩形判定設定
	g_SwordEnemyData.boxCollision.width = SWORD_ENEMY_BOX_COLLISION_WIDTH;
	g_SwordEnemyData.boxCollision.height = SWORD_ENEMY_BOX_COLLISION_HEIGHT;
}

void LoadSword()
{
	//画像
	g_EnemyMotion.walkR = LoadGraph("Data/Enemy/EnemyR.png");
	g_EnemyMotion.walkL = LoadGraph("Data/Enemy/EnemyL.png");
	g_EnemyMotion.frozenR = LoadGraph("Data/Enemy/EnemyFrozenR.png");
	g_EnemyMotion.frozenL = LoadGraph("Data/Enemy/EnemyFrozenL.png");
}

void StepSword()
{
	g_SwordEnemyData.move.x = 0.0f;

	//重力
	if (!g_SwordEnemyData.frozen)
	{
		g_SwordEnemyData.move.y += SWORD_ENEMY_GRAVITY;
	}
	else
	{
		g_SwordEnemyData.move.y = 0.0f;
	}

	g_PrevSwordEnemyData = g_SwordEnemyData;

	PlayerData* player = GetPlayer();
	//プレイヤーと同じ動きをさせる処理 + 凍っていたら動きを0に

	if (IsInputKey(KEY_LEFT))
	{
		if (!g_SwordEnemyData.frozen)
		{
			g_SwordEnemyData.move.x = -SWORD_ENEMY_MOVE_SPEED / 2;
		}
		else
		{
			g_SwordEnemyData.move.x = 0;
		}
	}
	if (IsInputKey(KEY_RIGHT))
	{
		if (!g_SwordEnemyData.frozen)
		{
			g_SwordEnemyData.move.x = SWORD_ENEMY_MOVE_SPEED / 2;
		}
		else
		{
			g_SwordEnemyData.move.x = 0;
		}
	}

	if (IsTriggerKey(KEY_SPACE) && !g_SwordEnemyData.isAir)
	{
		if (!g_SwordEnemyData.frozen)
		{
			g_SwordEnemyData.move.y -= SWORD_ENEMY_JUMP_POWER;
		}
		else
		{
			g_SwordEnemyData.move.y = 0;
		}
	}

	float dir = player->pos.x - g_SwordEnemyData.pos.x;

	float min = fabs(dir) < SWORD_ENEMY_MOVE_SPEED / 5 ?
		fabs(dir) :
		SWORD_ENEMY_MOVE_SPEED / 5;

	//自動追尾
	if (dir > 0)
	{
		if (!g_SwordEnemyData.frozen)
		{
			g_SwordEnemyData.move.x += min;
		}
		else
		{
			g_SwordEnemyData.move.x += 0;
		}
	}
	else if (dir < 0)
	{
		if (!g_SwordEnemyData.frozen)
		{
			g_SwordEnemyData.move.x -= min;
		}
		else
		{
			g_SwordEnemyData.move.x -= 0;
		}

	}

	//凍っている時間の処理
	if (g_SwordEnemyData.frozen == true)
	{
		g_SwordEnemyData.frozenTime--;
	}
}

void UpdateSword()
{
	// 上昇しているもしくは落ちている場合は空中フラグを立てる
	if (g_SwordEnemyData.move.y < 0.0f || g_SwordEnemyData.move.y > SWORD_ENEMY_GRAVITY)
	{
		g_SwordEnemyData.isAir = true;
	}

	if (g_SwordEnemyData.frozenTime <= 0)
	{
		g_SwordEnemyData.frozen = false;
	}

	//移動処理
	g_SwordEnemyData.pos.x += g_SwordEnemyData.move.x;
	g_SwordEnemyData.pos.y += g_SwordEnemyData.move.y;
}

void DrawSword()
{
	PlayerData* player = GetPlayer();

	//プレイヤーより右にいると左を向く
	if (player->pos.x < g_SwordEnemyData.pos.x)
	{
		if (g_SwordEnemyData.frozen == true) //凍っている
		{
			DrawGraph(g_SwordEnemyData.pos.x, g_SwordEnemyData.pos.y - 25, g_EnemyMotion.frozenL, TRUE);
		}
		else //凍っていない
		{
			DrawGraph(g_SwordEnemyData.pos.x, g_SwordEnemyData.pos.y - 20, g_EnemyMotion.walkL, TRUE);
		}
	}
	//プレイヤーより左にいると右を向く
	if (player->pos.x >= g_SwordEnemyData.pos.x)
	{
		if (g_SwordEnemyData.frozen == true) //凍っている
		{
			DrawGraph(g_SwordEnemyData.pos.x, g_SwordEnemyData.pos.y - 25, g_EnemyMotion.frozenR, TRUE);
		}
		else //凍っていない
		{
			DrawGraph(g_SwordEnemyData.pos.x, g_SwordEnemyData.pos.y - 20, g_EnemyMotion.walkR, TRUE);
		}
	}
}

void FinSword()
{

}

SwordEnemyData* GetSwordEnemy()
{
	return &g_SwordEnemyData;
}

void SwordEnemyHitNormalBlockX(MapChipData mapChipData)
{
	SwordEnemyData swordenemy = g_SwordEnemyData;
	BlockData* block = mapChipData.data;
	const float POS_OFFSET = SWORD_ENEMY_MAP_COLLISION_OFFSET;
	const float SIZE_OFFSET = SWORD_ENEMY_MAP_COLLISION_OFFSET * 2;

	// ターンフラグは前回のものにしないと反転した分ずれる
	swordenemy.isTurn = g_PrevSwordEnemyData.isTurn;

	// Y移動を戻し、横に当たっているかチェック
	swordenemy.pos.x = g_SwordEnemyData.pos.x;
	swordenemy.pos.y = g_PrevSwordEnemyData.pos.y;

	// 当たり判定のボックス計算
	float x, y, w, h;
	CalcBoxCollisionB(swordenemy, x, y, w, h);

	if (CheckSquareSquare(x + POS_OFFSET, y + POS_OFFSET, w - SIZE_OFFSET, h - SIZE_OFFSET,
		block->pos.x, block->pos.y, MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT))
	{
		// 左からあたったか
		if (swordenemy.move.x > 0.0f)
		{
			// 左に押し出す
			g_SwordEnemyData.pos.x -= (x + w) - block->pos.x;
		}
		// 右からあたったか
		else if (swordenemy.move.x < 0.0f)
		{
			// 右に押し出す
			g_SwordEnemyData.pos.x += (block->pos.x + MAP_CHIP_WIDTH) - x;
		}
	}
}

void SwordEnemyHitNormalBlockY(MapChipData mapChipData)
{
	SwordEnemyData swordenemy = g_SwordEnemyData;
	BlockData* block = mapChipData.data;
	const float POS_OFFSET = SWORD_ENEMY_MAP_COLLISION_OFFSET;
	const float SIZE_OFFSET = SWORD_ENEMY_MAP_COLLISION_OFFSET * 2;

	// ターンフラグは前回のものにしないと反転した分ずれる
	swordenemy.isTurn = g_PrevSwordEnemyData.isTurn;

	// 当たり判定のボックス計算
	float x, y, w, h;
	CalcBoxCollisionB(swordenemy, x, y, w, h);

	// まだ当たっているなら縦に当たっている
	if (CheckSquareSquare(x + POS_OFFSET, y + POS_OFFSET, w - SIZE_OFFSET, h - SIZE_OFFSET,
		block->pos.x, block->pos.y, MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT))
	{
		// Y移動量を0にする
		g_SwordEnemyData.move.y = 0.0f;

		// 上からあたったか
		if (swordenemy.move.y > 0.0f)
		{
			// 上に押し出す
			g_SwordEnemyData.pos.y -= (y + h) - block->pos.y;
			g_SwordEnemyData.isAir = false;
		}
		// 下からあたったか
		else if (swordenemy.move.y < 0.0f)
		{
			// 下に押し出す
			g_SwordEnemyData.pos.y += (block->pos.y + MAP_CHIP_WIDTH) - y;
		}
	}
}

void CalcBoxCollisionB(SwordEnemyData swordenemy, float& x, float& y, float& w, float& h)
{
	//矩形
	x = swordenemy.pos.x;
	y = swordenemy.pos.y;
	w = swordenemy.boxCollision.width;
	h = swordenemy.boxCollision.height;
}

void SwordEnemyHitPlayer()
{
	g_SwordEnemyData.active = false;
}

void BulletHitSwordEnemy()
{
	if (g_SwordEnemyData.frozenTime >= 0)
	{
		g_SwordEnemyData.frozen = true;
	}
	g_SwordEnemyData.frozenTime = SWORD_ENEMY_FROZEN_TIME;
}
