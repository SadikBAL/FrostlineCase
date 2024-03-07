// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mammal.h"
#include "Mouse.h"

#define CAT_PREGNANCY_LIMIT 8
#define CAT_HUNGRY_LIMIT 3

#include "Cat.generated.h"



/**
 * 
 */
UCLASS()
class FROSTLINECASE_API ACat : public AMammal
{
	GENERATED_BODY()
public:
	void NextTurn() override;
	bool IsHungry() override;
	void Birth() override;
	bool CouldGiveBirth() override;
	void HuntMouse();

protected:
	int HungryDay = 0;
	int PregnancyDay = 0;
	int TinyCatCount = 0;
private:

	AMouse* CheckMouse();
	
};
