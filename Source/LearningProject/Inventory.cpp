// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "Pickable.h"
#include "Helpers.h"

void UInventory::AddItem(APickable* ItemToAdd)
{
	FPickableData* NewItemData = ItemToAdd->GetItemData();

	DataList.Add(NewItemData);

	ItemToAdd->Destroy();
}

TArray<FString> UInventory::InspectItems()
{
	TArray<FString> ItemNames;

	for (int i = 0; i < DataList.Num(); i++)
	{
		ItemNames.Add(*(TEXT("%s: %s"), &DataList[i]->Name, &DataList[i]->ID));
	}

	return ItemNames;
}

FString UInventory::InspectActiveItem()
{
	if (DataList.Num() > 0)
	{
		return (TEXT("%s: %s"), DataList[ActiveItemID]->Name, DataList[ActiveItemID]->ID);
	}

	return (FString)TEXT("No items in inventory now");
}

APickable* UInventory::EquipActiveItem(UObject* PivotPoint)
{
	UE_LOG(LogTemp, Warning, TEXT("Active item: %s"), *DataList[ActiveItemID]->Name);
	return nullptr;
}
