// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMazeGameMode.h"
#include "Engine.h"

AMyMazeGameMode::AMyMazeGameMode() {
	PrimaryActorTick.bCanEverTick = true;
}

void AMyMazeGameMode::BeginPlay() {
	
	Super::BeginPlay();
}


void AMyMazeGameMode::PostLogin(APlayerController* NewPlayer) {
	if (!MazeGenerated) {
		if (APlayerController* Controller = Cast<APlayerController>(NewPlayer)) {
			UE_LOG(LogTemp, Warning, TEXT("QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"));
			SpawnPlayer(NewPlayer);
		}
	}
}

ASpawnPoint* AMyMazeGameMode::GetSpawnPoint()
{
	UE_LOG(LogTemp, Warning, TEXT("NUM111111 ====================== %d"), SpawnPoints.Num());
	for (int32 i = 0; i < SpawnPoints.Num(); i++) {
		int32 Slot = FMath::RandRange(0, SpawnPoints.Num() - 1);
		if (SpawnPoints[Slot]) {
			UE_LOG(LogTemp, Warning, TEXT("ITERARION"));
			return SpawnPoints[Slot];
		}
	}
	return nullptr;
}

void AMyMazeGameMode::SpawnPlayer(APlayerController* NewPlayer) {
	ASpawnPoint* PlayerSpawn = GetSpawnPoint();
	if (PlayerSpawn) {
		UE_LOG(LogTemp, Warning, TEXT("1111111111111111111111111111111111111111111111"));
		FVector Location = PlayerSpawn->GetActorLocation();
		FRotator Rotation = PlayerSpawn->GetActorRotation();
		if (APawn* Pawn = GetWorld()->SpawnActor<APawn>(DefaultPawnClass, Location, Rotation)) {
			NewPlayer->Possess(Pawn);
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("22222222222222222222222222222222222222222222222222222222"));
		FVector Location = FVector(0, 0, 1000);
		FRotator Rotation = FRotator::ZeroRotator;
		if (APawn* Pawn = GetWorld()->SpawnActor<APawn>(DefaultPawnClass, Location, Rotation)) {
			NewPlayer->Possess(Pawn);
		}
	}
}

void AMyMazeGameMode::SetSpawnPoints(TArray<ASpawnPoint*> WorldSpawnPoints) {
	SpawnPoints = WorldSpawnPoints;
}

void AMyMazeGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}