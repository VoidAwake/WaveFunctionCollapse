// Fill out your copyright notice in the Description page of Project Settings.


#include "WFCStructure.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"
#include "Direction.h"

// Sets default values
AWFCStructure::AWFCStructure()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));

	// TODO: Come back to this, for now just set up the grid manually
	//MyGrid = CreateDefaultSubobject<UGrid>(TEXT("Grid Component"));
	//MyGrid->AttachParent = RootComponent;
	//MyGrid->AttachToComponent

	//AddOwnedComponent(MyGrid);

	//MyGrid = FindComponentByClass<UGrid>();

	//UBoxComponent* PickupBoundingBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Bounding Box"));
	//PickupBoundingBox->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AWFCStructure::BeginPlay()
{
	Super::BeginPlay();
	
	//GenerateRandom();
}

// Called every frame
void AWFCStructure::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRegenerate) {
		Generate();

		bRegenerate = false;
	}

	if (bTestObserve) {
		Observe();

		bTestObserve = false;
	}

	if (bClearGrid) {
		if (MyGrid)
			MyGrid->Clear();

		bClearGrid = false;
	}


	if (bTestPropagate) {
		Propagate();

		bTestPropagate = false;
	}
}

bool AWFCStructure::ShouldTickIfViewportsOnly() const
{
	return true;
}

int AWFCStructure::Observe()
{
	if (!TileSet)
		return -1;

	int MinEntropy = TileSet->TileSet.Num() + 1;
	AGridCell* CellWithMinEntropy = nullptr;

	MyGrid->ForEachGridCell([&](AGridCell* GridCell) {
		//if (GridCell->Wave.Num() == 0)
		//	return -1; // Contradiction

		if (GridCell->Wave.Num() == MinEntropy) {
			// TODO: Not properly random
			if (FMath::RandBool()) { // Pick on at random
				MinEntropy = GridCell->Wave.Num();
				CellWithMinEntropy = GridCell;
			}
		}

		// TODO: Duplicate Code
		if (GridCell->Wave.Num() < MinEntropy && GridCell->Wave.Num() > 1) {
			MinEntropy = GridCell->Wave.Num();
			CellWithMinEntropy = GridCell;
		}
	});

	if (CellWithMinEntropy) {
		UE_LOG(LogTemp, Warning, TEXT("Min entropy was %i"), MinEntropy);

		CellWithMinEntropy->Observe();

		ChangedCellsQueue.Enqueue(CellWithMinEntropy);

		return 0; // Continue
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("All cells observed"));

		return 1; // Complete
	}
}

bool AWFCStructure::Propagate()
{
	// TODO: Fix naming convention
	bool changed = false;

	// TODO: Move outside this function
	TArray<EDirection> Directions = {
		EDirection::LEFT,
		EDirection::RIGHT,
		EDirection::FORWARD,
		EDirection::BACK,
		EDirection::UP,
		EDirection::DOWN
	};

	if (MyGrid) {
		while (!ChangedCellsQueue.IsEmpty()) {
			AGridCell* GridCell = *(ChangedCellsQueue.Peek());
			ChangedCellsQueue.Pop();

			UE_LOG(LogTemp, Warning, TEXT("Cell has been changed: Should run once per step"));
			for (auto Direction : Directions) {
				UE_LOG(LogTemp, Warning, TEXT("  %s"), *DirectionToString(Direction));

				AGridCell* AdjacentCell = MyGrid->GetAdjacentCell(GridCell, Direction);

				if (AdjacentCell) {
					TArray<TSubclassOf<ATile>> TilesToRemove;

					for (auto AdjacentWaveTile : AdjacentCell->Wave) {
						// if that tile is not allowed from the current tile
						if (!GridCell->Allows(AdjacentWaveTile, Direction)) {
							TilesToRemove.Add(AdjacentWaveTile);

							FString TileName = AdjacentWaveTile->GetDefaultObject<ATile>()->GetName();

							

							UE_LOG(LogTemp, Warning, TEXT("    %s disallowed"), *TileName);
						}
					}

					if (TilesToRemove.Num() > 0) {
						//AdjacentCell->bChanged = true;

						ChangedCellsQueue.Enqueue(AdjacentCell);

						changed = true;
					}

					for (auto TileToRemove : TilesToRemove) {
						AdjacentCell->Wave.Remove(TileToRemove);
					}

					if (AdjacentCell->Wave.Num() == 0) {
						UE_LOG(LogTemp, Warning, TEXT("    Contradiction"));
					}
					else if (AdjacentCell->Wave.Num() == 1) {
						UE_LOG(LogTemp, Warning, TEXT("    Observed"));
						AdjacentCell->Observe();
					}
				}
				else {
					UE_LOG(LogTemp, Warning, TEXT("    No cell in this direction."));
				}
			}			
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Has been changed? %s"), (changed ? TEXT("true") : TEXT("false")));

	return changed;
}

FString AWFCStructure::DirectionToString(EDirection Direction)
{
	switch (Direction)
	{
	case EDirection::LEFT:
		return FString(TEXT("Left"));
	case EDirection::RIGHT:
		return FString(TEXT("Right"));
	case EDirection::FORWARD:
		return FString(TEXT("Forward"));
	case EDirection::BACK:
		return FString(TEXT("Back"));
	case EDirection::UP:
		return FString(TEXT("Up"));
	case EDirection::DOWN:
		return FString(TEXT("Down"));
	}

	return FString();
}

void AWFCStructure::Generate()
{
	if (!MyGrid)
		return;

	if (!TileSet)
		return;

	MyGrid->GenerateGrid(TileSet->TileSet);

	while (Observe() == 0) {
		Propagate();
	}
}

