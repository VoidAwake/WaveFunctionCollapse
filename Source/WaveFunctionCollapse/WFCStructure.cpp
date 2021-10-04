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
		Clear();
		GenerateRandom();

		bRegenerate = false;
	}
}

void AWFCStructure::GenerateRandom()
{
	for (int x = 0; x < Depth; x++) {
		for (int y = 0; y < Width; y++) {
			for (int z = 0; z < Height; z++) {
				TSubclassOf<ATile> TileToSpawn = TileSet[FMath::RandRange(0, TileSet.Num() - 1)];

				FVector SpawnPosition = GetActorLocation() + FVector(x, y, z) * TileSize;

				ATile* SpawnedTile = GetWorld()->SpawnActor<ATile>(TileToSpawn, SpawnPosition, FRotator::ZeroRotator);

				Tiles.Add(SpawnedTile);
			}
		}
	}
}

bool AWFCStructure::ShouldTickIfViewportsOnly() const
{
	return true;
}

void AWFCStructure::Clear()
{
	for (auto Tile : Tiles) {
		Tile->Destroy();
	}

	Tiles.Empty();
}

