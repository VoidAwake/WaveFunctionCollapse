// Fill out your copyright notice in the Description page of Project Settings.


#include "WFCStructure.h"
#include "Engine/World.h"

// Sets default values
AWFCStructure::AWFCStructure()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
}

// Called when the game starts or when spawned
void AWFCStructure::BeginPlay()
{
	Super::BeginPlay();
	
	GenerateRandom();
}

// Called every frame
void AWFCStructure::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRegenerate) {
		GenerateRandom();

		bRegenerate = false;
	}
}

void AWFCStructure::GenerateRandom()
{
	if (MyGrid)
		MyGrid->~Grid();

	MyGrid = new Grid(Width, Depth, Height);

	MyGrid->ForEachGridCell([&](GridCell* GridCell, int x, int y, int z) {
		TSubclassOf<ATile> TileToSpawn = TileSet[FMath::RandRange(0, TileSet.Num() - 1)];

		FVector SpawnPosition = GetActorLocation() + FVector(x, y, z) * TileSize;

		ATile* SpawnedTile = GetWorld()->SpawnActor<ATile>(TileToSpawn, SpawnPosition, FRotator::ZeroRotator);

		GridCell->Tile = SpawnedTile;
	});
}

bool AWFCStructure::ShouldTickIfViewportsOnly() const
{
	return true;
}

