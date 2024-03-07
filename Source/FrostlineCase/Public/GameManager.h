
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#define MAXSIZE 25
#define MINSIZE 6

#include "GameManager.generated.h"

UENUM(BlueprintType)
enum class EGameState : uint8
{
	None = 0,
	Waiting = 1,
	CatWalking = 2,
	MouseWalking = 3,
	DeathAndBirth = 4

};
UENUM(BlueprintType)
enum class EUIState : uint8
{
	Menu = 0,
	InGame = 1,
	EndGame = 2
};

UENUM(BlueprintType)
enum class EWinState : uint8
{
	CatWin = 0,
	MouseWin = 1
};

UCLASS()
class FROSTLINECASE_API AGameManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGameManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Initialize();
	void AddMammalToHabitat(class AMammal* Mammel);
	
	
	
	FIntVector2 FindEmptyLocationInMammalArea();
	UFUNCTION(BlueprintCallable)
	void NextTurn();
	UFUNCTION(BlueprintCallable)
	void Play(int Width, int Height, int CatCount, int MouseCount);
	UFUNCTION(BlueprintCallable)
	void BackMenu();

public:
	// Called every frame
	UFUNCTION(BlueprintImplementableEvent, Category = "UpdateUIVariableEvent")
	void UpdateUIVariableEvent(int CatCount, int MouseCount, int Turn);
	UFUNCTION(BlueprintImplementableEvent, Category = "UpdateUIVariableEvent")
	void UpdateUIEndGameVariable(EWinState State);
	UFUNCTION(BlueprintImplementableEvent, Category = "UpdateUIStateEvent")
	void UpdateUIStateEvent(EUIState State);
	void UpdateUIVariable();
	void UpdateUIState(EUIState State);
	virtual void Tick(float DeltaTime) override;
	FIntVector2 GetWalkableHabitatAreaIndex(class AMammal* Walker);
	UPROPERTY(EditAnywhere, Category = "Settings", meta = (AllowPrivateAccess = true))
	TSubclassOf<AActor> Wall;
	UPROPERTY(EditAnywhere, Category = "Settings", meta = (AllowPrivateAccess = true))
	TSubclassOf<AActor> Cat;
	UPROPERTY(EditAnywhere, Category = "Settings", meta = (AllowPrivateAccess = true))
	TSubclassOf<AActor> Mouse;
	UPROPERTY(Editanywhere, Category = "Settings", meta = (ClampMin = "6", ClampMax = "25"))
	int Width = 5;
	UPROPERTY(Editanywhere, Category = "Settings", meta = (ClampMin = "6", ClampMax = "25"))
	int Height = 5;
	UPROPERTY(Editanywhere, Category = "Settings", meta = (ClampMin = "3", ClampMax = "100"))
	int InitCatCount = 3;
	UPROPERTY(Editanywhere, Category = "Settings", meta = (ClampMin = "5", ClampMax = "250"))
	int InitMouseCount = 5;
	UPROPERTY(Editanywhere, Category = "Settings", meta = (ClampMin = "5", ClampMax = "250"))
	int AnimSpeed = 10;
	AActor* CatInst;
	AActor* MouseInst;
	class AMammal* HabitatArea[MAXSIZE][MAXSIZE];
	TArray<AActor*> CatList;
	TArray<AActor*> MouseList;
	int TurnCount = 0;
	TArray<class AMammal*> MammalList;
	AMammal* FindNextMammal(AMammal* Current);
	void CheckMammalsHungryState();
	void CheckMammalsBirthState();
	EGameState CurrentState = EGameState::None;
	void AddMammalToHabitat(FIntVector2 Index,TSubclassOf<AActor> MammalType,TArray<AActor*>& List);
	

};
