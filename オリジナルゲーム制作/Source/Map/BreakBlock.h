#pragma once
#include "MapParameter.h"

void InitBreakBlock();
void LoadBreakBlock();
void StartBreakBlock();
void StepBreakBlock();
void DrawBreakBlock();
void FinBreakBlock();

BreakBlockData* CreateBreakBlock(MapChipType type, VECTOR pos);
BreakBlockData* GetBreakBlocks();