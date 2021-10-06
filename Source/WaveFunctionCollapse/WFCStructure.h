// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.h"
#include "Grid.h"
#include "GridCell.h"
#include "Containers/Queue.h"
#include "TileSet.h"
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
	UTileSet* TileSet;

	virtual bool ShouldTickIfViewportsOnly() const override;

	UPROPERTY(EditAnywhere)
	AGrid* MyGrid;

	UPROPERTY(EditAnywhere)
	bool bRegenerate;

	UPROPERTY(EditAnywhere)
	bool bClearGrid;

	UPROPERTY(EditAnywhere)
	bool bTestObserve;

	UPROPERTY(EditAnywhere)
	bool bTestPropagate;

	int Observe();

	bool Propagate();

	TQueue<AGridCell*> ChangedCellsQueue;

	FString DirectionToString(EDirection Direction);

	void Generate();
};
