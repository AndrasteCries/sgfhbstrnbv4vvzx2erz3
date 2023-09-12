// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMazeGameMode.h"
#include "Engine.h"

AMyMazeGameMode::AMyMazeGameMode() {
	PrimaryActorTick.bCanEverTick = true;
}

void AMyMazeGameMode::BeginPlay() {
	
	Super::BeginPlay();
	FVector Location = FVector(0, 0, 0);
	FRotator Rotation = FRotator::ZeroRotator;
	Generator = GetWorld()->SpawnActor<AMazeGenerator>(AMazeGenerator::StaticClass(), Location, Rotation);
	UE_LOG(LogTemp, Warning, TEXT("GENERATOR SPAWNED"));
}


void AMyMazeGameMode::PostLogin(APlayerController* NewPlayer) {
	//if (!MazeGenerated) {
	//	if (APlayerController* Controller = Cast<APlayerController>(NewPlayer)) {
	//		SpawnPlayer(NewPlayer);
	//	}
	//}
}

AMazeGeneratorCell* AMyMazeGameMode::GetSpawnPoint()
{
	for (int32 i = 0; i < SpawnPoints.Num(); i++) {
		int32 Slot = FMath::RandRange(0, SpawnPoints.Num() - 1);
		if (SpawnPoints[Slot]) {
			return SpawnPoints[Slot];
		}
	}
	return nullptr;
}

void AMyMazeGameMode::SpawnPlayer(APlayerController* NewPlayer) {
	AMazeGeneratorCell* PlayerSpawn = GetSpawnPoint();
	if (PlayerSpawn) {
		FVector Location = PlayerSpawn->GetActorLocation();
		FRotator Rotation = PlayerSpawn->GetActorRotation();
		if (APawn* Pawn = GetWorld()->SpawnActor<APawn>(DefaultPawnClass, Location, Rotation)) {
			NewPlayer->Possess(Pawn);
		}
	}
	else {
		FVector Location = FVector(0, 0, 1000);
		FRotator Rotation = FRotator::ZeroRotator;
		if (APawn* Pawn = GetWorld()->SpawnActor<APawn>(DefaultPawnClass, Location, Rotation)) {
			NewPlayer->Possess(Pawn);
		}
	}
}

void AMyMazeGameMode::SetSpawnPoints(TArray<AMazeGeneratorCell*> WorldSpawnPoints) {
	SpawnPoints = WorldSpawnPoints;
}

void AMyMazeGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}