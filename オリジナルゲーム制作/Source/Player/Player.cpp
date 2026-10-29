#include "DxLib.h"
#include "Player.h"
#include "../Input/Input.h"
#include "../Bullet/BulletManager.h"


// プレイヤー設定関連
#define PLAYER_DEFAULT_POS_X (400.0f)
#define PLAYER_DEFAULT_POS_Y (200.0f)
#define PLAYER_MOVE_SPEED (4.0f)

// ジャンプ力
#define PLAYER_JUMP_POWER (2.0f)
// 重力
#define PLAYER_GRAVITY (0.001f)

PlayerData g_PlayerData = { 0 };

void InitPlayer()
{
	g_PlayerData.posX = PLAYER_DEFAULT_POS_X;
	g_PlayerData.posY = PLAYER_DEFAULT_POS_Y;
	g_PlayerData.moveX = 0.0f;
	g_PlayerData.moveY = 0.0f;
	g_PlayerData.active = false;
}

void LoadPlayer()
{
	g_PlayerData.handle = LoadGraph("Data/Map/Bleak_Block.png");
}

void StartPlayer()
{
	// 生存フラグを立てる
	g_PlayerData.active = true;


}

void StepPlayer()
{
	// 死んでいたら何もしない
	if (!g_PlayerData.active) return;
	

	// X移動量は毎回リセットする
	g_PlayerData.moveX = 0.0f;

	// Y移動量に重力を反映
	g_PlayerData.moveY += PLAYER_GRAVITY;

	// 左入力
	if (IsInputKey(KEY_LEFT))
	{
		g_PlayerData.moveX = -PLAYER_MOVE_SPEED;
		g_PlayerData.isTurn = true;
	}
	// 右入力
	else if (IsInputKey(KEY_RIGHT))
	{
		g_PlayerData.moveX = PLAYER_MOVE_SPEED;
		g_PlayerData.isTurn = false;
	}
	if (g_PlayerData.isAir == false)
	{
		//スペース入力
		if (IsInputKey(KEY_SPACE))
		{
			g_PlayerData.moveY = -PLAYER_JUMP_POWER;
		}
	}
}

void UpdatePlayer()
{
	// 死んでいたら処理しない
	if (!g_PlayerData.active) return;

	// 上昇しているもしくは落ちている場合は空中フラグを立てる
	if (g_PlayerData.moveY < 0.0f || g_PlayerData.moveY > PLAYER_GRAVITY)
	{
		g_PlayerData.isAir = true;
	}

	// 移動処理
	g_PlayerData.posX += g_PlayerData.moveX;
	g_PlayerData.posY += g_PlayerData.moveY;
}

void DrawPlayer()
{
	// 死んでいたら処理しない
	if (!g_PlayerData.active) return;

	DrawGraph(g_PlayerData.posX, g_PlayerData.posY, g_PlayerData.handle, TRUE);
}

void FinPlayer()
{
	
}

PlayerData GetPlayer()
{
	return PlayerData();
}
