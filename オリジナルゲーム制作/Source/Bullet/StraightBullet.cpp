#include "DxLib.h"
#include "StraightBullet.h"
#include "../Player/Player.h"

// 矩形判定の位置補正
#define STRAIGHT_BULLET_COLLISION_OFFSET_X (0)
#define STRAIGHT_BULLET_COLLISION_OFFSET_Y (0)
// 矩形判定のサイズ
#define STRAIGHT_BULLET_BOX_COLLISION_WIDTH (5)
#define STRAIGHT_BULLET_BOX_COLLISION_HEIGHT (5)

StraightBulletData g_StraightBulletData[STRAIGHT_BULLET_MAX] = {0};

int g_BulletHandle[STRAIGHT_BULLET_MAX] = {0};

void InitStraightBullet()
{
	// 処理高速化のためポインタを使う
	StraightBulletData* bullet = g_StraightBulletData;
	for (int i = 0; i < STRAIGHT_BULLET_MAX; i++)
	{
		bullet->handle = 0;
		bullet->life = 0;
		bullet->pos.x = 0.0f;
		bullet->pos.y = 0.0f;
		bullet->move.x = 0.0f;
		bullet->move.y = 0.0f;
		bullet->active = false;
	}

	for (int i = 0; i < STRAIGHT_BULLET_TYPE_MAX; i++)
	{
		g_BulletHandle[i];
	}

}

void StartStraightBullet()
{
	g_StraightBulletData->BoxCollison.posX = STRAIGHT_BULLET_COLLISION_OFFSET_X;
	g_StraightBulletData->BoxCollison.posY = STRAIGHT_BULLET_COLLISION_OFFSET_Y;
	g_StraightBulletData->BoxCollison.height = STRAIGHT_BULLET_BOX_COLLISION_WIDTH;
	g_StraightBulletData->BoxCollison.width = STRAIGHT_BULLET_BOX_COLLISION_HEIGHT;
}

void LoadStraightBullet()
{
	// プレイヤー通常弾
	int handle = 0;
	handle = LoadGraph("Data/Bullet/Bullet.png");
	g_BulletHandle[STRAIGHT_BULLET_TYPE_PLAYER] = handle;
}

void StepStraightBullet()
{
	// 処理高速化のためポインタを使う
	StraightBulletData* bullet = g_StraightBulletData;
	for (int i = 0; i < STRAIGHT_BULLET_MAX; i++, bullet++)
	{
		// 生きている弾だけ処理をする
		if (!bullet->active)continue;

		// 寿命を減らす
		bullet->life--;
	}
}

void UpdateStraightBullet()
{
	// 処理高速化のためポインタを使う
	StraightBulletData* bullet = g_StraightBulletData;
	for (int i = 0; i < STRAIGHT_BULLET_MAX; i++, bullet++)
	{
		// 生きている弾だけ処理する
		if (!bullet->active)continue;

		// 移動
		bullet->pos.x += bullet->move.x;
		bullet->pos.y += bullet->move.y;

		// 寿命処理
		if (bullet->life <= 0)
		{
			// 寿命が過ぎたら生存フラグを折る
			bullet->active = false;
		}
	}
}

void DrawStraightBullet()
{
	// 処理高速化のためポインタを使う
	StraightBulletData* bullet = g_StraightBulletData;
	for (int i = 0; i < STRAIGHT_BULLET_MAX; i++, bullet++)
	{
		// 生きている弾だけ描画する
		if (!bullet->active) continue;

		DrawGraph((int)bullet->pos.x, (int)bullet->pos.y, bullet->handle, TRUE);
	}
}

void FinStraightBullet()
{
	// ロードした分だけ削除
	for (int i = 0; i < STRAIGHT_BULLET_TYPE_MAX; i++)
	{
		DeleteGraph(g_BulletHandle[i]);
	}
}

void FireStraightBullet(StraightBulletType type, int life, float posX, float posY, float moveX, float moveY, BoxCollision boxcollision, BulletCollisionTag tag)
{
	// 処理高速化のためポインタを使う
	StraightBulletData* bullet = g_StraightBulletData;
	for (int i = 0; i < STRAIGHT_BULLET_MAX; i++, bullet++)
	{
		// 配列内で使われていないところを探す
		if (!bullet->active)
		{
			// 発射処理
			bullet->active = true;

			// 寿命設定
			bullet->life = life;

			// 画像設定
			bullet->handle = g_BulletHandle[type];

			// 座標設定
			bullet->pos.x = posX;
			bullet->pos.y = posY;

			// 移動量設定
			bullet->move.x = moveX;
			bullet->move.y = moveY;

			// 半径(当たり判定)
//			bullet->radius = radius;

			bullet->BoxCollison.height = boxcollision.height;
			bullet->BoxCollison.width = boxcollision.width;
			bullet->BoxCollison.posX = boxcollision.posX;
			bullet->BoxCollison.posY = boxcollision.posY;

			//当たり判定のタグ
			bullet->tag = tag;

			// 1発発射したら抜ける
			break;
		}
	}
}

StraightBulletData* GetStraightBullet()
{
	return g_StraightBulletData;
}
