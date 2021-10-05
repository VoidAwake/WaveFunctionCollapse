// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridCell.h"

/**
 * 
 */
class WAVEFUNCTIONCOLLAPSE_API Grid
{
public:
	Grid(int Width, int Depth, int Height);
	~Grid();

	int Width;
	int Depth;
	int Height;

	TArray<GridCell*> GridCells;

	GridCell* GetGridCell(int x, int y, int z);

	void Clear();

	void ForEachGridCell(TFunctionRef<void(GridCell*)> Func);

	void ForEachGridCell(TFunctionRef<void(GridCell*, int, int, int)> Func);
};
