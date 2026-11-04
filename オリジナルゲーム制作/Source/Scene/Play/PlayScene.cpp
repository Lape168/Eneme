#include "DxLib.h"
#include "../../Scene/SceneManager.h"
#include "../../Map/MapManager.h"
#include "../../Player/Player.h"
#include "../../Camera/Camera.h"
#include "../../Collision/Collision.h"
#include "../../Bullet/BulletManager.h"


// 背景のスピード
#define BACK_GROUND_SPEED (-1.5f)

void InitPlayScene()
{
	// プレイヤー初期化
	InitPlayer();

	// マップ初期化
	InitMap();

	//弾の初期化
	InitBullet();
	
	// カメラ初期化
	InitCamera();
}

void LoadPlayScene()
{
	// プレイヤーロード
	LoadPlayer();

	// マップをロード
	LoadMap();

	//弾をロード
	LoadBullet();
}

void StartPlayScene()
{
	// プレイヤー開始
	StartPlayer();

	// マップを開始
	StartMap();
}

void StepPlayScene()
{
	// プレイヤーステップ
	StepPlayer();

	// カメラステップ
	StepCamera();

	//弾ステップ
	StepBullet();
}

void UpdatePlayScene()
{
	// マップ更新
	// プレイヤー更新
	UpdatePlayer();
	
	//弾を更新
	UpdateBullet();

	// 当たり判定
	CheckCollision();
}

void DrawPlayScene()
{
	// マップ描画
	DrawMap();

	// プレイヤー描画
	DrawPlayer();

	//弾を描画
	DrawBullet();

	// カメラ描画
	DrawCamera();
}

void FinPlayScene()
{
	// マップ終了
	FinMap();

	// プレイヤー終了
	FinPlayer();

	//弾を終了
	FinBullet();
}
