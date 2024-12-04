// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/SoftObjectPath.h"
#include "ColoredTexture.h"
#include "Status.h"
#include "UserProfile.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class LEARNINGPROJECT_API UUserProfile : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float Armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float HpMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	TSubclassOf<UObject> UClassOfPlayer; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	FColoredTexture Texture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	TEnumAsByte<Status> Status;

};
