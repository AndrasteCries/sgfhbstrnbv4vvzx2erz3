// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeGeneratorCell.h"
#include "MyMazeGameMode.h"
#include "MazeGenerator.generated.h"

class AMazeGeneratorCell;

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

	TArray<TArray<AMazeGeneratorCell*>> Maze;
	
	bool MazeGenerated;

	AMazeGenerator();


protected:
	virtual void BeginPlay() override;

private:
	void RemoveWallsWithBacktracker();
	void RemoveWall(AMazeGeneratorCell* Current, AMazeGeneratorCell* Choosen);

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	bool GetMazeGenerated();

};
