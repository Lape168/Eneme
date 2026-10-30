#include "DxLib.h"
#include "GameSetting/GameSetting.h"
#include "Scene/SceneManager.h"
#include "Input/Input.h"

//プログラムはWinMainから始まる
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	if (DxLib_Init() == -1)   //DXライブラリ初期化処理
	{
		return - 1;   //エラーが起きたら直ちに終了
	}
	// ウィンドウモードON
	ChangeWindowMode(TRUE);

	// 画面解像度の設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLOR_DEPTH);

	//描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	// ウィンドウサイズ設定
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	// 入力システムを初期化
	InitInput();

	//ゲームのメインループ
	while (ProcessMessage() >= 0)
	{
		//ループ処理前に1ミリ秒止めると処理が安定する
		Sleep(1);
		
		//画面をクリア
		ClearDrawScreen();

		// 入力を更新
		UpdateInput();

		// シーン管理の更新
		SceneManagerUpdate();

		//エスケープキーで終了
		if (CheckHitKey(KEY_INPUT_ESCAPE))break;

		//画面フリップ
		ScreenFlip();
	}

	DxLib_End();    //DXライブラリ使用で終了処理

	return 0;   //ソフトの終了
}