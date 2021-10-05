// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"

Grid::Grid(int Width, int Depth, int Height)
{
	this->Width = Width;
	this->Depth = Depth;
	this->Height = Height;

	for (int x = 0; x < Width; x++) {
		for (int y = 0; y < Depth; y++) {
			for (int z = 0; z < Height; z++) {
				GridCells.Add(new GridCell());
			}
		}
	}
}

Grid::~Grid()
{
	Clear();
}

GridCell* Grid::GetGridCell(int x, int y, int z)
{
	return GridCells[x * Depth * Height + y * Height + z];
}

void Grid::Clear()
{
	for (auto GridCell : GridCells) {
		ATile* Tile = GridCell->Tile;

		if (Tile)
			Tile->Destroy();
	}
}

void Grid::ForEachGridCell(TFunctionRef<void(GridCell*)> Func)
{
	ForEachGridCell([&](GridCell* GridCell, int x, int y, int z) {
		Func(GridCell);
	});
}

void Grid::ForEachGridCell(TFunctionRef<void(GridCell*, int, int, int)> Func)
{
	for (int x = 0; x < Width; x++) {
		for (int y = 0; y < Depth; y++) {
			for (int z = 0; z < Height; z++) {
				Func(GetGridCell(x, y, z), x, y, z);
			}
		}
	}
}
