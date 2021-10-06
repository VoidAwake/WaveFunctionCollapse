// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Direction.h"
#include "Tile.generated.h"

USTRUCT()
struct FTileFace
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ATile>> TileTypes;
};

USTRUCT()
struct FBoolArray
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<bool> Bools;

	FBoolArray () {
		Bools.Add(true);
		Bools.Add(true);
	}
};

UCLASS()
class WAVEFUNCTIONCOLLAPSE_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TMap<EDirection, FTileFace> AllowedNeighbours;

	TArray<TSubclassOf<ATile>> AllowedNeighboursInDirection(EDirection Direction);

	//UPROPERTY(EditAnywhere)
	//TMap<TSubclassOf<ATile>, FBoolArray> TestFormat;
};
