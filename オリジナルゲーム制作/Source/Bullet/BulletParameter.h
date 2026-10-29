#pragma once

#define STRAIGHT_BULLET_MAX (1024)
#define HOMING_BULLET_MAX (1024)

// 発射する弾丸のカテゴリ
enum BulletCategory
{
	BULLET_CATEGORY_STRAIGHT,
	BULLET_CATEGORY_HOMING,
};

// 弾の当たり判定で区別をつけるためのタグ
enum BulletCollisionTag
{
	BULLET_COLLISION_TAG_PLAYER,	// プレイヤーが撃った弾
	BULLET_COLLISION_TAG_ENEMY,		// 敵が撃った弾
};

// 直線弾の種類
enum StraightBulletType
{
	STRAIGHT_BULLET_TYPE_PLAYER,	// プレイヤーの通常弾
	STRAIGHT_BULLET_TYPE_ENEMY,		// 敵が撃つ弾
	STRAIGHT_BULLET_TYPE_MAX,
};

// 直線弾のデータ
struct StraightBulletData
{
	int handle;
	int life;
	float posX;
	float posY;
	float moveX;
	float moveY;
	float width;
	float height;
	float radius;
	bool active;
	BulletCollisionTag tag;
};