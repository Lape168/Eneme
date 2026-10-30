#include "DxLib.h"
#include "StraightBullet.h"
#include "../Player/Player.h"

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
		bullet->posX = 0.0f;
		bullet->posY = 0.0f;
		bullet->moveX = 0.0f;
		bullet->moveY = 0.0f;
		bullet->radius = 0.0f;
		bullet->active = false;
	}

	for (int i = 0; i < STRAIGHT_BULLET_TYPE_MAX; i++)
	{
		g_BulletHandle[i];
	}

}

void LoadStraightBullet()
{
	// プレイヤー通常弾
	int handle = 0;
	handle = LoadGraph("Data/Bullet/Bullet2.png");
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
		bullet->posX += bullet->moveX;
		bullet->posY += bullet->moveY;

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

		DrawGraph((int)bullet->posX, (int)bullet->posY, bullet->handle, TRUE);
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

void FireStraightBullet(StraightBulletType type, int life, float posX, float posY, float moveX, float moveY, float radius, BulletCollisionTag tag)
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
			bullet->posX = posX;
			bullet->posY = posY;

			// 移動量設定
			bullet->moveX = moveX;
			bullet->moveY = moveY;

			// 半径(当たり判定)
			bullet->radius = radius;

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
