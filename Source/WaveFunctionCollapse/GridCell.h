// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.h"
#include "Direction.h"
#include "GridCell.generated.h"

UCLASS()
class WAVEFUNCTIONCOLLAPSE_API AGridCell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridCell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	ATile* Tile;

	UPROPERTY(VisibleAnywhere)
	TArray<TSubclassOf<ATile>> Wave;

	void Observe();

	void Clear();

	void CreateTile(TSubclassOf<ATile> TileTypeToSpawn);

	void Initialise(TArray<TSubclassOf<ATile>> TileSet, int x, int y, int z);

	bool bChanged;

	bool Allows(TSubclassOf<ATile> TileType, EDirection Direction);

	FVector GridPosition;

	UPROPERTY(EditAnywhere)
	bool bBorders;
};
