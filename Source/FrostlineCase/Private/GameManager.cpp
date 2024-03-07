// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include <Mammal.h>

// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	UpdateUIState(EUIState::Menu);
}

// Spawn Area and Mammals
void AGameManager::Initialize()
{
	// Habitat Area Locations
	for (int i = 0; i < MAXSIZE; i++)
	{
		for (int j = 0; j < MAXSIZE; j++)
		{
			HabitatArea[i][j] = nullptr;
		}
	}
	// Spawn borders.
	int i;
	for (i = -1; i <= Width; i++)
	{
		GetWorld()->SpawnActor<AActor>(Wall, FVector(i * 100, -100, 50), FRotator(0, 0, 0));
		GetWorld()->SpawnActor<AActor>(Wall, FVector(i * 100, Height * 100, 50), FRotator(0, 0, 0));
	}
	for (i = 0; i < Height; i++)
	{
		GetWorld()->SpawnActor<AActor>(Wall, FVector(-100, i * 100, 50), FRotator(0, 0, 0));
		GetWorld()->SpawnActor<AActor>(Wall, FVector(Width * 100, i * 100, 50), FRotator(0, 0, 0));
	}
	//Spawn Cat and Mouse
	for (i = 0; i < InitCatCount; i++)
	{
		AddMammalToHabitat(FindEmptyLocationInMammalArea(),Cat,CatList);
	}
	for (i = 0; i < InitMouseCount; i++)
	{
		AddMammalToHabitat(FindEmptyLocationInMammalArea(), Mouse,MouseList);
	}
	CurrentState = EGameState::Waiting;
	UpdateUIVariable();
	
}

//Spawn Mammals and Teleport to Habitat.
void AGameManager::AddMammalToHabitat(FIntVector2 Index,TSubclassOf<AActor> MammalType,TArray<AActor*>& List)
{
	if (HabitatArea[Index.X][Index.Y] == nullptr)
	{
		AMammal* TempMammal = Cast<AMammal>(GetWorld()->SpawnActor<AActor>(MammalType, FVector(-100, -100, -100), FRotator(0, 0, 0)));
		if (TempMammal != nullptr)
		{
			TempMammal->Manager = this;
			HabitatArea[Index.X][Index.Y] = TempMammal;
			TempMammal->SetLocation(Index);
			List.Add(TempMammal);
		}

	}
}

//Find Walkable HabitatArea index value
FIntVector2 AGameManager::GetWalkableHabitatAreaIndex(AMammal* Walker)
{
	TArray< FIntVector2> WalkableIndexList;
	AMammal* Temp;
	if (Walker->GetHabitatAreaIndex().X - 1 >= 0)
	{
		Temp = Cast<AMammal>(HabitatArea[Walker->GetHabitatAreaIndex().X - 1][Walker->GetHabitatAreaIndex().Y]);
		if (Temp == nullptr)
		{
			WalkableIndexList.Add(FIntVector2(Walker->GetHabitatAreaIndex().X - 1, Walker->GetHabitatAreaIndex().Y));
		}
	}
	if (Walker->GetHabitatAreaIndex().X + 1 < Width)
	{
		Temp = Cast<AMammal>(HabitatArea[Walker->GetHabitatAreaIndex().X + 1][Walker->GetHabitatAreaIndex().Y]);
		if (Temp == nullptr)
		{
			WalkableIndexList.Add(FIntVector2(Walker->GetHabitatAreaIndex().X + 1, Walker->GetHabitatAreaIndex().Y));
		}
	}
	if (Walker->GetHabitatAreaIndex().Y - 1 >= 0)
	{
		Temp = Cast<AMammal>(HabitatArea[Walker->GetHabitatAreaIndex().X][Walker->GetHabitatAreaIndex().Y - 1]);
		if (Temp == nullptr)
		{
			WalkableIndexList.Add(FIntVector2(Walker->GetHabitatAreaIndex().X, Walker->GetHabitatAreaIndex().Y - 1));
		}
	}
	if (Walker->GetHabitatAreaIndex().Y + 1 < Height)
	{
		Temp = Cast<AMammal>(HabitatArea[Walker->GetHabitatAreaIndex().X][Walker->GetHabitatAreaIndex().Y + 1]);
		if (Temp == nullptr)
		{
			WalkableIndexList.Add(FIntVector2(Walker->GetHabitatAreaIndex().X, Walker->GetHabitatAreaIndex().Y + 1));
		}
	}
	if (WalkableIndexList.Num() > 0)
	{
		return WalkableIndexList[FMath::RandRange(0, WalkableIndexList.Num() - 1)];
	}
	return Walker->GetHabitatAreaIndex();
}

//Update InGame Value on UI
void AGameManager::UpdateUIVariable()
{
	UpdateUIVariableEvent(CatList.Num(), MouseList.Num(), TurnCount);
}

//Update UI State for close and open true UI canvas
void AGameManager::UpdateUIState(EUIState State)
{
	UpdateUIStateEvent(State);
}


//Find Random Empty Habitat Area Location from Habitat Array.
FIntVector2 AGameManager::FindEmptyLocationInMammalArea()
{
	int x = FMath::RandRange(0, Width - 1);
	int y = FMath::RandRange(0, Height - 1);
	if (HabitatArea[x][y] == nullptr)
		return FIntVector2(x, y);
	else
		return FindEmptyLocationInMammalArea();
}

//UI NextTurnButtton Event 
void AGameManager::NextTurn()
{
	if (CurrentState != EGameState::Waiting)
	{
		return;
	}
	TurnCount++;
	UpdateUIVariable();
	CurrentState = EGameState::CatWalking;
	AMammal* m = Cast<AMammal>(CatList[0]);
	if (m != nullptr)
	{
		m->NextTurn();
	}
}
//UI PlayButton Event
void AGameManager::Play(int w, int h,int CatCount, int MouseCount)
{
	Width = w;
	Height = h;
	InitCatCount = CatCount;
	InitMouseCount = MouseCount;
	Initialize();
	UpdateUIState(EUIState::InGame);
}
//UI BackMenuButton Event
void AGameManager::BackMenu()
{
	for (int i = 0; i < CatList.Num(); i++)
	{
		CatList[i]->Destroy();
	}
	for (int i = 0; i < MouseList.Num(); i++)
	{
		MouseList[i]->Destroy();
	}
	CatList.Empty();
	MouseList.Empty();
	TurnCount = 0;
	UpdateUIState(EUIState::Menu);
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//This metod for use Mammal lists (CatList and MouseList) like a linked list.
AMammal* AGameManager::FindNextMammal(AMammal* Current)
{
	for (int i = 0; i < CatList.Num(); i++)
	{
		if (CatList[i] == Current && (i + 1) < CatList.Num())
		{
			return Cast<AMammal>(CatList[i + 1]);
		}
		else if (CatList[i] == Current)
		{
			CurrentState = EGameState::MouseWalking;
			return Cast<AMammal>(MouseList[0]);
		}
	}
	for (int i = 0; i < MouseList.Num(); i++)
	{
		if (MouseList[i] == Current && (i + 1) < MouseList.Num())
		{
			return Cast<AMammal>(MouseList[i + 1]);
		}
		else if (MouseList[i] == Current)
		{
			CheckMammalsHungryState();
			CurrentState = EGameState::Waiting;
			return nullptr;
		}
	}
	CheckMammalsHungryState();
	CurrentState = EGameState::Waiting;
	return nullptr;
}

//Check Cats Hungry State
void AGameManager::CheckMammalsHungryState()
{
	TArray<AMammal*> Die;
	for (int i = 0; i < CatList.Num(); i++)
	{
		AMammal* m = Cast<AMammal>(CatList[i]);
		if (m != nullptr)
		{
			if (m->IsHungry())
			{
				Die.Add(m);
			}
		}
	}
	for (int i = 0; i < Die.Num(); i++)
	{
		Die[i]->Die(); //Die
	}
	if (CatList.Num() == 0)
	{
		CurrentState = EGameState::None;
		UpdateUIState(EUIState::EndGame);
		UpdateUIEndGameVariable(EWinState::MouseWin);
		return;
	}
	else if (MouseList.Num() == 0)
	{
		CurrentState = EGameState::None;
		UpdateUIState(EUIState::EndGame);
		UpdateUIEndGameVariable(EWinState::CatWin);
		return;
	}
	CheckMammalsBirthState();
}

//Check all mammals birth state children are our future.
void AGameManager::CheckMammalsBirthState()
{
	for (int i = 0; i < CatList.Num(); i++)
	{
		AMammal* m = Cast<AMammal>(CatList[i]);
		if (m != nullptr)
		{
			m->Birth();
		}
	}
	for (int i = 0; i < MouseList.Num(); i++)
	{
		AMammal* m = Cast<AMammal>(MouseList[i]);
		if (m != nullptr)
		{
			m->Birth();
		}
	}
}





