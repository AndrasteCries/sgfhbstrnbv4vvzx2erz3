#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeGeneratorCell.h"
#include "Maze.h"
#include "Net/UnrealNetwork.h"
#include "MazeGenerator.generated.h"

class AMazeGeneratorCell;

UCLASS()
class MYPROJECT6_API AMazeGenerator : public AActor
{
	GENERATED_BODY()

public:	

	AMazeGenerator();

	UPROPERTY(Category = "Settings", EditAnywhere, BlueprintReadWrite)
	int32 Height = 5;

	UPROPERTY(Category = "Settings", EditAnywhere, BlueprintReadWrite)
	int32 Width = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* WallMesh;

	UPROPERTY(Replicated)
	AMaze* Maze;
	
	bool MazeGenerated;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		bool GetMazeGenerated();

protected:
	virtual void BeginPlay() override;

private:
	void RemoveWallsWithBacktracker();
	void RemoveWall(AMazeGeneratorCell* Current, AMazeGeneratorCell* Choosen);
};
