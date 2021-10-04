// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

USTRUCT()
struct FTileFace
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere)
	int testInt;

	UPROPERTY(EditAnywhere)
	TArray<int> test2;

	FTileFace() {
		//testInt = 0;
		//test2 = TArray<int>;
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
	TArray<FTileFace> AllowedNeighbours;

	UPROPERTY(EditAnywhere)
	FTileFace testFace;
};
