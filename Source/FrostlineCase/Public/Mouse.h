// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mammal.h"

#define MOUSE_PREGNANCY_LIMIT 3

#include "Mouse.generated.h"

/**
 * 
 */
UCLASS()
class FROSTLINECASE_API AMouse : public AMammal
{
	GENERATED_BODY()
public:
	void NextTurn() override;
	void Birth() override;
	bool CouldGiveBirth() override;
	void Run();

protected:
	int PregnancyDay = 0;
	int TinyMouseCount = 0;
};
