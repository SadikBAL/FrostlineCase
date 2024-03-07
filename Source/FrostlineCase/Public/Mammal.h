// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <GameManager.h>

#include "Mammal.generated.h"







UENUM(BlueprintType)
enum class EMammalAnimState : uint8
{
	None = 0,
	Walking = 1,
	WalkingEnd = 2
};

UCLASS()
class FROSTLINECASE_API AMammal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMammal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FIntVector2 HabitatAreaIndex;
	bool IsDie = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NextTurn();
	virtual void Birth();
	void FinishMyTurn();
	FIntVector2 GetHabitatAreaIndex();
	void SetLocation(FIntVector2 Index);
	void SetLocationWithAnimation(FIntVector2 Index);
	EMammalAnimState GetAnimState();
	bool IsMoving = false;
	FVector TargetLocation;
	FVector StartLocation;
	float AnimationPercent = 0;
	EMammalAnimState CurrentAnimState = EMammalAnimState::None;
	AGameManager* Manager;
	void Die();
	virtual bool IsHungry();
	virtual bool CouldGiveBirth();
};
