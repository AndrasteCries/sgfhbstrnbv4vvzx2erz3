#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeGeneratorCell.h"
#include "Maze.generated.h"

UCLASS()
class MYPROJECT6_API AMaze : public AActor
{
	GENERATED_BODY()

	int32 Width = 5;
	int32 Height = 5;

public:
	AMaze();

	TArray<TArray<AMazeGeneratorCell*>> Maze;

	virtual void Tick(float DeltaTime) override;

	void InitMaze(int32 InHeight, int32 InWidth, UStaticMesh* InMesh);
	void FillMaze();
	
protected:
	virtual void BeginPlay() override;

};
