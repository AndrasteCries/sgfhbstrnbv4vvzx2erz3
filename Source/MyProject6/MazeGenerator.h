// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeGeneratorCell.h"
#include "MazeGenerator.generated.h"

UCLASS()
class MYPROJECT6_API AMazeGenerator : public AActor
{
	GENERATED_BODY()
public:	

	UPROPERTY(Category = "Settings", EditAnywhere, BlueprintReadWrite)
	int32 Height = 5;

	UPROPERTY(Category = "Settings", EditAnywhere, BlueprintReadWrite)
	int32 Width = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* WallMesh;
	// Sets default values for this actor's properties
	AMazeGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnStaticMeshActor(const FVector& InLocation, const FRotator& InRotation);

};
