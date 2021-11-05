// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "UObject/ConstructorHelpers.h"

APlayerHUD::APlayerHUD() {
	static ConstructorHelpers::FClassFinder<UUserWidget> PlayerHUDObject(TEXT("/Game/Widgets/PlayerHUDWidget"));

	PlayerHUDClass = PlayerHUDObject.Class;

	if (!PlayerHUDClass) {
		UE_LOG(LogTemp, Warning, TEXT("Failed to initialise PlayerHUDClass"))
		return;
	}

	CurrentPlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass);

	if (!CurrentPlayerHUDWidget) {
		UE_LOG(LogTemp, Warning, TEXT("Failed to create UUserWidget"))
		return;
	}

	CurrentPlayerHUDWidget->AddToViewport();

	HealthProgressBar = Cast<UProgressBar>(CurrentPlayerHUDWidget->GetWidgetFromName(TEXT("ProgHealthBar")));


}

void APlayerHUD::SetPlayerHealthBarPercent(float Percent)
{
	if (!HealthProgressBar)
		return;

	HealthProgressBar->SetPercent(Percent);
}

void APlayerHUD::SetHUDVisible(bool bIsVisible)
{
	HealthProgressBar->SetVisibility(bIsVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}


