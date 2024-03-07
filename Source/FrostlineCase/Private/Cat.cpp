// Fill out your copyright notice in the Description page of Project Settings.


#include "Cat.h"
#include <Kismet/GameplayStatics.h>

void ACat::NextTurn()
{
	if (Manager)
	{
		HuntMouse();
		HungryDay++;
		PregnancyDay++;
		if (PregnancyDay == CAT_PREGNANCY_LIMIT)
		{
			TinyCatCount++;
			PregnancyDay = 0;
		}
		UE_LOG(LogTemp, Warning, TEXT("CAT"));
	}

}

bool ACat::IsHungry()
{
	if (HungryDay >= CAT_HUNGRY_LIMIT)
		return true;
	return false;
}

void ACat::Birth()
{
	if (CouldGiveBirth())
	{
		FIntVector2 BirthLocation = Manager->GetWalkableHabitatAreaIndex(this);
		if (BirthLocation != this->HabitatAreaIndex)
		{
			TinyCatCount--;
			Manager->AddMammalToHabitat(BirthLocation,Manager->Cat,Manager->CatList);
			//Manager->AddMammalToHabitatLocation(nullptr, BirthLocation);
		}
	}

}

bool ACat::CouldGiveBirth()
{
	if (TinyCatCount > 0)
		return true;
	return false;
}

void ACat::HuntMouse()
{
	AMouse* Hunt = CheckMouse();
	if (Hunt != nullptr)
	{
		this->SetLocationWithAnimation(Hunt->GetHabitatAreaIndex());
		Hunt->Die();
		HungryDay = 0;
	}
	else
	{
		this->SetLocationWithAnimation(Manager->GetWalkableHabitatAreaIndex(this));
	}
}

AMouse* ACat::CheckMouse()
{
	AMouse* Temp = nullptr;
	if (HabitatAreaIndex.X - 1 >= 0)
	{
		Temp = Cast<AMouse>(Manager->HabitatArea[HabitatAreaIndex.X - 1][HabitatAreaIndex.Y]);
	}
	if (Temp != nullptr)
		return Temp;
	if (HabitatAreaIndex.X + 1 < Manager->Width)
	{
		Temp = Cast<AMouse>(Manager->HabitatArea[HabitatAreaIndex.X + 1][HabitatAreaIndex.Y]);
	}
	if (Temp != nullptr)
		return Temp;
	if (HabitatAreaIndex.Y - 1 >= 0)
	{
		Temp = Cast<AMouse>(Manager->HabitatArea[HabitatAreaIndex.X][HabitatAreaIndex.Y - 1]);
	}
	if (Temp != nullptr)
		return Temp;
	if (HabitatAreaIndex.Y + 1 < Manager->Height)
	{
		Temp = Cast<AMouse>(Manager->HabitatArea[HabitatAreaIndex.X][HabitatAreaIndex.Y + 1]);
	}
	if (Temp != nullptr)
		return Temp;
	return nullptr;
}





