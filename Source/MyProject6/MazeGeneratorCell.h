// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "SpawnPoint.h"
#include "Net/UnrealNetwork.h"
#include "MazeGeneratorCell.generated.h"

class AStaticMeshActor;

UCLASS()
class MYPROJECT6_API AMazeGeneratorCell : public AActor
{
	GENERATED_BODY()
	
public:	
	AMazeGeneratorCell();

	UPROPERTY(Category = "Mesh", EditAnywhere, BlueprintReadWrite)
	UStaticMesh* WallMesh;
	UPROPERTY(Category = "Mesh", EditAnywhere, BlueprintReadWrite)
	UStaticMesh* CollumnMesh;

	UPROPERTY(Category = "Mesh", Replicated, BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* BottomWallMeshComponent;
	UPROPERTY(Category = "Mesh", Replicated, BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* LeftWallMeshComponent;
	UPROPERTY(Category = "Mesh", Replicated, BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* FloorWallMeshComponent;
	UPROPERTY(Category = "Mesh", BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* CollumnMeshComponent;

	UPROPERTY()
	bool BottomWall;
	UPROPERTY()
	bool LeftWall;
	UPROPERTY()
	bool Floor;
	
	UPROPERTY()
	bool Visited;

	ASpawnPoint* PlayerStart;

	void SpawnBotWall();
	void DestroyBotWall();

	void SpawnLeftWall();
	void DestroyLeftWall();

	void SpawnFloor();
	void DestroyFloor();

	void SpawnPlayerStart();
	void DestroyPlayerStart();

	void ReplaceSpawnPoint();

	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

protected:

	USceneComponent* MyRootComponent;


	virtual void BeginPlay() override;

};
