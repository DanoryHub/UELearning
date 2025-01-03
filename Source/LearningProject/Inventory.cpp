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

APickable* UInventory::InspectActiveItem(UWorld* World, FString PrevActiveItemId, USceneComponent* PivotPoint)
{
	if (DataList.Num() == 0 || ActiveItemID > DataList.Num() - 1 || ActiveItemID < 0)
	{
		return nullptr;
	}

	FPickableData* ItemToSpawn = DataList[ActiveItemID];
	if (ItemToSpawn->ID.IsEmpty())
	{
		return nullptr;
	}

	UClass* ItemClass = ItemToSpawn->ItemClass;

	APickable* SpawnedItem = SpawnActiveItem(World, ItemClass, PivotPoint->GetComponentLocation(), PivotPoint->GetComponentRotation());

	if (PrevActiveItemId != DataList[ActiveItemID]->ID)
	{
		if (ActiveItem == nullptr && SpawnedItem != nullptr)
		{
			APickable* NewItem = EquipActiveItem(World, PivotPoint, SpawnedItem);
			SpawnedItem->SetActorScale3D(FVector::One() * ItemToSpawn->HandleScale);
			ActiveItem = NewItem;
			return NewItem;
		}
	}

	return nullptr;
}

APickable* UInventory::EquipActiveItem(UWorld* World, USceneComponent* PivotPoint, APickable* SpawnedItem)
{
	if (SpawnedItem == nullptr)
	{
		return nullptr;
	}
	SpawnedItem->AttachToComponent(PivotPoint);

	return SpawnedItem;
}

APickable* UInventory::DropActiveItem(UWorld* World, FVector SpawnPoint, FRotator SpawnRotation, FVector ForceDirection, float ForceStrength)
{
	UClass* ItemClass = GetActiveItemClass();

	APickable* SpawnedItem = SpawnActiveItem(World, ItemClass, SpawnPoint, SpawnRotation);

	if (SpawnedItem == nullptr)
	{
		return nullptr;
	}

	ApplyForceToItem(SpawnedItem, ForceDirection, ForceStrength);
	DeleteItem(DataList[ActiveItemID]->ID);
	return SpawnedItem;
}

APickable* UInventory::SpawnActiveItem(UWorld* World, UClass* ItemClass, FVector SpawnPoint, FRotator SpawnRotation)
{
	if (DataList.Num() == 0 || ActiveItemID > DataList.Num() - 1)
	{
		return nullptr;
	}

	if (World != nullptr && ItemClass != nullptr)
	{
		APickable* SpawnedItem = World->SpawnActor<APickable>(ItemClass, SpawnPoint, SpawnRotation);
		return SpawnedItem;
	}

	return nullptr;
}

UClass* UInventory::GetActiveItemClass()
{
	if (DataList.Num() == 0 || ActiveItemID > DataList.Num() - 1)
	{
		return nullptr;
	}

	FPickableData* ItemToSpawn = DataList[ActiveItemID];
	if (ItemToSpawn != nullptr)
	{
		UClass* ItemClass = ItemToSpawn->ItemClass;
		return ItemClass;
	}

	return nullptr;
}

void UInventory::ApplyForceToItem(APickable* ItemToApplyForce, FVector ForceDirection, float ForceStrength)
{
	if (ItemToApplyForce != nullptr)
	{
		ItemToApplyForce->SetPhysics(true);
		ItemToApplyForce->ApplyForce(ForceDirection, ForceStrength);
	}
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
		ActiveItemID = ActiveItemID - 1;
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
		ActiveItemID = ActiveItemID + 1;
	}
}

FString UInventory::GetActiveItemID()
{
	if (DataList.Num() == 0 || ActiveItemID > DataList.Num() - 1)
	{
		return "";
	}
	return DataList[ActiveItemID]->ID;
}

int32 UInventory::GetNumOfItemsInInventory()
{
	return DataList.Num();
}

void UInventory::ClearActiveItem()
{
	ActiveItem = nullptr;
}
