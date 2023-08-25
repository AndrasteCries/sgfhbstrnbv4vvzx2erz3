#include "MazeGenerator.h"
#include "Engine/StaticMeshActor.h"
#include "Engine.h"
#include "MazeGeneratorCell.h"

AMazeGenerator::AMazeGenerator()
{
    PrimaryActorTick.bCanEverTick = true;

    Maze = CreateDefaultSubobject<AMaze>(TEXT("MazeData"));
    WallMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/wall/FullWall"));
    if (WallMesh) {
        UE_LOG(LogTemp, Warning, TEXT("Mest is not null ptr"));
        Maze->InitMaze(Height, Width, WallMesh);
    }
    MazeGenerated = false;

}

void AMazeGenerator::BeginPlay()
{
	Super::BeginPlay();
    //Maze->FillMaze();
    //RemoveWallsWithBacktracker();
    MazeGenerated = true;

}

void AMazeGenerator::RemoveWallsWithBacktracker() {

    AMazeGeneratorCell* Current = Maze->Maze[0][0];

    Current->Visited = true;
    TArray<AMazeGeneratorCell*> stack;
    do
    {
        TArray<AMazeGeneratorCell*> unvisitedNeighbours;

        int32 x = Current->GetX() - 1;
        int32 y = Current->GetY() - 1;

        if (x > 0 && !Maze->Maze[x - 1][y]->Visited) unvisitedNeighbours.Add(Maze->Maze[x - 1][y]);
        if (y > 0 && !Maze->Maze[x][y - 1]->Visited) unvisitedNeighbours.Add(Maze->Maze[x][y - 1]);
        if (x < Maze->Maze.Num() - 2 && !Maze->Maze[x + 1][y]->Visited) unvisitedNeighbours.Add(Maze->Maze[x + 1][y]);
        if (y < Maze->Maze[0].Num() - 2 && !Maze->Maze[x][y + 1]->Visited) unvisitedNeighbours.Add(Maze->Maze[x][y + 1]);


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


void AMazeGenerator::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AMazeGenerator, Maze);

}

// Called every frame
void AMazeGenerator::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}


bool AMazeGenerator::GetMazeGenerated() {
    return MazeGenerated;
}
