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

public:

	UInventory() {};

	TArray<FString> InspectItems();

	APickable* InspectActiveItem(UWorld* World, FString PrevActiveItemId, USceneComponent* PivotPoint);

	APickable* DropActiveItem(UWorld* World, FVector SpawnPoint, FRotator SpawnRotation, FVector ForceDirection, float ForceStrength);

	FString GetActiveItemID();

	void AddItem(APickable* ItemToAdd);

	void ChangeActiveItemDown();

	void ChangeActiveItemUp();

	void ClearActiveItem();

private:

	APickable* SpawnActiveItem(UWorld* World, UClass* ItemClass, FVector SpawnPoint, FRotator SpawnRotation);

	APickable* EquipActiveItem(UWorld* World, USceneComponent* PivotPoint, APickable* SpawnedItem);

	UClass* GetActiveItemClass();

	int GetNumOfItemsInInventory();

	int ActiveItemID;

	void ApplyForceToItem(APickable* ItemToApplyForce, FVector ForceDirection, float ForceStrength);

	void DeleteItem(FString ItemID);

	APickable* ActiveItem;

	TArray<FPickableData*> DataList;
};
