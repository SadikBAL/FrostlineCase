// Fill out your copyright notice in the Description page of Project Settings.


#include "Mammal.h"

// Sets default values
AMammal::AMammal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMammal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMammal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsDie && AnimationPercent < 1)
	{
		AnimationPercent += DeltaTime* Manager->AnimSpeed;
		SetActorScale3D(FMath::Lerp(StartLocation, TargetLocation, AnimationPercent));
	}
	else if(IsDie && AnimationPercent >= 1)
	{
		Destroy();
	}
	else if (CurrentAnimState == EMammalAnimState::Walking)
	{
		AnimationPercent += DeltaTime * Manager->AnimSpeed;
		SetActorLocation(FMath::Lerp(StartLocation, TargetLocation, AnimationPercent));
		if (AnimationPercent > 1)
			CurrentAnimState = EMammalAnimState::WalkingEnd;
	}
	else if(CurrentAnimState == EMammalAnimState::WalkingEnd)
	{
		FinishMyTurn();
		CurrentAnimState = EMammalAnimState::None;
	}

}

void AMammal::NextTurn()
{
	UE_LOG(LogTemp, Warning, TEXT("MAMMAL"));
}

void AMammal::Birth()
{

}

void AMammal::FinishMyTurn()
{
	AMammal* Next = Manager->FindNextMammal(this);
	if (Next != nullptr)
	{
		Next->NextTurn();
	}
}

FIntVector2 AMammal::GetHabitatAreaIndex()
{

	return HabitatAreaIndex;
}

//Teleport to location for Initilization metod.
void AMammal::SetLocation(FIntVector2 Location)
{
	Manager->HabitatArea[HabitatAreaIndex.X][HabitatAreaIndex.Y] = nullptr;
	this->HabitatAreaIndex = Location;
	Manager->HabitatArea[HabitatAreaIndex.X][HabitatAreaIndex.Y] = this;
	this->SetActorLocation(FVector(Location.X * 100, Location.Y * 100, 0));
}
//Move to location with smoot animation.
void AMammal::SetLocationWithAnimation(FIntVector2 Location)
{
	Manager->HabitatArea[HabitatAreaIndex.X][HabitatAreaIndex.Y] = nullptr;
	this->HabitatAreaIndex = Location;
	Manager->HabitatArea[HabitatAreaIndex.X][HabitatAreaIndex.Y] = this;
	CurrentAnimState = EMammalAnimState::Walking;
	AnimationPercent = 0;
	TargetLocation = FVector(Location.X*100, Location.Y*100,0);
	StartLocation = GetActorLocation();
}

EMammalAnimState AMammal::GetAnimState()
{
	return CurrentAnimState;
}

void AMammal::Die()
{
	IsDie = true;
	AnimationPercent = 0;
	TargetLocation = FVector(0,0,0);
	StartLocation = GetActorScale();
	Manager->CatList.RemoveSingle(this);
	Manager->MouseList.RemoveSingle(this);
	Manager->UpdateUIVariable();
}

bool AMammal::IsHungry()
{
	return false;
}

bool AMammal::CouldGiveBirth()
{
	return false;
}

