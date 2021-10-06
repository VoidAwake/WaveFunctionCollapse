// Fill out your copyright notice in the Description page of Project Settings.

#include "GridCell.h"
#include "Engine/World.h"

// Sets default values
AGridCell::AGridCell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
}

// Called when the game starts or when spawned
void AGridCell::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGridCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGridCell::Observe()
{
	// Pick a random TileType from the wave
	TSubclassOf<ATile> TileTypeToSpawn = Wave[FMath::RandRange(0, Wave.Num() - 1)];

	Wave.Empty();

	Wave.Add(TileTypeToSpawn);

	CreateTile(TileTypeToSpawn);

	bChanged = true;

	Tile->AllowedNeighbours;

	Wave[0]->GetDefaultObject<ATile>()->AllowedNeighbours;
}

void AGridCell::Clear()
{
	if (Tile)
		Tile->Destroy();
}

void AGridCell::CreateTile(TSubclassOf<ATile> TileTypeToSpawn)
{
	Clear();
	
	Tile = GetWorld()->SpawnActor<ATile>(TileTypeToSpawn, GetActorLocation(), FRotator::ZeroRotator);

	// TODO: May need to revisit this
	Tile->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
}

void AGridCell::Initialise(TArray<TSubclassOf<ATile>> TileSet, int x, int y, int z)
{
	for (auto TileType : TileSet) {
		Wave.Add(TileType);
	}

	GridPosition = FVector(x, y, z);
}

bool AGridCell::Allows(TSubclassOf<ATile> NeighbourTileType, EDirection Direction)
{
	for (auto TileType : Wave) {
		if (TileType->GetDefaultObject<ATile>()->AllowedNeighboursInDirection(Direction).Contains(NeighbourTileType))
			return true;
	}

	return false;
}
