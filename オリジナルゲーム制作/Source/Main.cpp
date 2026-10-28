#include "DxLib.h"

//プログラムはWinMainから始まる
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	if (DxLib_Init() == -1)   //DXライブラリ初期化処理
	{
		return - 1;   //エラーが起きたら直ちに終了
	}

	//描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	//ゲームのメインループ
	while (ProcessMessage() >= 0)
	{
		//画面をクリア
		ClearDrawScreen();

		//エスケープキーで終了
		if (CheckHitKey(KEY_INPUT_ESCAPE))break;

		//画面フリップ
		ScreenFlip();
	}

	DxLib_End();    //DXライブラリ使用で終了処理

	return 0;   //ソフトの終了
}