// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPoint.h"

// Sets default values
ASpawnPoint::ASpawnPoint()
{
	PrimaryActorTick.bCanEverTick = true;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/bullet/bullet"));
	if (Mesh)
	{
		UStaticMeshComponent* MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
		MeshComponent->SetupAttachment(RootComponent); 
		MeshComponent->SetStaticMesh(Mesh);
		MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		MeshComponent->SetVisibility(false);
		RootComponent = MeshComponent;
	}
	Tags.Add(FName("SpawnPoint"));

}

// Called when the game starts or when spawned
void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("SPAWN POINT BEGIN PLAY"));

}



// Called every frame
void ASpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

