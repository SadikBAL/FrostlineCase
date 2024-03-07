// Fill out your copyright notice in the Description page of Project Settings.


#include "Mouse.h"

void AMouse::NextTurn()
{

	Run();
	PregnancyDay++;
	if (PregnancyDay == MOUSE_PREGNANCY_LIMIT)
	{
		TinyMouseCount++;
		PregnancyDay = 0;
	}
	UE_LOG(LogTemp,Warning,TEXT("MOUSE"));
}

void AMouse::Birth()
{
	if (CouldGiveBirth())
	{
		FIntVector2 BirthLocation = Manager->GetWalkableHabitatAreaIndex(this);
		if (BirthLocation != this->HabitatAreaIndex)
		{
			TinyMouseCount--;
			Manager->AddMammalToHabitat(BirthLocation, Manager->Mouse, Manager->MouseList);
			//Manager->AddMammalToHabitatLocation(nullptr, BirthLocation);
		}
	}
}

bool AMouse::CouldGiveBirth()
{
	if (TinyMouseCount > 0)
		return true;
	return false;
}

void AMouse::Run()
{
	this->SetLocationWithAnimation(Manager->GetWalkableHabitatAreaIndex(this));
}

