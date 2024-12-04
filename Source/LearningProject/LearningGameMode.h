// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "UserProfile.h"
#include "LearningGameMode.generated.h"

/**
 * 
 */
UCLASS()
class LEARNINGPROJECT_API ALearningGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=UClassNames)
	TSubclassOf<UUserProfile> UPBlueprintClassName;

	virtual void BeginPlay() override;
};
