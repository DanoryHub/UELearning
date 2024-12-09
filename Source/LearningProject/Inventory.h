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

	FString InspectActiveItem();

	APickable* EquipActiveItem(UObject* PivotPoint);

private:

	int32 ActiveItemID;

	TArray<FPickableData*> DataList;
};
