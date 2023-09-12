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
    MazeGenerated = true;

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
