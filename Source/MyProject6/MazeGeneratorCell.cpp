// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGeneratorCell.h"
#include "Engine/StaticMeshActor.h"
// Sets default values
AMazeGeneratorCell::AMazeGeneratorCell()
{
	PrimaryActorTick.bCanEverTick = true;

	BottomWall = true;
	LeftWall = true;

	Visited = false;

}

// Called when the game starts or when spawned
void AMazeGeneratorCell::BeginPlay()
{
	Super::BeginPlay();

}

void AMazeGeneratorCell::SpawnBotWall() {
	if (BotWall == nullptr) {
		BotWall = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass());
		BotWall -> SetActorLabel(FString::Printf(TEXT("BotWall%d%d"), x, y));

		BotWall->SetMobility(EComponentMobility::Movable);
		 
		MeshComponent = BotWall->GetStaticMeshComponent();
		if (MeshComponent) {
			MeshComponent->SetStaticMesh(WallMesh);
		}

		FVector Origin, BoxExtent;
		MeshComponent->GetLocalBounds(Origin, BoxExtent);

		//MeshSize
		WallWidth = BoxExtent.X * 2;
		WallHeight = BoxExtent.Y * 2;
		WallDepth = BoxExtent.Z * 2;

		//Calculate and set location
		FVector ActorLocation = FVector(x * WallWidth, y * WallWidth, WallWidth / 2);
		BotWall->SetActorLocation(ActorLocation);

		//Set rotation
		FRotator ActorRotation = FRotator(0.f, 90.f, 0.f);
		BotWall->SetActorRotation(ActorRotation);

	}
}

void AMazeGeneratorCell::DestroyBotWall() {
	if (BotWall)
	{
		BotWall->Destroy();
		BotWall = nullptr;
	}
}

void AMazeGeneratorCell::SpawnLeftWall() {
	if (LWall == nullptr) {
		LWall = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass());
		LWall -> SetActorLabel(FString::Printf(TEXT("LeftWall%d%d"), x, y));

		LWall->SetMobility(EComponentMobility::Movable);

		MeshComponent = LWall->GetStaticMeshComponent();
		if (MeshComponent) {
			MeshComponent->SetStaticMesh(WallMesh);
		}

		//Calculate and set location
		FVector ActorLocation = FVector(x * WallWidth + (WallWidth / 2 - WallHeight / 2), y * WallWidth - (WallWidth / 2 - WallHeight / 2), WallWidth / 2);
		LWall->SetActorLocation(ActorLocation);

		//Set rotation
		FRotator ActorRotation = FRotator(0.f, 0.f, 0.f);
		LWall->SetActorRotation(ActorRotation);

	}
}

void AMazeGeneratorCell::DestroyLeftWall() {
	if (LWall)
	{
		LWall->Destroy();
		LWall = nullptr;
	}
}

void AMazeGeneratorCell::SpawnFloor() {
	//CreateFloor for every cell
	Floor = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass());
	Floor->SetActorLabel(FString::Printf(TEXT("Floor%d%d"), x, y));

	Floor->SetMobility(EComponentMobility::Movable);

	MeshComponent = Floor->GetStaticMeshComponent();
	if (MeshComponent) {
		MeshComponent->SetStaticMesh(WallMesh);
	}

	//Calculate and set location
	FVector ActorLocation = FVector(x * WallWidth + WallWidth / 2, y * WallWidth, 0);
	Floor->SetActorLocation(ActorLocation);

	//Set rotation
	FRotator ActorRotation = FRotator(0.f, 0.f, 90.f);
	Floor->SetActorRotation(ActorRotation);
}

void AMazeGeneratorCell::DestroyFloor() {
	if (Floor)
	{
		Floor -> Destroy();
		Floor = nullptr;
	}
}

void AMazeGeneratorCell::SpawnPlayerStart() {
	PlayerStart = GetWorld()->SpawnActor<ASpawnPoint>(ASpawnPoint::StaticClass());
	PlayerStart->SetActorLabel(FString::Printf(TEXT("PlayerStart%d%d"), x, y));

	FVector ActorLocation = FVector(x * WallWidth + WallWidth / 2, y * WallWidth, 200);
	PlayerStart->SetActorLocation(ActorLocation);

	FRotator RandomRotation = FRotator(0, FMath::RandRange(-180.f, 180.f),  0
		
	);

	PlayerStart->SetActorRotation(RandomRotation);


}

void AMazeGeneratorCell::DestroyPlayerStart() {
	if (PlayerStart)
	{
		PlayerStart->Destroy();
		PlayerStart = nullptr;
	}
}

// Called every frame
void AMazeGeneratorCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	

}

