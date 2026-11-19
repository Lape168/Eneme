#include "BreakBlock.h"
#include "../Camera/Camera.h"

BreakBlockData g_BreakBlocks[BLOCK_MAX] = { 0 };
int g_BreakBlockHandle[BLOCK_TYPE_MAX] = { 0 };

void InitBreakBlock()
{
	BreakBlockData* Bblock = g_BreakBlocks;
	for (int i = 0; i < BLOCK_MAX; i++, Bblock++)
	{
		Bblock->active = false;
		Bblock->pos = VGet(0.0f, 0.0f, 0.0f);
		Bblock->type = MAP_CHIP_NONE;
	}
}

void LoadBreakBlock()
{
	g_BreakBlockHandle[BREAK_BLOCK] = LoadGraph("Data/Map/Break_Block.png");
}

void StartBreakBlock()
{
}

void StepBreakBlock()
{
}

void DrawBreakBlock()
{
	// スクロールのためカメラを取得
	CameraData camera = GetCamera();

	BreakBlockData* Bblock = g_BreakBlocks;
	for (int i = 0; i < BLOCK_MAX; i++, Bblock++)
	{
		if (Bblock->active)
		{
			DrawGraph((int)(Bblock->pos.x - camera.pos.x), (int)(Bblock->pos.y - camera.pos.y), Bblock->handle, TRUE);
		}
	}
}

void FinBreakBlock()
{
}

BreakBlockData* CreateBreakBlock(MapChipType type, VECTOR pos)
{
	// 未使用のブロックを探す
	BreakBlockData* Bblock = g_BreakBlocks;
	for (int i = 0; i < BLOCK_MAX; i++, Bblock++)
	{
		if (!Bblock->active)
		{
			// ブロック生成
			Bblock->active = true;
			Bblock->handle = g_BreakBlockHandle[type];
			Bblock->pos = pos;
			Bblock->type = type;
			return Bblock;
		}
	}

	return nullptr;
}

BreakBlockData* GetBreakBlocks()
{
	return g_BreakBlocks;
}
