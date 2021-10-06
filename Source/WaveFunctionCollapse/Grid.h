// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "GridCell.h"
#include "Direction.h"
#include "Grid.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class WAVEFUNCTIONCOLLAPSE_API UGrid : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UGrid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	int Width;

	UPROPERTY(EditAnywhere)
	int Depth;
	
	UPROPERTY(EditAnywhere)
	int Height;

	UPROPERTY(EditAnywhere)
	float TileSize;

	TArray<AGridCell*> GridCells;

	AGridCell* GetGridCell(int x, int y, int z);

	void Clear();

	void ForEachGridCell(TFunctionRef<void(AGridCell*)> Func);

	void ForEachGridCell(TFunctionRef<void(AGridCell*, int, int, int)> Func);

	void GenerateGrid(TArray<TSubclassOf<ATile>> TileSet);

	AGridCell* GetAdjacentCell(int x, int y, int z, EDirection Direction);

	AGridCell* GetAdjacentCell(AGridCell* GridCell, EDirection Direction);
};
