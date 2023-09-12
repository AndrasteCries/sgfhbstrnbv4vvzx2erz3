// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGeneratorCell.h"
#include "Engine/StaticMeshActor.h"

AMazeGeneratorCell::AMazeGeneratorCell()
{
	PrimaryActorTick.bCanEverTick = true;

	MyRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(MyRootComponent);


	WallMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/wall/FullWall"));
	if (!WallMesh) UE_LOG(LogTemp, Warning, TEXT("WallMesh Error"));
	CollumnMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/wall/WallCollumn"));
	if (!CollumnMesh) UE_LOG(LogTemp, Warning, TEXT("WallMesh Error"));

	BottomWallMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BottomWallMesh"));
	if (BottomWallMeshComponent) {
		BottomWallMeshComponent->SetStaticMesh(WallMesh);
		BottomWall = true;
		BottomWallMeshComponent->SetupAttachment(MyRootComponent);
		BottomWallMeshComponent->SetRelativeLocation(FVector(225.f, 0.f, 0.f));
		BottomWallMeshComponent->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("BottomWallMeshComponent Error"));
		BottomWall = false;
	}

	LeftWallMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftWallMesh"));
	if (LeftWallMeshComponent) {
		LeftWallMeshComponent->SetStaticMesh(WallMesh);
		LeftWall = true;
		LeftWallMeshComponent->SetupAttachment(MyRootComponent);
		LeftWallMeshComponent->SetRelativeLocation(FVector(0.f, 225.f, 0.f));
		LeftWallMeshComponent->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("LeftWallMeshComponent Error"));
		LeftWall = false;
	}

	FloorWallMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorWallMesh"));
	if (FloorWallMeshComponent) {
		FloorWallMeshComponent->SetStaticMesh(WallMesh);
		Floor = true;
		FloorWallMeshComponent->SetupAttachment(MyRootComponent);
		FloorWallMeshComponent->SetRelativeLocation(FVector(0.f, 0.f, -250.f));
		FloorWallMeshComponent->SetRelativeScale3D(FVector(1.05f, 1.f, 1.05f));
		FloorWallMeshComponent->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("FloorWallMeshComponent Error"));
		Floor = false;
	}

	CollumnMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CollumnWallMesh"));
	if (CollumnMeshComponent) {
		CollumnMeshComponent->SetStaticMesh(CollumnMesh);
		CollumnMeshComponent->SetupAttachment(MyRootComponent);
		CollumnMeshComponent->SetRelativeLocation(FVector(225.f, 225.f, 0.f));
		CollumnMeshComponent->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("CollumnMeshComponent Error"));
	}

	
	Visited = false;

}

// Called when the game starts or when spawned
void AMazeGeneratorCell::BeginPlay()
{
	Super::BeginPlay();
	PlayerStart = GetWorld()->SpawnActor<ASpawnPoint>(ASpawnPoint::StaticClass());
	PlayerStart->SetActorLabel(FString::Printf(TEXT("PlayerStart")));
	FRotator RandomRotation = FRotator(0, FMath::RandRange(-180.f, 180.f), 0);

	PlayerStart->SetActorRotation(RandomRotation);

}

void AMazeGeneratorCell::DestroyBotWall() {
	BottomWallMeshComponent->DestroyComponent();

}

void AMazeGeneratorCell::DestroyLeftWall() {
	LeftWallMeshComponent->DestroyComponent();

}

void AMazeGeneratorCell::DestroyFloor() {
	FloorWallMeshComponent->DestroyComponent();

}

void AMazeGeneratorCell::DestroyPlayerStart() {
	PlayerStart->Destroy();

}

void AMazeGeneratorCell::ReplaceSpawnPoint() {
	FVector ActorLocation = GetActorLocation();
	PlayerStart->SetActorRelativeLocation(ActorLocation);

}

// Called every frame
void AMazeGeneratorCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	

}

void AMazeGeneratorCell::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMazeGeneratorCell, BottomWallMeshComponent);
	DOREPLIFETIME(AMazeGeneratorCell, LeftWallMeshComponent);
	DOREPLIFETIME(AMazeGeneratorCell, FloorWallMeshComponent);

}

