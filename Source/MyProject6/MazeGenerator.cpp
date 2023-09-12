#include "MazeGenerator.h"
#include "Engine/StaticMeshActor.h"
#include "Engine.h"
#include "MazeGeneratorCell.h"

AMazeGenerator::AMazeGenerator()
{
    PrimaryActorTick.bCanEverTick = true;

    Maze = CreateDefaultSubobject<AMaze>(TEXT("MazeData"));
    WallMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/wall/FullWall"));

    MazeGenerated = false;

}

void AMazeGenerator::BeginPlay()
{
	Super::BeginPlay();
    if (WallMesh) {
        UE_LOG(LogTemp, Warning, TEXT("Mest is not null ptr"));
        Maze->InitMaze(Height, Width, WallMesh);
    }
    RemoveWallsWithBacktracker();
    MazeGenerated = true;

}

void AMazeGenerator::RemoveWallsWithBacktracker() {
    
    TArray<TArray<AMazeGeneratorCell*>> MazeFromMaze = Maze->Maze;

    AMazeGeneratorCell* Current = MazeFromMaze[0][0];

    Current->Visited = true;
    TArray<AMazeGeneratorCell*> stack;
    do
    {
        TArray<AMazeGeneratorCell*> unvisitedNeighbours;

        int32 x = Current->GetX() - 1;
        int32 y = Current->GetY() - 1;

        if (x > 0 && !MazeFromMaze[x - 1][y]->Visited) unvisitedNeighbours.Add(MazeFromMaze[x - 1][y]);
        if (y > 0 && !MazeFromMaze[x][y - 1]->Visited) unvisitedNeighbours.Add(MazeFromMaze[x][y - 1]);
        if (x < MazeFromMaze.Num() - 2 && !MazeFromMaze[x + 1][y]->Visited) unvisitedNeighbours.Add(MazeFromMaze[x + 1][y]);
        if (y < MazeFromMaze[0].Num() - 2 && !MazeFromMaze[x][y + 1]->Visited) unvisitedNeighbours.Add(MazeFromMaze[x][y + 1]);


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

void AMazeGenerator::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AMazeGenerator, Maze);

}


bool AMazeGenerator::GetMazeGenerated() {
    return MazeGenerated;
}
