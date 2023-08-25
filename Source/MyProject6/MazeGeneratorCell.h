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

	UPROPERTY()
	int32 x;
	UPROPERTY()
	int32 y;

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

	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;


	void SetX(int32 NewX) { x = NewX; }
	void SetY(int32 NewY) { y = NewY; }
	int32 GetX() const { return x; }
	int32 GetY() const { return y; }

protected:

	USceneComponent* MyRootComponent;


	virtual void BeginPlay() override;

};
