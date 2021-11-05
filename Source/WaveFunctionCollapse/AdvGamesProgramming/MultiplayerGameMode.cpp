// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerGameMode.h"
#include "EngineUtils.h"
#include "Engine/GameEngine.h"
#include "PlayerHUD.h"
#include "Kismet/GameplayStatics.h"

void AMultiplayerGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessages)
{
	Super::InitGame(MapName, Options, ErrorMessages);

	for (TActorIterator<AProcedurallyGeneratedMap> It(GetWorld()); It; ++It) {
		ProceduralMap = *(It);

		break;
	}

	PickupManager = GetWorld()->SpawnActor<APickupManager>();

	PickupManager->Init(ProceduralMap->Vertices, WeaponPickupClass, WeaponSpawnInterval, WeaponSpawnLocationOffset);
}

void AMultiplayerGameMode::Respawn(AController* Controller)
{
	if (!Controller)
		return;

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::Printf(TEXT("Respawning")));

	Controller->GetPawn()->Destroy();

	FTimerDelegate TimerDel;
	TimerDel.BindUFunction(this, FName("SpawnPawn"), Controller);

	GetWorldTimerManager().SetTimer(RespawnTimer, TimerDel, RespawnInterval, false);
}

void AMultiplayerGameMode::SpawnPawn(AController* Controller)
{
	if (!Controller)
		return;

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::Printf(TEXT("Respawned")));

	AActor* PlayerStart = ChoosePlayerStart(Controller);

	if (!PlayerStart) {
		UE_LOG(LogTemp, Warning, TEXT("Failed to choose PlayerStart"))
			return;
	}

	APawn* Pawn = GetWorld()->SpawnActor<APawn>(DefaultPawnClass, PlayerStart->GetActorLocation(), FRotator::ZeroRotator);

	if (!Pawn) {
		UE_LOG(LogTemp, Warning, TEXT("Failed to spawn DefaultPawnClass"))
			return;
	}

	Controller->Possess(Pawn);
}
