// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGenerator.h"
#include "Engine/StaticMeshActor.h"
#include "Engine.h"
#include "MazeGeneratorCell.h"

AMazeGenerator::AMazeGenerator()
{
    PrimaryActorTick.bCanEverTick = true;

    MazeGenerated = false;

}

void AMazeGenerator::BeginPlay()
{
	Super::BeginPlay();

    //Create cells array
    Maze.SetNum(Height);
    for (int32 RowIndex = 0; RowIndex < Maze.Num(); RowIndex++)
    {
        Maze[RowIndex].SetNum(Width);
        for (int32 ColumnIndex = 0; ColumnIndex < Maze[0].Num(); ColumnIndex++)
        {
            //Create every cell and set param
            AMazeGeneratorCell* NewCell = NewObject<AMazeGeneratorCell>(this, AMazeGeneratorCell::StaticClass());
            NewCell->SetX(RowIndex + 1);
            NewCell->SetY(ColumnIndex + 1);
            NewCell->WallMesh = WallMesh;
            Maze[RowIndex][ColumnIndex] = NewCell;
        }
    }

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

    RemoveWallsWithBacktracker();

    TArray<APlayerController*> PlayerControllers;
    for (TActorIterator<APlayerController> Iterator(GetWorld(), APlayerController::StaticClass()); Iterator; ++Iterator) {
        PlayerControllers.Add(Cast<APlayerController>(*Iterator));
    }
    UE_LOG(LogTemp, Warning, TEXT("PLAYER CONTROLLER = %d"), PlayerControllers.Num());

    TArray<ASpawnPoint*> PlayerSpawnPoints;
    for (TActorIterator<ASpawnPoint> Iterator(GetWorld(), ASpawnPoint::StaticClass()); Iterator; ++Iterator) {
        PlayerSpawnPoints.Add(Cast<ASpawnPoint>(*Iterator));
    }
    UE_LOG(LogTemp, Warning, TEXT("NUM ====================== %d"), PlayerSpawnPoints.Num());
    //for (int32 i = 1; i < PlayerControllers.Num(); i++) {
    //    if (AMyMazeGameMode* GM = Cast<AMyMazeGameMode>(GetWorld()->GetAuthGameMode())) {
    //        GM->SetSpawnPoints(PlayerSpawnPoints);
    //        GM->PostLogin(PlayerControllers[i]);
    //        //GM->SpawnPlayer(PlayerControllers[i]);
    //    }
    //}
    MazeGenerated = true;
}

void AMazeGenerator::RemoveWallsWithBacktracker() {

    AMazeGeneratorCell* Current = Maze[0][0];

    Current->Visited = true;
    TArray<AMazeGeneratorCell*> stack;
    do
    {
        TArray<AMazeGeneratorCell*> unvisitedNeighbours;

        int32 x = Current->GetX() - 1;
        int32 y = Current->GetY() - 1;

        if (x > 0 && !Maze[x - 1][y]->Visited) unvisitedNeighbours.Add(Maze[x - 1][y]);
        if (y > 0 && !Maze[x][y - 1]->Visited) unvisitedNeighbours.Add(Maze[x][y - 1]);
        if (x < Maze.Num() - 2 && !Maze[x + 1][y]->Visited) unvisitedNeighbours.Add(Maze[x + 1][y]);
        if (y < Maze[0].Num() - 2 && !Maze[x][y + 1]->Visited) unvisitedNeighbours.Add(Maze[x][y + 1]);


        if (unvisitedNeighbours.Num() > 0)
        {
            AMazeGeneratorCell* Chosen = unvisitedNeighbours[FMath::RandRange(0, unvisitedNeighbours.Num() - 1)];
            RemoveWall(Current, Chosen);

            Chosen->Visited = true;
            stack.Push(Chosen);
            Current = Chosen;
        }
        else
        {
            if (stack.Num() > 0) {
                Current = stack.Pop();
            }
        }
    } while (stack.Num() > 0);

}

void AMazeGenerator::RemoveWall(AMazeGeneratorCell* Current, AMazeGeneratorCell* Choosen)
{
    if (Current->GetX() == Choosen->GetX())
    {
        if (Current->GetY() > Choosen->GetY()) {
            Current->BottomWall = false;
            Current->DestroyLeftWall();
        }
        else {
            Choosen->BottomWall = false;
            Choosen->DestroyLeftWall();
        }
    }
    else
    {
        if (Current->GetX() > Choosen->GetX()) {
            Current->LeftWall = false;
            Current->DestroyBotWall();
        }
        else {
            Choosen->LeftWall = false; 
            Choosen->DestroyBotWall();
        }
    }
}


// Called every frame
void AMazeGenerator::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}


bool AMazeGenerator::GetMazeGenerated() {
    return MazeGenerated;
}
