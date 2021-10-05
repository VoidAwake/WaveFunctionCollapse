// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridCell.h"
#include "Grid.generated.h"

UCLASS()
class WAVEFUNCTIONCOLLAPSE_API AGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Grid(int Width, int Depth, int Height);
	//~Grid();

	UPROPERTY(EditAnywhere)
	int Width;

	UPROPERTY(EditAnywhere)
	int Depth;
	
	UPROPERTY(EditAnywhere)
	int Height;

	UPROPERTY(EditAnywhere)
	float TileSize;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AGridCell> GridCellToSpawn;

	TArray<AGridCell*> GridCells;

	AGridCell* GetGridCell(int x, int y, int z);

	void Clear();

	void ForEachGridCell(TFunctionRef<void(AGridCell*)> Func);

	void ForEachGridCell(TFunctionRef<void(AGridCell*, int, int, int)> Func);

	void GenerateGrid(TArray<TSubclassOf<ATile>> TileSet);
};
