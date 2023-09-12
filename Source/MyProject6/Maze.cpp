#include "Maze.h"

AMaze::AMaze()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMaze::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMaze::InitMaze(int32 InHeight, int32 InWidth, UStaticMesh* InMesh) {

    Width = InWidth + 1;
    Height = InHeight + 1;
    float MeshWidth;
    if (InMesh)
    {
        FVector MeshBounds = InMesh->GetBounds().BoxExtent;
        MeshWidth = MeshBounds.X  * 2.0f;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load StaticMesh"));
    }

    Maze.SetNum(Height);
    for (int32 RowIndex = 0; RowIndex < Maze.Num(); RowIndex++)
    {
        Maze[RowIndex].SetNum(Width);
        for (int32 ColumnIndex = 0; ColumnIndex < Maze[0].Num(); ColumnIndex++)
        {
            AMazeGeneratorCell* NewCell = GetWorld()->SpawnActor<AMazeGeneratorCell>(AMazeGeneratorCell::StaticClass());
            NewCell->SetActorLocation(FVector(MeshWidth * RowIndex, MeshWidth * ColumnIndex, 0.f));
            NewCell->SetActorRotation(FRotator(0, 180.0f, 0));
            NewCell->SetActorLabel(FString::Printf(TEXT("Cell %d%d"), RowIndex, ColumnIndex));
            NewCell->ReplaceSpawnPoint();
            Maze[RowIndex][ColumnIndex] = NewCell;
        }
    }
    DestroyExtraMesh();
}

void AMaze::DestroyExtraMesh() {
    for (int32 RowIndex = 0; RowIndex < Maze.Num(); RowIndex++) {
        Maze[RowIndex][Maze[RowIndex].Num() - 1]->DestroyBotWall();
        Maze[RowIndex][Maze[RowIndex].Num() - 1]->DestroyFloor();
        Maze[RowIndex][Maze[RowIndex].Num() - 1]->DestroyPlayerStart();
    }
    for (int32 ColumnIndex = 0; ColumnIndex < Maze[0].Num(); ColumnIndex++) {
        Maze[Maze.Num() - 1][ColumnIndex]->DestroyLeftWall();
        Maze[Maze.Num() - 1][ColumnIndex]->DestroyFloor();
        Maze[Maze.Num() - 1][ColumnIndex]->DestroyPlayerStart();
    }

}

void AMaze::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
