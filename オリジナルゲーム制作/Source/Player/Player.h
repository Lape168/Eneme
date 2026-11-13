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
	bool isAtk;									// 銃を撃ったか
	bool isFire;
	int bulletInterval;							// 銃のインターバル
	int height;									// 縦幅
	int width;									// 横幅
	VECTOR pos;									// 座標
	VECTOR move;								// 移動量
	BoxCollision boxCollision;					// 矩形当たり判定
};

struct Motion
{
	int walkR;									//右方向の移動
	int jump_upR;								//右方向のジャンプの上り
	int jump_fallR;								//右方向のジャンプの下り
	int shotR;									//右方向の銃発砲
	int walkL;									//左方向の移動
	int jump_upL;								//左方向のジャンプの上り
	int jump_fallL;								//左方向のジャンプの下り
	int shotL;									//左方向の銃発砲
};

struct Body
{
	bool isAir;
	VECTOR pos;
	VECTOR move;
	float width;
	float height;
	float radius;
	float reflactPower;
	VECTOR prevPos;
	const Body* hitBlock;
	const Body* groundBlock;
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

void PlayerHitEnemy();