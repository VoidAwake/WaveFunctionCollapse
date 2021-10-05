// Fill out your copyright notice in the Description page of Project Settings.

#include "Grid.h"
#include "Tile.h"
#include "Engine/World.h"

// Sets default values for this component's properties
AGrid::AGrid()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));

	// ...
}

// Called when the game starts or when spawned
void AGrid::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ...
}

AGridCell* AGrid::GetGridCell(int x, int y, int z)
{
	return GridCells[x * Depth * Height + y * Height + z];
}

void AGrid::Clear()
{
	for (auto GridCell : GridCells) {
		if (GridCell) {
			GridCell->Clear();

			GridCell->Destroy();
		}
	}

	GridCells.Empty();
}

void AGrid::ForEachGridCell(TFunctionRef<void(AGridCell*)> Func)
{
	ForEachGridCell([&](AGridCell* GridCell, int x, int y, int z) {
		Func(GridCell);
		});
}

void AGrid::ForEachGridCell(TFunctionRef<void(AGridCell*, int, int, int)> Func)
{
	for (int x = 0; x < Width; x++) {
		for (int y = 0; y < Depth; y++) {
			for (int z = 0; z < Height; z++) {
				Func(GetGridCell(x, y, z), x, y, z);
			}
		}
	}
}

void AGrid::GenerateGrid(TArray<TSubclassOf<ATile>> TileSet)
{
	Clear();

	for (int x = 0; x < Width; x++) {
		for (int y = 0; y < Depth; y++) {
			for (int z = 0; z < Height; z++) {
				FVector SpawnPosition = GetActorLocation() + FVector(x, y, z) * TileSize;

				AGridCell* SpawnedGridCell = GetWorld()->SpawnActor<AGridCell>(GridCellToSpawn, SpawnPosition, FRotator::ZeroRotator);

				GridCells.Add(SpawnedGridCell);

				SpawnedGridCell->Initialise(TileSet);
			}
		}
	}
}

