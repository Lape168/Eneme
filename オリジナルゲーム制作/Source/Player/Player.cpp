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

//弾
#define PLAYER_BULLET_SPEED_X	(20.0f)
#define PLAYER_BULLET_SPEED_Y	(0.0f)
#define PLAYER_BULLET_LIFE		(20)
#define PLAYER_BULLET_OFFSET_R_X	(40.0f)
#define PLAYER_BULLET_OFFSET_R_Y	(21.0f)
#define PLAYER_BULLET_OFFSET_L_X	(12.0f)
#define PLAYER_BULLET_OFFSET_L_Y	(21.0f)
#define PLAYER_BULLET_INTERVAL  (60)

//弾の矩形判定
#define PLAYER_BULLET_BOX_COLLISION_WIDTH (20)
#define PLATER_BULLET_BOX_COLLISION_HEIGHT (20)

// ジャンプ力
#define PLAYER_JUMP_POWER (10.0f)

// 重力
#define PLAYER_GRAVITY (0.45f)

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
	g_MotionData.walkR = LoadGraph("Data/Player/Player_WalkR.png");
	g_MotionData.shotR = LoadGraph("Data/Player/Player_ShotR.png");
	g_MotionData.jump_upR = LoadGraph("Data/Player/Player_JumpUpR.png");
	g_MotionData.jump_fallR = LoadGraph("Data/Player/Player_JumpFallR.png");
	g_MotionData.walkL = LoadGraph("Data/Player/Player_WalkL.png");
	g_MotionData.shotL = LoadGraph("Data/Player/Player_ShotL.png");
	g_MotionData.jump_upL = LoadGraph("Data/Player/Player_JumpUpL.png");
	g_MotionData.jump_fallL = LoadGraph("Data/Player/Player_JumpFallL.png");
}

void StartPlayer()
{
	// 生存フラグを立てる
	g_PlayerData.active = true;


	// 矩形判定設定
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

	//これ以上重力を増やさせない
	if (g_PlayerData.move.y > 20.0f)
	{
		g_PlayerData.move.y = 0;
	}

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
	}
	// 右入力
	else if (IsInputKey(KEY_RIGHT))
	{
		g_PlayerData.move.x = PLAYER_MOVE_SPEED;
		g_PlayerData.isTurn = false;
	}
	g_PlayerData.isAtk = false;
	//Zキー入力
	if (IsInputKey(KEY_Z))
	{
		g_PlayerData.isAtk = true;
		PlayerData* player = GetPlayer();

		float fireRX = g_PlayerData.pos.x + PLAYER_BULLET_OFFSET_R_X;
		float fireRY = g_PlayerData.pos.y + PLAYER_BULLET_OFFSET_R_Y;
		float fireLX = g_PlayerData.pos.x + PLAYER_BULLET_OFFSET_L_X;
		float fireLY = g_PlayerData.pos.y + PLAYER_BULLET_OFFSET_L_Y;

		BoxCollision bulletbox = { 0 };

		bulletbox.width = PLAYER_BULLET_BOX_COLLISION_WIDTH;
		bulletbox.height = PLATER_BULLET_BOX_COLLISION_HEIGHT;

		if (g_PlayerData.bulletInterval <= 0)
		{
			if (player->active)
			{
				if (g_PlayerData.isTurn == true)
				{
					RequestFireBullet(STRAIGHT_BULLET_TYPE_PLAYER, PLAYER_BULLET_LIFE, fireRX - 20, fireRY - 15, -PLAYER_BULLET_SPEED_X,
						PLAYER_BULLET_SPEED_Y, bulletbox, BULLET_COLLISION_TAG_PLAYER);
					g_PlayerData.isFire = true;
				}
				if (!g_PlayerData.isTurn)
				{
					RequestFireBullet(STRAIGHT_BULLET_TYPE_PLAYER, PLAYER_BULLET_LIFE, fireRX, fireRY - 15, PLAYER_BULLET_SPEED_X,
						PLAYER_BULLET_SPEED_Y, bulletbox, BULLET_COLLISION_TAG_PLAYER);
					g_PlayerData.isFire = true;
				}
			}
			// インターバル設定
			g_PlayerData.bulletInterval = PLAYER_BULLET_INTERVAL;
		}

	}
	//スペース入力
	if (IsTriggerKey(KEY_SPACE) && !g_PlayerData.isAir)
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

	// 移動処理
	g_PlayerData.pos.x += g_PlayerData.move.x;
	g_PlayerData.pos.y += g_PlayerData.move.y;
}

void DrawPlayer()
{
	// 死んでいたら処理しない
	if (!g_PlayerData.active) return;

	//左向きか
	if (g_PlayerData.isTurn == true)
	{
		if (g_PlayerData.isAir == true) //空中か
		{
			if (g_PlayerData.move.y < 0) //上昇中
			{
				if (g_PlayerData.isAtk == true) //攻撃した瞬間
				{
					DrawGraph(g_PlayerData.pos.x, g_PlayerData.pos.y - 15, g_MotionData.shotL, TRUE); //攻撃表示
				}
				else
				{
					DrawGraph(g_PlayerData.pos.x, g_PlayerData.pos.y - 15, g_MotionData.jump_upL, TRUE); //上昇表示
				}
			}
			else //下降中
			{
				if (g_PlayerData.isAtk == true) //攻撃した瞬間
				{
					DrawGraph(g_PlayerData.pos.x, g_PlayerData.pos.y - 15, g_MotionData.shotL, TRUE); //攻撃表示
				}
				else
				{
					DrawGraph(g_PlayerData.pos.x, g_PlayerData.pos.y - 15, g_MotionData.jump_fallL, TRUE); //下降表示
				}
			}
		}
		else //歩いていたら
		{
			if (g_PlayerData.isAtk == true) //攻撃した瞬間
			{
				DrawGraph(g_PlayerData.pos.x, g_PlayerData.pos.y - 15, g_MotionData.shotL, TRUE); //攻撃表示
			}
			else
			{
				DrawGraph(g_PlayerData.pos.x, g_PlayerData.pos.y - 15, g_MotionData.walkL, TRUE); //歩き表示
			}
		}
	}
	else //左向きではない(右向き)
	{
		if (g_PlayerData.isAir == true) //空中か
		{
			if (g_PlayerData.move.y < 0) //上昇中
			{
				if (g_PlayerData.isAtk == true) //攻撃した瞬間
				{
					DrawGraph(g_PlayerData.pos.x, g_PlayerData.pos.y - 15, g_MotionData.shotR, TRUE); //攻撃表示
				}
				else
				{
					DrawGraph(g_PlayerData.pos.x, g_PlayerData.pos.y - 15, g_MotionData.jump_upR, TRUE); //上昇表示
				}
			}
			else //下降中
			{
				if (g_PlayerData.isAtk == true) //攻撃した瞬間
				{
					DrawGraph(g_PlayerData.pos.x, g_PlayerData.pos.y - 15, g_MotionData.shotR, TRUE); //攻撃表示
				}
				else
				{
					DrawGraph(g_PlayerData.pos.x, g_PlayerData.pos.y - 15, g_MotionData.jump_fallR, TRUE); //下降表示
				}
			}
		}
		else //歩いていたら
		{
			if (g_PlayerData.isAtk == true) //攻撃した瞬間
			{
				DrawGraph(g_PlayerData.pos.x, g_PlayerData.pos.y - 15, g_MotionData.shotR, TRUE); //攻撃表示
			}
			else
			{
				DrawGraph(g_PlayerData.pos.x, g_PlayerData.pos.y - 15, g_MotionData.walkR, TRUE); //歩き表示
			}
		}
	}
}


void FinPlayer()
{
	DeleteGraph(g_MotionData.jump_fallL);
	DeleteGraph(g_MotionData.jump_fallR);
	DeleteGraph(g_MotionData.jump_upL);
	DeleteGraph(g_MotionData.jump_upR);
	DeleteGraph(g_MotionData.shotL);
	DeleteGraph(g_MotionData.shotR);
	DeleteGraph(g_MotionData.walkL);
	DeleteGraph(g_MotionData.walkR);
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

void PlayerHitBreakBlockX(MapChipData mapChipData)
{
	PlayerData player = g_PlayerData;
	BreakBlockData* Bblock = mapChipData.Bdata;
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
		Bblock->pos.x, Bblock->pos.y, MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT))
	{
		// 左からあたったか
		if (player.move.x > 0.0f)
		{
			// 左に押し出す
			g_PlayerData.pos.x -= (x + w) - Bblock->pos.x;
		}
		// 右からあたったか
		else if (player.move.x < 0.0f)
		{
			// 右に押し出す
			g_PlayerData.pos.x += (Bblock->pos.x + MAP_CHIP_WIDTH) - x;
		}
	}
}

void PlayerHitBreakBlockY(MapChipData mapChipData)
{
	PlayerData player = g_PlayerData;
	BreakBlockData* Bblock = mapChipData.Bdata;
	const float POS_OFFSET = PLAYER_MAP_COLLISION_OFFSET;
	const float SIZE_OFFSET = PLAYER_MAP_COLLISION_OFFSET * 2;

	// ターンフラグは前回のものにしないと反転した分ずれる
	player.isTurn = g_PrevPlayerData.isTurn;

	// 当たり判定のボックス計算
	float x, y, w, h;
	CalcBoxCollision(player, x, y, w, h);

	// まだ当たっているなら縦に当たっている
	if (CheckSquareSquare(x + POS_OFFSET, y + POS_OFFSET, w - SIZE_OFFSET, h - SIZE_OFFSET,
		Bblock->pos.x, Bblock->pos.y, MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT))
	{
		// Y移動量を0にする
		g_PlayerData.move.y = 0.0f;

		// 上からあたったか
		if (player.move.y > 0.0f)
		{
			// 上に押し出す
			g_PlayerData.pos.y -= (y + h) - Bblock->pos.y;
			g_PlayerData.isAir = false;
		}
		// 下からあたったか
		else if (player.move.y < 0.0f)
		{
			// 下に押し出す
			g_PlayerData.pos.y += (Bblock->pos.y + MAP_CHIP_WIDTH) - y;
		}
	}
}

void CalcBoxCollision(PlayerData player, float& x, float& y, float& w, float& h)
{
	x = player.pos.x;
	y = player.pos.y;
	w = player.boxCollision.width;
	h = player.boxCollision.height;
}

void PlayerDead()
{
	g_PlayerData.active = false;
}

void PlayerHitNomalEnemy()
{
	PlayerDead();
}

void PlayerHitSwordEnemy()
{
	PlayerDead();
}

