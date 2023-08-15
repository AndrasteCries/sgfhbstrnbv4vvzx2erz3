// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGenerator.h"
#include "Engine/StaticMeshActor.h"
#include "MazeGeneratorCell.h"

// Sets default values
AMazeGenerator::AMazeGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMazeGenerator::BeginPlay()
{
	Super::BeginPlay();
    //Create cells array
	TArray<TArray<AMazeGeneratorCell*>> maze;
	maze.SetNum(Height);
    for (int32 RowIndex = 0; RowIndex < maze.Num(); RowIndex++)
    {
        maze[RowIndex].SetNum(Width);
        for (int32 ColumnIndex = 0; ColumnIndex < maze[0].Num(); ColumnIndex++)
        {
            //Create every cell and set param
            AMazeGeneratorCell* NewCell = NewObject<AMazeGeneratorCell>(this, AMazeGeneratorCell::StaticClass());
            NewCell->SetX(RowIndex + 1);
            NewCell->SetY(ColumnIndex + 1);
            NewCell->WallMesh = WallMesh;
            maze[RowIndex][ColumnIndex] = NewCell;
        }
    }

    for (int32 RowIndex = 0; RowIndex < maze.Num(); RowIndex++)
    {
        for (int32 ColumnIndex = 0; ColumnIndex < maze[0].Num(); ColumnIndex++)
        {
            AMazeGeneratorCell* Cell = maze[RowIndex][ColumnIndex];

            if (Cell->BottomWall) {
                Cell->SpawnBotWall();
            }

            if (Cell->LeftWall) {
                Cell->SpawnLeftWall();
            }
        }
    }

    for (int32 RowIndex = 0; RowIndex < maze.Num(); RowIndex++) {
        maze[RowIndex][maze[RowIndex].Num() - 1]->DestroyBotWall();
    }
    for (int32 ColumnIndex = 0; ColumnIndex < maze[0].Num(); ColumnIndex++) {
        maze[maze.Num() - 1][ColumnIndex]->DestroyLeftWall();
    }

}

// Called every frame
void AMazeGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMazeGenerator::SpawnStaticMeshActor(const FVector& InLocation, const FRotator& InRotation) {
	AStaticMeshActor* MyNewActor = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass());
	MyNewActor->SetMobility(EComponentMobility::Movable);
	MyNewActor->SetActorLocation(InLocation);
	MyNewActor->SetActorRotation(InRotation);

	UStaticMeshComponent* MeshComponent = MyNewActor->GetStaticMeshComponent();
	if (MeshComponent) {
		MeshComponent->SetStaticMesh(WallMesh);
	}
}
