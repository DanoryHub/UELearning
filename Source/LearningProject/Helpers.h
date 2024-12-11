#pragma once

#include "CoreMinimal.h"
#include "Helpers.generated.h"


USTRUCT(BlueprintType)
struct FPickableData
{
	GENERATED_BODY()

	FPickableData() {}

	// Need to be set on BeginPlay of parent Actor ( ugly solution, hope will find better one )
	FString ID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<AActor> ItemClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString Name;
};
