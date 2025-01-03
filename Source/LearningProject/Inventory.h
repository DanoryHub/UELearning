// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Inventory.generated.h"

// Forward declaration
struct FPickableData;
class APickable;

UCLASS()
class LEARNINGPROJECT_API UInventory : public UObject
{
	GENERATED_BODY()

	UInventory() {};

public:

	void AddItem(APickable* ItemToAdd);

	TArray<FString> InspectItems();

	APickable* InspectActiveItem(UWorld* World, FString PrevActiveItemId, USceneComponent* PivotPoint);

	APickable* EquipActiveItem(UWorld* World, USceneComponent* PivotPoint, APickable* SpawnedItem);

	APickable* DropActiveItem(UWorld* World, FVector SpawnPoint, FRotator SpawnRotation, FVector ForceDirection, float ForceStrength);

	APickable* SpawnActiveItem(UWorld* World, UClass* ItemClass, FVector SpawnPoint, FRotator SpawnRotation);

	UClass* GetActiveItemClass();

	void ApplyForceToItem(APickable* ItemToApplyForce, FVector ForceDirection, float ForceStrength);

	void DeleteItem(FString ItemID);

	void ChangeActiveItemDown();

	void ChangeActiveItemUp();

	FString GetActiveItemID();

	int GetNumOfItemsInInventory();

	void ClearActiveItem();

private:

	int ActiveItemID;

	APickable* ActiveItem;

	TArray<FPickableData*> DataList;
};
