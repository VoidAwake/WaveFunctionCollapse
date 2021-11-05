// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ProcedurallyGeneratedMap.h"
#include "PickupManager.h"
#include "MultiplayerGameMode.generated.h"

/**
 * 
 */
UCLASS()
class WAVEFUNCTIONCOLLAPSE_API AMultiplayerGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APickup> WeaponPickupClass;

	UPROPERTY(EditDefaultsOnly)
	float WeaponSpawnInterval;

	UPROPERTY(EditDefaultsOnly)
	FVector WeaponSpawnLocationOffset;

	UPROPERTY(EditDefaultsOnly)
	float RespawnInterval;

	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessages) override;

	void Respawn(AController* Controller);

private:
	AProcedurallyGeneratedMap* ProceduralMap;

	APickupManager* PickupManager;

	FTimerHandle RespawnTimer;

	UFUNCTION()
	void SpawnPawn(AController* Controller);

};
