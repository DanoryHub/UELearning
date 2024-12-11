// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "Pickable.h"
#include "Helpers.h"

void UInventory::AddItem(APickable* ItemToAdd)
{
	if (ItemToAdd == nullptr)
	{
		return;
	}

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

APickable* UInventory::SpawnActiveItem(UWorld* World, FVector SpawnPoint, FRotator SpawnRotation, FVector ForceDirection, float ForceStrength)
{
	if (DataList.Num() == 0)
	{
		return nullptr;
	}

	FPickableData* ItemToSpawn = DataList[ActiveItemID];
	UClass* ItemClass;
	
	if (ItemToSpawn != nullptr)
	{
		ItemClass = ItemToSpawn->ItemClass;
	}
	else
	{
		return nullptr;
	}

	if (World != nullptr)
	{
		APickable* SpawnedItem = World->SpawnActor<APickable>(ItemClass, SpawnPoint, SpawnRotation);

		if (SpawnedItem == nullptr)
		{
			return nullptr;
		}

		SpawnedItem->SetPhysics(true);
		SpawnedItem->ApplyForce(ForceDirection, ForceStrength);

		DeleteItem(DataList[ActiveItemID]->ID);
		return SpawnedItem;
	}

	return nullptr;
}

void UInventory::DeleteItem(FString ItemID)
{
	FPickableData* ItemToRemove = nullptr;

	for (int i = 0; i < DataList.Num(); i++)
	{
		if (DataList[i]->ID == ItemID)
		{
			ItemToRemove = DataList[i];
			break;
		}
	}

	if (ItemToRemove != nullptr)
	{
		DataList.Remove(ItemToRemove);
		ChangeActiveItemDown();
	}
}

void UInventory::ChangeActiveItemDown()
{
	if (DataList.Num() == 0)
	{
		return;
	}

	if (ActiveItemID == 0)
	{
		ActiveItemID = DataList.Num() - 1;
	}
	else
	{
		ActiveItemID--;
	}
}

void UInventory::ChangeActiveItemUp()
{
	if (DataList.Num() == 0)
	{
		return;
	}

	if (ActiveItemID + 1 == DataList.Num())
	{
		ActiveItemID = 0;
	}
	else
	{
		ActiveItemID++;
	}
}
