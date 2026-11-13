#include "DxLib.h"
#include "../../Scene/SceneManager.h"
#include "../../Map/MapManager.h"
#include "../../Player/Player.h"
#include "../../Camera/Camera.h"
#include "../../Collision/Collision.h"
#include "../../Bullet/BulletManager.h"
#include "../../Enemy/EnemyManager.h"


void InitPlayScene()
{
	// プレイヤー初期化
	InitPlayer();

	// マップ初期化
	InitMap();

	//弾の初期化
	InitBullet();

	//敵を初期化
	InitEnemy();
	
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

	//敵をロード
	LoadEnemy();
}

void StartPlayScene()
{
	// プレイヤー開始
	StartPlayer();

	// マップを開始
	StartMap();

	//敵を開始
	StartEnemy();
}

void StepPlayScene()
{
	// プレイヤーステップ
	StepPlayer();

	// カメラステップ
	StepCamera();

	//弾ステップ
	StepBullet();

	//敵ステップ
	StepEnemy();
}

void UpdatePlayScene()
{
	// マップ更新
	// プレイヤー更新
	UpdatePlayer();
	
	//弾を更新
	UpdateBullet();

	//敵を更新
	UpdateEnemy();

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

	//敵を描画
	DrawEnemy();

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

	//敵を終了
	FinEnemy();
}
