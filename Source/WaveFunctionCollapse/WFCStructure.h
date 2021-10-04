// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.h"
#include "WFCStructure.generated.h"

UCLASS()
class WAVEFUNCTIONCOLLAPSE_API AWFCStructure : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWFCStructure();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ATile>> TileSet;

	UPROPERTY(EditAnywhere)
	int Width;

	UPROPERTY(EditAnywhere)
	int Height;

	UPROPERTY(EditAnywhere)
	int Depth;

	UPROPERTY(EditAnywhere)
	float TileSize;

	void GenerateRandom();

	virtual bool ShouldTickIfViewportsOnly() const override;

	UPROPERTY(EditAnywhere)
	bool bRegenerate;

	void Clear();

	TArray<ATile*> Tiles;

};
