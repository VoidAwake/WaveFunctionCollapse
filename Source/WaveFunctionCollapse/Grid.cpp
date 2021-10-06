// Fill out your copyright notice in the Description page of Project Settings.

#include "Grid.h"
#include "Tile.h"
#include "GridCell.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UGrid::UGrid()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void UGrid::BeginPlay()
{
	Super::BeginPlay();
	
}

void UGrid::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

AGridCell* UGrid::GetGridCell(int x, int y, int z)
{
	return GridCells[x * Depth * Height + y * Height + z];
}

void UGrid::Clear()
{
	for (auto GridCell : GridCells) {
		if (GridCell) {
			GridCell->Clear();

			GridCell->Destroy();
		}
	}

	GridCells.Empty();
}

void UGrid::ForEachGridCell(TFunctionRef<void(AGridCell*)> Func)
{
	ForEachGridCell([&](AGridCell* GridCell, int x, int y, int z) {
		Func(GridCell);
		});
}

void UGrid::ForEachGridCell(TFunctionRef<void(AGridCell*, int, int, int)> Func)
{
	for (int x = 0; x < Width; x++) {
		for (int y = 0; y < Depth; y++) {
			for (int z = 0; z < Height; z++) {
				Func(GetGridCell(x, y, z), x, y, z);
			}
		}
	}
}

void UGrid::GenerateGrid(TArray<TSubclassOf<ATile>> TileSet)
{
	Clear();

	for (int x = 0; x < Width; x++) {
		for (int y = 0; y < Depth; y++) {
			for (int z = 0; z < Height; z++) {
				FVector SpawnPosition = GetOwner()->GetActorLocation() + FVector(x, y, z) * TileSize;

				AGridCell* SpawnedGridCell = GetWorld()->SpawnActor<AGridCell>(SpawnPosition, FRotator::ZeroRotator);

				SpawnedGridCell->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepWorldTransform);

				GridCells.Add(SpawnedGridCell);

				SpawnedGridCell->Initialise(TileSet, x, y, z);
			}
		}
	}
}

AGridCell* UGrid::GetAdjacentCell(int x, int y, int z, EDirection Direction)
{
	switch (Direction)
	{
		case EDirection::RIGHT:
			if (x > 0)
				return GetGridCell(x - 1, y, z);
			break;
		case EDirection::LEFT:
			if (x < Width - 1)
				return GetGridCell(x + 1, y, z);
			break;
		case EDirection::BACK:
			if (y > 0)
				return GetGridCell(x, y - 1, z);
			break;
		case EDirection::FORWARD:
			if (y < Depth - 1)
				return GetGridCell(x, y + 1, z);
			break;
		case EDirection::DOWN:
			if (z > 0)
				return GetGridCell(x, y, z - 1);
			break;
		case EDirection::UP:
			if (z < Height - 1)
				return GetGridCell(x, y, z + 1);
			break;
	}

	return nullptr;
}


AGridCell* UGrid::GetAdjacentCell(AGridCell* GridCell, EDirection Direction)
{
	if (GridCell)
		return GetAdjacentCell(GridCell->GridPosition.X, GridCell->GridPosition.Y, GridCell->GridPosition.Z, Direction);
	else
		return nullptr;
}

