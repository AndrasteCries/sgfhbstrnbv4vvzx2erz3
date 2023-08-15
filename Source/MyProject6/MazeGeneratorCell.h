// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

	UPROPERTY()
	bool BottomWall;
	UPROPERTY()
	bool LeftWall;
	
	UPROPERTY()
	bool Visited;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* WallMesh;

	UPROPERTY()
	AStaticMeshActor* BotWall;
	UPROPERTY()
	AStaticMeshActor* LWall;

	void SetX(int32 NewX) { x = NewX; }
	void SetY(int32 NewY) { y = NewY; }
	int32 GetX() const { return x; }
	int32 GetY() const { return y; }

	virtual void Tick(float DeltaTime) override;

	void SpawnBotWall();
	void DestroyBotWall();

	void SpawnLeftWall();
	void DestroyLeftWall();

protected:
	virtual void BeginPlay() override;

};
