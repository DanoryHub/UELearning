// Fill out your copyright notice in the Description page of Project Settings.

#include "LearningGameMode.h"
#include "MyFirstActor.h"

void ALearningGameMode::BeginPlay()
{
	ALearningGameMode* gm = Cast<ALearningGameMode>(GetWorld()->GetAuthGameMode());

	if (gm != nullptr)
	{
		UUserProfile* constructedObject = NewObject<UUserProfile>(GetTransientPackage(), UUserProfile::StaticClass());
	}

	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("Actror Spawning"));

	FTransform SpawnLocation;
	GetWorld()->SpawnActor<AMyFirstActor>(AMyFirstActor::StaticClass(), SpawnLocation);
}
