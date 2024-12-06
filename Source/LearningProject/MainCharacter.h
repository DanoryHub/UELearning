// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

//Forward declaration
class UInputAction;
class UInputMappingContext;
class UEnhancedInputLocalPlayerSubsystem;

UCLASS()
class LEARNINGPROJECT_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void Move(const FInputActionInstance& Instance);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	TMap<FString, UInputAction*> InputActions;

	UEnhancedInputLocalPlayerSubsystem* PlayerInputSystem;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
