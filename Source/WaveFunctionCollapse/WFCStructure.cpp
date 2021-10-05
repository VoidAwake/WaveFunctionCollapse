// Fill out your copyright notice in the Description page of Project Settings.


#include "WFCStructure.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"

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
		GenerateRandom();

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
}

void AWFCStructure::GenerateRandom()
{
	//MyGrid = FindComponentByClass<UGrid>();

	if (MyGrid) {
		MyGrid->GenerateGrid(TileSet);

		//MyGrid->ForEachGridCell([&](AGridCell* GridCell) {
		//	TSubclassOf<ATile> TileToSpawn = TileSet[FMath::RandRange(0, TileSet.Num() - 1)];

		//	if (GridCell)
		//		GridCell->CreateTile(TileToSpawn);
		//});
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Could not find Grid"));
	}
}

bool AWFCStructure::ShouldTickIfViewportsOnly() const
{
	return true;
}

int AWFCStructure::Observe()
{
	int MinEntropy = TileSet.Num() + 1;
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
		// TODO: Mark cell as changed

		UE_LOG(LogTemp, Warning, TEXT("Min entropy was %i"), MinEntropy);

		CellWithMinEntropy->Observe();

		return 0; // Continue
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("All cells observed"));

		return 1; // Complete
	}
}

