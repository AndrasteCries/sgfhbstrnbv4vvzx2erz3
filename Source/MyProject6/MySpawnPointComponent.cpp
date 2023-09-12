#include "MySpawnPointComponent.h"

UMySpawnPointComponent::UMySpawnPointComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UMySpawnPointComponent::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UMySpawnPointComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

