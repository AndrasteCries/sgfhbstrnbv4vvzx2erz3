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

    Width = InWidth;
    Height = InHeight;

    Maze.SetNum(Height);
    for (int32 RowIndex = 0; RowIndex < Maze.Num(); RowIndex++)
    {
        UE_LOG(LogTemp, Warning, TEXT("Height succ"));
        Maze[RowIndex].SetNum(Width);
        for (int32 ColumnIndex = 0; ColumnIndex < Maze[0].Num(); ColumnIndex++)
        {
            UE_LOG(LogTemp, Warning, TEXT("Width succ"));
        //    //Create every cell and set param
        //    AMazeGeneratorCell* NewCell = CreateDefaultSubobject<AMazeGeneratorCell>(TEXT("MazeCell"));
        //    NewCell->SetX(RowIndex + 1);
        //    NewCell->SetY(ColumnIndex + 1);
        //    NewCell->WallMesh = InMesh;
        //    Maze[RowIndex][ColumnIndex] = NewCell;
        }
    }
}

void AMaze::FillMaze() {

    for (int32 RowIndex = 0; RowIndex < Maze.Num(); RowIndex++)
    {
        for (int32 ColumnIndex = 0; ColumnIndex < Maze[0].Num(); ColumnIndex++)
        {
            AMazeGeneratorCell* Cell = Maze[RowIndex][ColumnIndex];

            if (Cell->BottomWall) {
                Cell->SpawnBotWall();
            }

            if (Cell->LeftWall) {
                Cell->SpawnLeftWall();
            }
            Cell->SpawnFloor();
            Cell->SpawnPlayerStart();
        }
    }

    //destroy last
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
