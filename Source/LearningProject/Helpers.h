#pragma once

#include "CoreMinimal.h"
#include "Helpers.generated.h"

USTRUCT(BlueprintType)
struct FPickableData
{
	GENERATED_BODY()

	FPickableData() {}

	UClass* ItemClass = nullptr;

	// Need to be set on BeginPlay of parent Actor ( ugly solution, hope will find better one )
	FString ID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString Name;
};
