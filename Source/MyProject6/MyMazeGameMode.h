// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerStart.h"
#include "SpawnPoint.h"
#include "MyMazeGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT6_API AMyMazeGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyMazeGameMode();

	UPROPERTY(BlueprintReadOnly)
	TArray<ASpawnPoint*> SpawnPoints;

	void PostLogin(APlayerController* NewPlayer);
	ASpawnPoint* GetSpawnPoint();
	UFUNCTION(BlueprintCallable)
	void SpawnPlayer(APlayerController* NewPlayer);
	

	UFUNCTION(BlueprintCallable)
	void SetSpawnPoints(TArray<ASpawnPoint*> WorldSpawnPoints);

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

};
