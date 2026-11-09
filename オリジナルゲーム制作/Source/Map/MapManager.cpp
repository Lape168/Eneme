#include "MapManager.h"
#include "MapParameter.h"
#include "MapChip.h"
#include "Block.h"
#include "../Player/Player.h"
#include "../Enemy/EnemyManager.h"
#include "../Enemy/Nomal.h"

// キャラクターの周囲何マスまでチェックするか
#define CHECK_ROUND_NUM (2)

void InitMap()
{
}

void LoadMap()
{
	LoadMapChipData();
	LoadBlock();
}

void StartMap()
{
	CreateMap();
}

void DrawMap()
{
	// ブロック描画
	DrawBlock();
}

void FinMap()
{
}

void ChceckMapPlayerCollision()
{
	PlayerData* player = GetPlayer();
	// プレイヤーの足元の座標をマップチップのインデックスに変換
	int playerX = (int)(player->pos.x / MAP_CHIP_WIDTH);
	int playerY = (int)((player->pos.y + PLAYER_HEIGHT) / MAP_CHIP_HEIGHT);
	// プレイヤーの左上にあるマップチップインデックス
	int left = playerX - CHECK_ROUND_NUM;
	int top = playerY - CHECK_ROUND_NUM;
	// プレイヤーの右下にあるマップチップインデックス
	int right = playerX + CHECK_ROUND_NUM;
	int bottom = playerY + CHECK_ROUND_NUM;

	// まずはX軸でチェックする

	// 左上から3マスずつチェックしていく
	for (int y = top; y <= bottom; y++)
	{
		// マップチップからはみ出したら処理しなくていい
		if (y < 0 || y >= MAP_CHIP_Y_NUM) continue;

		for (int x = left; x <= right; x++)
		{
			// マップチップからはみ出したら処理しなくていい
			if (x < 0 || x >= MAP_CHIP_X_NUM) continue;

			// マップチップ番号を取得
			MapChipData mapChipData = GetMapChipData(x, y);
			switch (mapChipData.mapChip)
			{
			case NORMAL_BLOCK:
				PlayerHitNormalBlockX(mapChipData);
				break;
			}
		}
	}

	// X軸チェック後にY軸チェックする

	// 左上から3マスずつチェックしていく
	for (int y = top; y <= bottom; y++)
	{
		// マップチップからはみ出したら処理しなくていい
		if (y < 0 || y >= MAP_CHIP_Y_NUM) continue;

		for (int x = left; x <= right; x++)
		{
			// マップチップからはみ出したら処理しなくていい
			if (x < 0 || x >= MAP_CHIP_X_NUM) continue;

			// マップチップ番号を取得
			MapChipData mapChipData = GetMapChipData(x, y);
			switch (mapChipData.mapChip)
			{
			case NORMAL_BLOCK:
				PlayerHitNormalBlockY(mapChipData);
				break;
			}
		}
	}

}

//void CheckMapNomalEnemyCollision()
//{
//	NomalEnemyData* nomalenemy = GetNomalEnemy();
//	// 通常敵の足元の座標をマップチップのインデックスに変換
//	int nomalenemyX = (int)(nomalenemy->pos.x / MAP_CHIP_WIDTH);
//	int nomalenemyY = (int)((nomalenemy->pos.y + NOMAL_ENEMY_HEIGHT) / MAP_CHIP_HEIGHT);
//	// 通常敵の左上にあるマップチップインデックス
//	int left = nomalenemyX - CHECK_ROUND_NUM;
//	int top = nomalenemyY - CHECK_ROUND_NUM;
//	// 通常敵の右下にあるマップチップインデックス
//	int right = nomalenemyX + CHECK_ROUND_NUM;
//	int bottom = nomalenemyY + CHECK_ROUND_NUM;
//
//	// まずはX軸でチェックする
//
//	// 左上から3マスずつチェックしていく
//	for (int y = top; y <= bottom; y++)
//	{
//		// マップチップからはみ出したら処理しなくていい
//		if (y < 0 || y >= MAP_CHIP_Y_NUM) continue;
//
//		for (int x = left; x <= right; x++)
//		{
//			// マップチップからはみ出したら処理しなくていい
//			if (x < 0 || x >= MAP_CHIP_X_NUM) continue;
//
//			// マップチップ番号を取得
//			MapChipData mapChipData = GetMapChipData(x, y);
//			switch (mapChipData.mapChip)
//			{
//			case NORMAL_BLOCK:
//				NomalEnemyHitNormalBlockX(mapChipData);
//				break;
//			}
//		}
//	}
//
//	// X軸チェック後にY軸チェックする
//
//	// 左上から3マスずつチェックしていく
//	for (int y = top; y <= bottom; y++)
//	{
//		// マップチップからはみ出したら処理しなくていい
//		if (y < 0 || y >= MAP_CHIP_Y_NUM) continue;
//
//		for (int x = left; x <= right; x++)
//		{
//			// マップチップからはみ出したら処理しなくていい
//			if (x < 0 || x >= MAP_CHIP_X_NUM) continue;
//
//			// マップチップ番号を取得
//			MapChipData mapChipData = GetMapChipData(x, y);
//			switch (mapChipData.mapChip)
//			{
//			case NORMAL_BLOCK:
//				NomalEnemyHitNormalBlockY(mapChipData);
//				break;
//			}
//		}
//	}
//}

