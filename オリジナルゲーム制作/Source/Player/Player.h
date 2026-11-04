#pragma once
#include "../Map/MapParameter.h"
#include "../Collision/Collision.h"

// プレイヤーサイズ
#define PLAYER_WIDTH	(72.0f)
#define PLAYER_HEIGHT	(72.0f)
#define PLAYER_RADIUS	(36.0f)

struct PlayerData
{
	int handle;									// 画像
	bool active;								// 生存フラグ
	bool isTurn;								// 左を向いているか
	bool isAir;									// 空中にいるか
	int bulletInterval;							// 銃のインターバル
	VECTOR pos;									// 座標
	VECTOR move;								// 移動量
	BoxCollision boxCollision;					// 矩形当たり判定
};

struct Motion
{
	int walk;
	int jump_up;
	int jump_fall;
	int shot;
};

// 関数のプロトタイプ宣言
void InitPlayer();
void LoadPlayer();
void StartPlayer();
void StepPlayer();
void UpdatePlayer();
void DrawPlayer();
void FinPlayer();

// 取得関数
PlayerData* GetPlayer();

// 当たり判定
void PlayerHitNormalBlockX(MapChipData mapChipData);
void PlayerHitNormalBlockY(MapChipData mapChipData);