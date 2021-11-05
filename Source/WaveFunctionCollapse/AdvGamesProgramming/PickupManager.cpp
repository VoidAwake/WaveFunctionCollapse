// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupManager.h"

#include "Engine/GameEngine.h"

// Sets default values
APickupManager::APickupManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APickupManager::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(WeaponSpawnTimer, this, &APickupManager::SpawnWeaponPickup, SpawnInterval, true, 0.0f);
}

// Called every frame
void APickupManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupManager::Init(const TArray<FVector>& PossibleSpawnLocatinsArg, TSubclassOf<APickup> WeaponPikcupClassArg, float SpawnIntervalArg, FVector SpawnLocationOffsetArg) {
	PossibleSpawnLocations = PossibleSpawnLocatinsArg;
	WeaponPickupClass = WeaponPikcupClassArg;
	SpawnInterval = SpawnIntervalArg;
	SpawnLocationOffset = SpawnLocationOffsetArg;
}

void APickupManager::SpawnWeaponPickup() {
	FVector RandomSpawnLocation = PossibleSpawnLocations[FMath::RandRange(0, PossibleSpawnLocations.Num() - 1)];

	APickup* WeaponPickup = GetWorld()->SpawnActor<APickup>(WeaponPickupClass, RandomSpawnLocation + SpawnLocationOffset, FRotator::ZeroRotator);

	WeaponPickup->SetLifeSpan(PICKUP_LIFETIME);

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::Printf(TEXT("Pickup Spawned")));
}