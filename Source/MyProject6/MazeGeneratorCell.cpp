// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGeneratorCell.h"
#include "Engine/StaticMeshActor.h"
// Sets default values
AMazeGeneratorCell::AMazeGeneratorCell()
{
	PrimaryActorTick.bCanEverTick = true;

	BottomWall = true;
	LeftWall = true;

	Visited = true;

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
		float Width = BoxExtent.X * 2;
		float Height = BoxExtent.Y * 2;
		float Depth = BoxExtent.Z * 2;

		//Calculate and set location
		FVector ActorLocation = FVector(x * Width, y * Width, Width / 2);
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

		FVector Origin, BoxExtent;
		MeshComponent->GetLocalBounds(Origin, BoxExtent);

		//MeshSize
		float Width = BoxExtent.X * 2;
		float Height = BoxExtent.Y * 2;
		float Depth = BoxExtent.Z * 2;

		//Calculate and set location
		FVector ActorLocation = FVector(x * Width + (Width / 2 - Height / 2), y * Width - (Width / 2 - Height / 2), Width / 2);
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

	FVector Origin, BoxExtent;
	MeshComponent->GetLocalBounds(Origin, BoxExtent);

	//MeshSize
	float Width = BoxExtent.X * 2;
	float Height = BoxExtent.Y * 2;
	float Depth = BoxExtent.Z * 2;

	//Calculate and set location
	FVector ActorLocation = FVector(x * Width + Width / 2, y * Width, 0);
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

// Called every frame
void AMazeGeneratorCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
}

