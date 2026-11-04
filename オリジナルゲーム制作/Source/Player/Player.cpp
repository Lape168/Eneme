#include "DxLib.h"
#include "Player.h"
#include "../Input/Input.h"
#include "../Bullet/BulletManager.h"
#include "../Collision/Collision.h"

// プレイヤー設定関連
#define PLAYER_DEFAULT_POS_X		(400.0f)
#define PLAYER_DEFAULT_POS_Y		(300.0f)
#define PLAYER_MOVE_SPEED			(6.0f)
#define PLAYER_MAP_COLLISION_OFFSET (0.10f)

// 矩形判定の位置補正
#define PLAYER_BOX_COLLISION_OFFSET_X (40)
#define PLAYER_BOX_COLLISION_OFFSET_Y (0)
// 矩形判定のサイズ
#define PLAYER_BOX_COLLISION_WIDTH (20)
#define PLAYER_BOX_COLLISION_HEIGHT (50)

//弾関連
#define PLAYER_BULLET_SPEED_X	(8.0f)
#define PLAYER_BULLET_SPEED_Y	(0.0f)
#define PLAYER_BULLET_LIFE		(120)
#define PLAYER_BULLET_OFFSET_X	(34.0f)
#define PLAYER_BULLET_OFFSET_Y	(18.0f)
#define PLAYER_BULLET_RADIUS	(8)
#define PLAYER_BULLET_INTERVAL  (20)

// ジャンプ力
#define PLAYER_JUMP_POWER (7.0f)

// 重力
#define PLAYER_GRAVITY (0.2f)

PlayerData g_PlayerData = { 0 };
PlayerData g_PrevPlayerData = { 0 };
Motion g_MotionData = { 0 };

void CalcBoxCollision(PlayerData player, float& x, float& y, float& w, float& h);

void InitPlayer()
{
	g_PlayerData.pos.x = PLAYER_DEFAULT_POS_X;
	g_PlayerData.pos.y = PLAYER_DEFAULT_POS_Y;
	g_PlayerData.move.x = 0.0f;
	g_PlayerData.move.y = 0.0f;
	g_PlayerData.bulletInterval = 0;
	g_PlayerData.active = false;

	// 構造体はmemsetで0初期化できる
	memset(&g_PlayerData.boxCollision, 0, sizeof(g_PlayerData.boxCollision));
}

void LoadPlayer()
{
	g_MotionData.shot = LoadGraph("Data/Player/Player_Shot.png");
	g_MotionData.jump_up = LoadGraph("Data/Player/Player_JumpUp.png");
	g_MotionData.jump_fall = LoadGraph("Data/Player/Player_JumpFall.png");
}

void StartPlayer()
{
	// 生存フラグを立てる
	g_PlayerData.active = true;


	// 矩形判定設定
	g_PlayerData.boxCollision.posX = PLAYER_BOX_COLLISION_OFFSET_X;
	g_PlayerData.boxCollision.posY = PLAYER_BOX_COLLISION_OFFSET_Y;
	g_PlayerData.boxCollision.width = PLAYER_BOX_COLLISION_WIDTH;
	g_PlayerData.boxCollision.height = PLAYER_BOX_COLLISION_HEIGHT;
}

void StepPlayer()
{
	// 死んでいたら何もしない
	if (!g_PlayerData.active) return;

	// 前回のデータとして記憶	
	g_PrevPlayerData = g_PlayerData;

	// X移動量は毎回リセットする
	g_PlayerData.move.x = 0.0f;

	// Y移動量に重力を反映
	g_PlayerData.move.y += PLAYER_GRAVITY;

	//弾のインターバルの時間を減らす
	if (g_PlayerData.bulletInterval > 0)
	{
		g_PlayerData.bulletInterval--;
	}

	// 左入力
	if (IsInputKey(KEY_LEFT))
	{
		g_PlayerData.move.x = -PLAYER_MOVE_SPEED;
		g_PlayerData.isTurn = true;

		//スペース入力
		if (IsInputKey(KEY_SPACE))
		{
			g_PlayerData.move.y = -PLAYER_JUMP_POWER;
		}
		//Zキー入力
		if (IsInputKey(KEY_Z))
		{
			PlayerData* player = GetPlayer();

			float fireX = g_PlayerData.pos.x + PLAYER_BULLET_OFFSET_X;
			float fireY = g_PlayerData.pos.y + PLAYER_BULLET_OFFSET_Y;
			if (g_PlayerData.bulletInterval <= 0)
			{
				if (player->active)
				{
					RequestFireBullet(STRAIGHT_BULLET_TYPE_PLAYER, PLAYER_BULLET_LIFE, fireX, fireY, -PLAYER_BULLET_SPEED_X, PLAYER_BULLET_SPEED_Y, PLAYER_BULLET_RADIUS, BULLET_COLLISION_TAG_PLAYER);
				}
				// インターバル設定
				g_PlayerData.bulletInterval = PLAYER_BULLET_INTERVAL;
			}

		}
	}
	// 右入力
	else if (IsInputKey(KEY_RIGHT))
	{
		g_PlayerData.move.x = PLAYER_MOVE_SPEED;
		g_PlayerData.isTurn = false;

		//スペース入力
		if (IsInputKey(KEY_SPACE))
		{
			g_PlayerData.move.y = -PLAYER_JUMP_POWER;
		}
		//Zキー入力
		if (IsInputKey(KEY_Z))
		{
			PlayerData* player = GetPlayer();

			float fireX = g_PlayerData.pos.x + PLAYER_BULLET_OFFSET_X;
			float fireY = g_PlayerData.pos.y + PLAYER_BULLET_OFFSET_Y;
			if (g_PlayerData.bulletInterval <= 0)
			{
				if (player->active)
				{
					RequestFireBullet(STRAIGHT_BULLET_TYPE_PLAYER, PLAYER_BULLET_LIFE, fireX, fireY, PLAYER_BULLET_SPEED_X, PLAYER_BULLET_SPEED_Y, PLAYER_BULLET_RADIUS, BULLET_COLLISION_TAG_PLAYER);
				}
				// インターバル設定
				g_PlayerData.bulletInterval = PLAYER_BULLET_INTERVAL;
			}

		}
	}
	//Zキー入力
	else if (IsInputKey(KEY_Z))
	{
		PlayerData* player = GetPlayer();

		float fireX = g_PlayerData.pos.x + PLAYER_BULLET_OFFSET_X;
		float fireY = g_PlayerData.pos.y + PLAYER_BULLET_OFFSET_Y;
		if (g_PlayerData.bulletInterval <= 0)
		{
			if (player->active)
			{
				DrawGraph(g_PlayerData.pos.x, g_PlayerData.pos.y, g_MotionData.shot, TRUE);
				RequestFireBullet(STRAIGHT_BULLET_TYPE_PLAYER, PLAYER_BULLET_LIFE, fireX, fireY, PLAYER_BULLET_SPEED_X, PLAYER_BULLET_SPEED_Y, PLAYER_BULLET_RADIUS, BULLET_COLLISION_TAG_PLAYER);
			}
			// インターバル設定
			g_PlayerData.bulletInterval = PLAYER_BULLET_INTERVAL;
		}

	}
	//スペース入力
	else if (IsInputKey(KEY_SPACE))
	{
		g_PlayerData.move.y = -PLAYER_JUMP_POWER;
	}

}

void UpdatePlayer()
{
	// 死んでいたら処理しない
	if (!g_PlayerData.active) return;

	// 上昇しているもしくは落ちている場合は空中フラグを立てる
	if (g_PlayerData.move.y < 0.0f || g_PlayerData.move.y > PLAYER_GRAVITY)
	{
		g_PlayerData.isAir = true;
	}

	if (g_PlayerData.isAir = true && g_PlayerData.move.y > 0)
	{

	}
	if (g_PlayerData.isAir = true && g_PlayerData.move.y < 0)
	{

	}
	// 移動処理
	g_PlayerData.pos.x += g_PlayerData.move.x;
	g_PlayerData.pos.y += g_PlayerData.move.y;
}

void DrawPlayer()
{
	// 死んでいたら処理しない
	if (!g_PlayerData.active) return;

	DrawGraph(g_PlayerData.pos.x, g_PlayerData.pos.y, g_MotionData.walk, TRUE);
}

void FinPlayer()
{

}

PlayerData* GetPlayer()
{
	return &g_PlayerData;
}

void PlayerHitNormalBlockX(MapChipData mapChipData)
{
	PlayerData player = g_PlayerData;
	BlockData* block = mapChipData.data;
	const float POS_OFFSET = PLAYER_MAP_COLLISION_OFFSET;
	const float SIZE_OFFSET = PLAYER_MAP_COLLISION_OFFSET * 2;

	// ターンフラグは前回のものにしないと反転した分ずれる
	player.isTurn = g_PrevPlayerData.isTurn;

	// Y移動を戻し、横に当たっているかチェック
	player.pos.x = g_PlayerData.pos.x;
	player.pos.y = g_PrevPlayerData.pos.y;

	// 当たり判定のボックス計算
	float x, y, w, h;
	CalcBoxCollision(player, x, y, w, h);

	if (CheckSquareSquare(x + POS_OFFSET, y + POS_OFFSET, w - SIZE_OFFSET, h - SIZE_OFFSET,
		block->pos.x, block->pos.y, MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT))
	{
		// 左からあたったか
		if (player.move.x > 0.0f)
		{
			// 左に押し出す
			g_PlayerData.pos.x -= (x + w) - block->pos.x;
		}
		// 右からあたったか
		else if (player.move.x < 0.0f)
		{
			// 右に押し出す
			g_PlayerData.pos.x += (block->pos.x + MAP_CHIP_WIDTH) - x;
		}
	}

}

void PlayerHitNormalBlockY(MapChipData mapChipData)
{
	PlayerData player = g_PlayerData;
	BlockData* block = mapChipData.data;
	const float POS_OFFSET = PLAYER_MAP_COLLISION_OFFSET;
	const float SIZE_OFFSET = PLAYER_MAP_COLLISION_OFFSET * 2;

	// ターンフラグは前回のものにしないと反転した分ずれる
	player.isTurn = g_PrevPlayerData.isTurn;

	// 当たり判定のボックス計算
	float x, y, w, h;
	CalcBoxCollision(player, x, y, w, h);

	// まだ当たっているなら縦に当たっている
	if (CheckSquareSquare(x + POS_OFFSET, y + POS_OFFSET, w - SIZE_OFFSET, h - SIZE_OFFSET,
		block->pos.x, block->pos.y, MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT))
	{
		// Y移動量を0にする
		g_PlayerData.move.y = 0.0f;

		// 上からあたったか
		if (player.move.y > 0.0f)
		{
			// 上に押し出す
			g_PlayerData.pos.y -= (y + h) - block->pos.y;
			g_PlayerData.isAir = false;
		}
		// 下からあたったか
		else if (player.move.y < 0.0f)
		{
			// 下に押し出す
			g_PlayerData.pos.y += (block->pos.y + MAP_CHIP_WIDTH) - y;
		}
	}
}

void CalcBoxCollision(PlayerData player, float& x, float& y, float& w, float& h)
{
	x = player.isTurn ?
		player.pos.x + PLAYER_WIDTH - player.boxCollision.posX - player.boxCollision.width :
		player.pos.x + player.boxCollision.posX;
	y = player.pos.y + player.boxCollision.posY;
	w = player.boxCollision.width;
	h = player.boxCollision.height;
}

